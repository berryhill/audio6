#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "PlayerAudio.hpp"
#include "../JuceLibraryCode/JuceHeader.h"


class MainContentComponent   : public AudioAppComponent {
public:
    PlayerAudio* playerOne;
    PlayerAudio* playerTwo;
    
    MainContentComponent() {
        playerOne = new PlayerAudio();
        playerTwo = new PlayerAudio();
        
        addAndMakeVisible(playerOne);
        addAndMakeVisible(playerTwo);
        
        setSize (800, 600);
//        setAudioChannels (0, 2);
    }

    ~MainContentComponent() {
        shutdownAudio();
    }
    
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override {
    }

    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override {
    }

    void releaseResources() override {
    }

    void paint (Graphics& g) override {
        g.fillAll (Colours::black);
    }

    void resized() override {
        playerOne->setBounds(0, 0, 600, 120);
        playerTwo->setBounds(0, 130, 600, 120);
    }


private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};

Component* createMainContentComponent()     { return new MainContentComponent(); }


#endif  // MAINCOMPONENT_H_INCLUDED
