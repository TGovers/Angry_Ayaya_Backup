/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "JuceHeader.h"


AnimatedComponent::AnimatedComponent() {
	currentIndex = 0;
	currentImage = images[currentIndex];
	Timer::startTimer(90);
}

void AnimatedComponent::timerCallback()
{
	DBG("in timer callback");
	rotateImage();
	repaint();
}


void AnimatedComponent::paint(juce::Graphics &g)
{
	//DBG(currentIndex);
	g.drawImageAt(currentImage, 0, 0);
}

void AnimatedComponent::rotateImage() {

	if (currentIndex < 48) {
		currentIndex++;
		currentImage = images[currentIndex];
	}
	else if (currentIndex >= 48) {//8
		currentIndex = 0;
		currentImage = images[currentIndex];
	}
	DBG(currentIndex);
}
//==============================================================================
SoftwareSummativeAudioProcessorEditor::SoftwareSummativeAudioProcessorEditor (SoftwareSummativeAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{

	addAndMakeVisible(BigboyAnimation);
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setOpaque(true);
    setSize (540, 450);
    
	filterCutoffDial.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxAbove, true, 55, 30);
	filterCutoffDial.setColour(Slider::ColourIds::textBoxTextColourId, Colours::black);
	filterCutoffDial.setColour(Slider::ColourIds::textBoxOutlineColourId, Colour());
    filterCutoffDial.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
	filterCutoffDial.setNumDecimalPlacesToDisplay(0);
    filterCutoffDial.setSize(150, 100);

    filterCutoffDial.setTextValueSuffix("hz");
 
    
    // dont change these two
    filterCutoffDial.addListener(this);
    addAndMakeVisible(filterCutoffDial);
    
	filterResDial.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxAbove, true, 50,30);
	filterResDial.setColour(Slider::ColourIds::textBoxOutlineColourId, Colour());
    filterResDial.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    filterResDial.setSize(150, 100);
    //filterResDial.setRange(1.0, 5.0);
    filterResDial.setTextValueSuffix("Q");
    //filterResDial.setColour(Slider::ColourIds::rotarySliderFillColourId, Colours::yellowgreen);
	filterResDial.setColour(Slider::ColourIds::textBoxTextColourId, Colours::black);
    
    // dont change these two
    filterResDial.addListener(this);
    addAndMakeVisible(filterResDial);
    
    // dont change these two
    filterCutoffValue = new AudioProcessorValueTreeState::SliderAttachment (processor.mState, "cutoff", filterCutoffDial);
    filterResValue = new AudioProcessorValueTreeState::SliderAttachment (processor.mState, "resonance", filterResDial);
    
    filterCutoffDial.setSkewFactorFromMidPoint(1000.0f);
    
    filterCutoffDial.setLookAndFeel(&otherLookAndFeel2);
    filterResDial.setLookAndFeel(&otherLookAndFeel2);
    
    //addAndMakeVisible(filterCutoffLabel);
   // filterCutoffLabel.setText("Cutoff Freq", dontSendNotification);
    mixLabel.attachToComponent(&filterCutoffDial, false);
    
    addAndMakeVisible(filterResLabel);
    //filterResLabel.setText("Q", dontSendNotification);
    filterResLabel.attachToComponent(&filterResDial, false);
    
    distDriveDial.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    distDriveDial.setSize(150, 100);
    //distDriveDial.setRange(20.0, 20000.0);
    distDriveDial.setTextValueSuffix("%");
    //distDriveDial.setColour(Slider::ColourIds::rotarySliderFillColourId, Colours::yellowgreen);
    
    // dont change these two
    distDriveDial.addListener(this);
    addAndMakeVisible(distDriveDial);
    
    distRangeDial.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
	distRangeDial.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxAbove, true, 55, 30);
	distRangeDial.setColour(Slider::ColourIds::textBoxTextColourId, Colours::black);
	distRangeDial.setColour(Slider::ColourIds::textBoxOutlineColourId, Colour());

    distRangeDial.setSize(150, 100);
    //distRangeDial.setRange(20.0, 20000.0);
    distRangeDial.setTextValueSuffix("f");
    //distRangeDial.setColour(Slider::ColourIds::rotarySliderFillColourId, Colours::yellowgreen);
    
    // dont change these two
    distRangeDial.addListener(this);
    addAndMakeVisible(distRangeDial);
    
    distBlendDial.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
	distBlendDial.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxAbove, true, 55, 30);
	distBlendDial.setColour(Slider::ColourIds::textBoxTextColourId, Colours::black);
	distBlendDial.setColour(Slider::ColourIds::textBoxOutlineColourId, Colour());
	distBlendDial.setNumDecimalPlacesToDisplay(2);
    distBlendDial.setSize(150, 100);
    //distBlendDial.setRange(20.0, 20000.0);
    distBlendDial.setTextValueSuffix("%");
	
    //distBlendDial.setColour(Slider::ColourIds::rotarySliderFillColourId, Colours::yellowgreen);
    
    // dont change these two
    distBlendDial.addListener(this);
    addAndMakeVisible(distBlendDial);
    
    distVolumeDial.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	distVolumeDial.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, true, 100, 30);
	distVolumeDial.setColour(Slider::ColourIds::textBoxTextColourId, Colours::black);
	distVolumeDial.setColour(Slider::ColourIds::textBoxOutlineColourId, Colour());
    distVolumeDial.setSize(100, 70);
    //distVolumeDial.setRange(20.0, 20000.0);
    distVolumeDial.setTextValueSuffix("%");
    //distVolumeDial.setColour(Slider::ColourIds::rotarySliderFillColourId, Colours::yellowgreen);
    
    // dont change these two
    distVolumeDial.addListener(this);
    addAndMakeVisible(distVolumeDial);
    
	distDriveDial.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxAbove, true, 55, 30);
	distDriveDial.setColour(Slider::ColourIds::textBoxTextColourId, Colours::black);
	distDriveDial.setColour(Slider::ColourIds::textBoxOutlineColourId, Colour());
   
	distDriveDial.setLookAndFeel(&otherLookAndFeel);
    distRangeDial.setLookAndFeel(&otherLookAndFeel);
    distBlendDial.setLookAndFeel(&otherLookAndFeel);
    distVolumeDial.setLookAndFeel(&otherLookAndFeel3);
    
    
    // dont change these four
    distDriveValue = new AudioProcessorValueTreeState::SliderAttachment (processor.mState, "drive", distDriveDial);
    distRangeValue = new AudioProcessorValueTreeState::SliderAttachment (processor.mState, "range", distRangeDial);
    distBlendValue = new AudioProcessorValueTreeState::SliderAttachment (processor.mState, "blend", distBlendDial);
    distVolumeValue = new AudioProcessorValueTreeState::SliderAttachment (processor.mState, "volume", distVolumeDial);

}

SoftwareSummativeAudioProcessorEditor::~SoftwareSummativeAudioProcessorEditor()
{
}

//==============================================================================
void SoftwareSummativeAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
	Image background = ImageCache::getFromMemory(BinaryData::AyayaBackground_png, BinaryData::AyayaBackground_pngSize);
	g.drawImageAt(background, 0, 0);
}

void SoftwareSummativeAudioProcessorEditor::resized()
{    
    //mixSlider.setBounds(10, getHeight()-100, 80, 80);
    filterCutoffDial.setBounds(0, getHeight()-130, 80, 80);
    filterResDial.setBounds(100, getHeight()-130, 80, 80);
    distDriveDial.setBounds(200, getHeight()-130, 80, 80);
    distRangeDial.setBounds(300, getHeight()-130, 80, 80);
    distBlendDial.setBounds(400, getHeight()-130, 80, 80);
    distVolumeDial.setBounds(425, getHeight()-310, 80, 80);

	BigboyAnimation.setBounds(getLocalBounds());
    
    
}

void SoftwareSummativeAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
    if (slider == &mixSlider)
    {
        processor.mixLevel.setTargetValue(mixSlider.getValue());
        
    }
    
}
