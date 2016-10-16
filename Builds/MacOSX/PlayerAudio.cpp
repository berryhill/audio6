
#include "PlayerAudio.hpp"

PlayerAudio::PlayerAudio() {
//    setSize (600, 120);
    
    addAndMakeVisible(&playButton);
    playButton.setButtonText (">");
    playButton.addListener (this);
    playButton.setColour (TextButton::buttonColourId, Colours::grey);
    playButton.setEnabled (false);
    
    addAndMakeVisible(&stopButton);
    stopButton.setButtonText ("o");
    stopButton.addListener (this);
    stopButton.setColour (TextButton::buttonColourId, Colours::grey);
    stopButton.setEnabled (false);
    
    addAndMakeVisible(&openButton);
    openButton.setButtonText ("...");
    openButton.addListener (this);
    openButton.setColour (TextButton::buttonColourId, Colours::grey);
    openButton.setEnabled (true);
    
    formatManager.registerBasicFormats();
    transportSource.addChangeListener(this);
    
    setAudioChannels (0, 2);
}

PlayerAudio::~PlayerAudio() {
//    shutdownAudio();
}

void PlayerAudio::prepareToPlay (int samplesPerBlockExpected, double sampleRate) {
    transportSource.prepareToPlay (samplesPerBlockExpected, sampleRate);
}

void PlayerAudio::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) {
    if (readerSource == nullptr) {
        bufferToFill.clearActiveBufferRegion();
        return;
    }
    
    transportSource.getNextAudioBlock (bufferToFill);
}

void PlayerAudio::releaseResources() {
    transportSource.releaseResources();
}

void PlayerAudio::paint (Graphics& g) {
    g.fillAll (Colour (0x00000000));
}

void PlayerAudio::changeListenerCallback (ChangeBroadcaster* source) {
    if (source == &transportSource) {
        if (transportSource.isPlaying())
            changeState (Play);
        else
            changeState (Stopped);
    }
}

void PlayerAudio::buttonClicked(Button* button) {
    if (button == &playButton)  playButtonClicked();
    if (button == &stopButton)  stopButtonClicked();
    if (button == &openButton)  openButtonClicked();
}

void PlayerAudio::playButtonClicked(){
    changeState(Play);
}

void PlayerAudio::stopButtonClicked() {
    changeState(Stopping);
}

void PlayerAudio::openButtonClicked() {
    FileChooser chooser ("Select a Wave file to play...",
                         File::nonexistent,
                         "*.wav");
    
    if(chooser.browseForFileToOpen()) {
        File file (chooser.getResult());
        AudioFormatReader* reader = formatManager.createReaderFor (file);
        
        if(reader != nullptr) {
            ScopedPointer<AudioFormatReaderSource> newSource = new AudioFormatReaderSource (reader, true);
            transportSource.setSource (newSource, 0, nullptr, reader->sampleRate);
            playButton.setEnabled (true);
            readerSource = newSource.release();
        }
    }
}

void PlayerAudio::resized() {
    playButton.setBounds(0, 100, 50, 20);
    stopButton.setBounds (50, 100, 50, 20);
    openButton.setBounds (100, 100, 50, 20);
}

void PlayerAudio::changeState(TransportState newState) {
    if(state != newState) {
        state = newState;
        
        switch(state) {
            case Stopped:
                transportSource.setPosition (0.0);
                break;
            case Play:
                transportSource.start();
                break;
            case Stopping:                          
                transportSource.stop();
                break;
        }
    } else {
        switch(state) {
            case Play:
                transportSource.setPosition(0.0);
        }
    }
}