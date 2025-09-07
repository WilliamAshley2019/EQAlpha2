#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <cmath>

class ApiLookAndFeel : public juce::LookAndFeel_V4
{
public:
    ApiLookAndFeel()
    {
        setColour(juce::Slider::thumbColourId, juce::Colour(0xffe2e2e2)); // Pointer
        setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colour(0xff00529e)); // API Blue
        setColour(juce::Slider::rotarySliderFillColourId, juce::Colour(0xff2b2b2b)); // Knob face
        setColour(juce::Label::textColourId, juce::Colours::lightgrey);
        setColour(juce::TextButton::textColourOnId, juce::Colour(0xff00529e)); // API Blue when toggled
        setColour(juce::TextButton::textColourOffId, juce::Colours::lightgrey);
        setColour(juce::TextButton::buttonColourId, juce::Colour(0xff333333));
        setColour(juce::TextButton::buttonOnColourId, juce::Colour(0xff555555)); // Lighter when toggled
    }

    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
        const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& /*slider*/) override
    {
        auto bounds = juce::Rectangle<float>(static_cast<float>(x), static_cast<float>(y),
            static_cast<float>(width), static_cast<float>(height)).reduced(10.0f);
        auto radius = juce::jmin(bounds.getWidth(), bounds.getHeight()) / 2.0f;
        auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
        auto lineW = juce::jmin(4.0f, radius * 0.25f);
        auto centre = bounds.getCentre();

        g.setColour(findColour(juce::Slider::rotarySliderFillColourId));
        g.fillEllipse(bounds);

        g.setColour(findColour(juce::Slider::rotarySliderOutlineColourId));
        g.drawEllipse(bounds, lineW);

        juce::Path p;
        p.startNewSubPath(centre.getX(), centre.getY() - radius * 0.4f);
        p.lineTo(centre.getX(), centre.getY() - radius);
        g.setColour(findColour(juce::Slider::thumbColourId));
        g.strokePath(p, juce::PathStrokeType(lineW, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
        p.applyTransform(juce::AffineTransform::rotation(toAngle, centre.getX(), centre.getY()));
        g.strokePath(p, juce::PathStrokeType(lineW, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
    }

    void drawToggleButton(juce::Graphics& g, juce::TextButton& button, bool /*shouldDrawButtonAsHighlighted*/, bool /*shouldDrawButtonAsDown*/)
    {
        auto bounds = button.getLocalBounds().toFloat().reduced(2.0f);
        g.setColour(button.getToggleState() ? findColour(juce::TextButton::buttonOnColourId) : findColour(juce::TextButton::buttonColourId));
        g.fillRoundedRectangle(bounds, 4.0f);
        g.setColour(findColour(button.getToggleState() ? juce::TextButton::textColourOnId : juce::TextButton::textColourOffId));
        g.setFont(juce::FontOptions(12.0f, juce::Font::bold));
        g.drawText(button.getButtonText(), bounds, juce::Justification::centred, true);
    }
};

Api550bAudioProcessorEditor::Api550bAudioProcessorEditor(Api550bAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    laf = std::make_unique<ApiLookAndFeel>();
    setLookAndFeel(laf.get());

    setupSlider(lowFreqSlider);
    setupSlider(lowMidFreqSlider);
    setupSlider(highMidFreqSlider);
    setupSlider(highFreqSlider);
    setupSlider(lowGainSlider);
    setupSlider(lowMidGainSlider);
    setupSlider(highMidGainSlider);
    setupSlider(highGainSlider);
    setupSlider(satDriveSlider);

    auto setupLabel = [&](juce::Label& label, const juce::String& text, float fontSize = 14.0f) {
        label.setText(text, juce::dontSendNotification);
        label.setJustificationType(juce::Justification::centred);
        label.setFont(juce::FontOptions(fontSize));
        addAndMakeVisible(label);
        };

    setupLabel(lowBandLabel, "LOW");
    setupLabel(lowMidBandLabel, "LOW-MID");
    setupLabel(highMidBandLabel, "HIGH-MID");
    setupLabel(highBandLabel, "HIGH");

    auto setupButton = [&](juce::TextButton& button, const juce::String& text) {
        addAndMakeVisible(button);
        button.setButtonText(text);
        button.setClickingTogglesState(true);
        button.setToggleState(false, juce::dontSendNotification); // Initialize to off
        };

    setupButton(lowShelfButton, "SHELF");
    setupButton(highShelfButton, "SHELF");
    setupButton(qModeButton, "Q MODE");

    lowFreqAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, Params::LOW_FREQ, lowFreqSlider);
    lowGainAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, Params::LOW_GAIN, lowGainSlider);
    lowShelfAttachment = std::make_unique<ButtonAttachment>(audioProcessor.apvts, Params::LOW_SHELF, lowShelfButton);
    lowMidFreqAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, Params::LM_FREQ, lowMidFreqSlider);
    lowMidGainAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, Params::LM_GAIN, lowMidGainSlider);
    highMidFreqAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, Params::HM_FREQ, highMidFreqSlider);
    highMidGainAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, Params::HM_GAIN, highMidGainSlider);
    highFreqAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, Params::HIGH_FREQ, highFreqSlider);
    highGainAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, Params::HIGH_GAIN, highGainSlider); // Fixed: Changed SlaveAttachment to SliderAttachment
    highShelfAttachment = std::make_unique<ButtonAttachment>(audioProcessor.apvts, Params::HIGH_SHELF, highShelfButton);
    satDriveAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, Params::SAT_DRIVE, satDriveSlider);
    qModeAttachment = std::make_unique<ButtonAttachment>(audioProcessor.apvts, Params::Q_MODE, qModeButton);

    setSize(600, 420);
    setResizable(true, true);
    setResizeLimits(600, 420, 1200, 840);
}

Api550bAudioProcessorEditor::~Api550bAudioProcessorEditor()
{
    setLookAndFeel(nullptr);
}

void Api550bAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colour(0xff222222)); // Dark charcoal background

    auto bounds = getLocalBounds();
    g.setColour(juce::Colours::lightgrey);
    g.setFont(juce::FontOptions(22.0f, juce::Font::bold));
    g.drawText("EQ Alpha 2", bounds.removeFromTop(50), juce::Justification::centred, true);

    auto panelBounds = bounds.reduced(10);
    g.setColour(juce::Colour(0xff1a1a1a)); // Slightly lighter charcoal for panels

    const int numBands = 4;
    const int panelWidth = panelBounds.getWidth() / numBands;

    for (int i = 0; i < numBands; ++i)
    {
        g.fillRoundedRectangle(static_cast<float>(panelBounds.getX() + i * panelWidth),
            static_cast<float>(panelBounds.getY()),
            static_cast<float>(panelWidth - 5),
            static_cast<float>(panelBounds.getHeight()), 10.0f);
    }
}

void Api550bAudioProcessorEditor::resized()
{
    auto bounds = getLocalBounds();
    bounds.removeFromTop(50); // Space for title
    bounds.reduce(15, 15);

    const int numBands = 4;
    const int bandWidth = (bounds.getWidth() - (numBands - 1) * 10) / numBands; // ~140px at 600px width

    auto layoutBand = [&](juce::Rectangle<int> area, juce::Label& bandLabel,
        juce::Slider& freqSlider, juce::Slider& gainSlider, juce::Component* extraControl, juce::Label* extraLabelTop = nullptr, juce::Label* extraLabelBottom = nullptr)
        {
            const int labelHeight = 25;
            const int knobSize = 60;
            const int textBoxHeight = 30; // Taller for readability
            const int buttonHeight = 25;
            const int spacing = 10;

            bandLabel.setBounds(area.removeFromTop(labelHeight));
            area.removeFromTop(spacing);

            auto knobArea = area.removeFromTop(knobSize);
            freqSlider.setBounds(knobArea.withWidth(knobSize).withX(area.getCentreX() - knobSize / 2));

            area.removeFromTop(spacing);

            auto gainKnobArea = area.removeFromTop(knobSize);
            gainSlider.setBounds(gainKnobArea.withWidth(knobSize).withX(area.getCentreX() - knobSize / 2));

            if (extraControl)
            {
                area.removeFromTop(spacing);
                if (extraLabelTop)
                    extraLabelTop->setBounds(area.removeFromTop(labelHeight));
                area.removeFromTop(spacing);
                if (dynamic_cast<juce::Slider*>(extraControl)) // For satDriveSlider
                    extraControl->setBounds(area.removeFromTop(knobSize + textBoxHeight).reduced(area.getWidth() / 4, 0));
                else // For qModeButton
                    extraControl->setBounds(area.removeFromTop(buttonHeight).reduced(area.getWidth() / 4, 0));
                if (extraLabelBottom)
                {
                    area.removeFromTop(spacing);
                    extraLabelBottom->setBounds(area.removeFromTop(labelHeight));
                }
            }
        };

    for (int i = 0; i < numBands; ++i)
    {
        auto column = bounds.withX(bounds.getX() + i * (bandWidth + 10)).withWidth(bandWidth);

        if (i == 0) // Low Band: Shelf toggle
        {
            layoutBand(column, lowBandLabel, lowFreqSlider, lowGainSlider, &lowShelfButton);
        }
        else if (i == 1) // Low-Mid Band: Sat Drive
        {
            juce::Label satDriveLabel;
            addAndMakeVisible(satDriveLabel);
            satDriveLabel.setText("DRIVE", juce::dontSendNotification);
            satDriveLabel.setJustificationType(juce::Justification::centred);
            satDriveLabel.setFont(juce::FontOptions(22.0f, juce::Font::bold)); // Match title font
            satDriveLabel.setColour(juce::Label::textColourId, juce::Colours::white); // White like title
            layoutBand(column, lowMidBandLabel, lowMidFreqSlider, lowMidGainSlider, &satDriveSlider, &satDriveLabel);
        }
        else if (i == 2) // High-Mid Band: Q Mode
        {
            juce::Label qModeLabel, qModeLabelBelow;
            addAndMakeVisible(qModeLabel);
            addAndMakeVisible(qModeLabelBelow);
            qModeLabel.setText("Q MODE", juce::dontSendNotification);
            qModeLabel.setJustificationType(juce::Justification::centred);
            qModeLabel.setFont(juce::FontOptions(14.0f));
            qModeLabelBelow.setText("FIXED / PROP", juce::dontSendNotification);
            qModeLabelBelow.setJustificationType(juce::Justification::centred);
            qModeLabelBelow.setFont(juce::FontOptions(14.0f));
            layoutBand(column, highMidBandLabel, highMidFreqSlider, highMidGainSlider, &qModeButton, &qModeLabel, &qModeLabelBelow);
        }
        else if (i == 3) // High Band: Shelf toggle
        {
            layoutBand(column, highBandLabel, highFreqSlider, highGainSlider, &highShelfButton);
        }
    }
}

void Api550bAudioProcessorEditor::setupSlider(juce::Slider& slider)
{
    slider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 30); // Editable, taller text box
    slider.setTextValueSuffix("");
    addAndMakeVisible(slider);
}