This is an Alpha release use at your own risk, it is provided GPLv3 license withuot warranty no assumed liability for enduse.

EQAlpha2

EQAlpha2 is a 4-band parametric VST3 equalizer plugin inspired by the revered API 550B, tailored for electronic music production. Crafted in JUCE 8.0.9 with the Steinberg VST3 SDK, EQAlpha2 blends analog warmth and modular tonal control—with features like saturation drive, proportional/fixed Q, and flexible shelf/peak toggles—into a sleek, modern plugin. Cross-platform compatible and tested in FL Studio 2025, Ableton Live, and Reaper.

Developed by William Ashley, a hobbyist producer and plugin developer, EQAlpha2 builds on the musical foundation of EQAlpha1 with expanded control and enhanced UI. Explore more of my journey at my Official Website
 or YouTube channel
.

Features

4-Band Parametric EQ with stepped controls for repeatable precision:

Low Band (40–2400 Hz, peak/shelf toggle)

Low-Mid Band (40–2400 Hz, includes saturation DRIVE)

High-Mid Band (800–12 500 Hz, Q MODE toggle between fixed and proportional Q)

High Band (800–12 500 Hz, peak/shelf toggle)

Saturation DRIVE (Low-Mid band): dial in analog-esque grit and fullness via a tanh-based stage (0.5–5.0).

Proportional / Fixed Q switch ("Q MODE"): choose fixed Q (~1.5) for API 550B authenticity or proportional Q (0.7–2.2) for dynamic bandwidth.

Shelf/Peak Flexibility: Sculpt broad or focused curves on the Low and High bands.

Modern, Resizable UI: API-blue knobs, bold labels, adjustable window sizing (600×420 → 1200×840).

Tested on Windows 11 in FL Studio 2025

git clone https://github.com/WilliamAshley2019/EQAlpha2.git



Build (requires JUCE 8.0.9, VST3 SDK, and CMake):


Windows → copy EQAlpha2.vst3 to C:\Program Files\Common Files\VST3\

Load in DAW: Rescan plugins in FL Studio, Ableton Live, Reaper, etc. and insert EQAlpha2 into your session.

Quick Usage Guide

Load EQAlpha2 onto a mixer track or bus.

Adjust Frequencies & Gain with stepped rotary knobs.

Toggle shelf/peak curves on the Low and High bands.

Use DRIVE in the Low-Mid band to add warmth or distortion; type exact values into the text box if needed.

Switch Q MODE on the High-Mid band for analog-style tone shaping.

Automate DRIVE or Q MODE for dynamic transitions or creative FX.

For deeper analysis, test DSP behavior using Plugin Doctor or similar tools.

Comparison: EQAlpha2 vs. EQAlpha1 & Other Plugins
Plugin	Strengths
EQAlpha1	Simple 3-band EQ with proportional Q and saturation—great for intuitive, musical mixing.
EQAlpha2	Expanded 4-band control, DRIVE saturation, Q MODE flexibility, and advanced UI for more nuanced production needs.
Has classic analog character.

Contributing & Support

I welcome feature requests, bug reports, and enhancements!

Fork the repo

git checkout -b feature/your-feature

git commit -m "Add your feature"

git push origin feature/your-feature

Open a Pull Request with screenshots if related to GUI changes.

Please test builds in Debug x64, and report issues on the Issues tab
.

License & Acknowledgments

EQAlpha2 is licensed under GPLv3.

Built using JUCE 8.0.9 (GPLv3 or commercial)—see JUCE
 for details.

Uses Steinberg VST3 SDK under GPLv3 licensing terms. VST® is a registered trademark of Steinberg Media Technologies GmbH.

Inspired by the API 550B filter design and sonics of the API 2520 op-amp with some twists.

About Me — William Ashley

I’m an electronic music producer and dedicated plugin developer, who currently is taking on making plugins that are inspired by classic analog equipment that defined early studio development. 
EQAlpha2 reflects my passion for crafting musical tools that sound great and foster creative workflows. It is not intended to be a clone of api but take some of the design principles and in this plugin I took some liberties to make it a little more flexible with qmode 
and drive adjustment.

Connect with my projects and sound design explorations:

Website: williamashley https://12264447666william.wixsite.com/williamashley

YouTube: WilliamAshleyOnline https://www.youtube.com/@WilliamAshleyOnline

Support: Buy Me a Coffee https://buymeacoffee.com/williamashley

Stay tuned for updates on EQAlpha2 and the upcoming EQAlpha3, featuring more creative filters and interactive UI enhancements. I'm not entirely sure what it will just yet we will all need to wait and see.
