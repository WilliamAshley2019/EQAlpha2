#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"

class ApiLookAndFeel;

class Api550bAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    Api550bAudioProcessorEditor(Api550bAudioProcessor&);
    ~Api550bAudioProcessorEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    Api550bAudioProcessor& audioProcessor;

    juce::Slider lowFreqSlider, lowMidFreqSlider, highMidFreqSlider, highFreqSlider;
    juce::Slider lowGainSlider, lowMidGainSlider, highMidGainSlider, highGainSlider;
    juce::Slider satDriveSlider;
    juce::TextButton lowShelfButton, highShelfButton, qModeButton;
    juce::Label lowBandLabel, lowMidBandLabel, highMidBandLabel, highBandLabel;

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    using ButtonAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;

    std::unique_ptr<SliderAttachment> lowFreqAttachment, lowGainAttachment, lowMidFreqAttachment, lowMidGainAttachment;
    std::unique_ptr<SliderAttachment> highMidFreqAttachment, highMidGainAttachment, highFreqAttachment, highGainAttachment;
    std::unique_ptr<SliderAttachment> satDriveAttachment;
    std::unique_ptr<ButtonAttachment> lowShelfAttachment, highShelfAttachment, qModeAttachment;

    std::unique_ptr<ApiLookAndFeel> laf;

    void setupSlider(juce::Slider& slider);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Api550bAudioProcessorEditor)
};