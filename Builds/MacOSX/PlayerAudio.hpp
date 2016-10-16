
#ifndef PlayerAudio_hpp
#define PlayerAudio_hpp

#include <stdio.h>
#include "../JuceLibraryCode/JuceHeader.h"

class PlayerAudio : public AudioAppComponent, public ChangeListener, public Button::Listener {
public:
    AudioFormatManager formatManager;
    ScopedPointer<AudioFormatReaderSource> readerSource;
    AudioTransportSource transportSource;
    
    PlayerAudio();
    ~PlayerAudio();
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;
    
    void paint (Graphics&) override;
    void changeListenerCallback (ChangeBroadcaster* source) override;
    void resized() override;
    
    TextButton playButton;
    TextButton stopButton;
    TextButton openButton;
    
    void buttonClicked(Button* button) override;
    void playButtonClicked();
    void stopButtonClicked();
    void openButtonClicked();
    
private:
    
    
    enum TransportState
    {
        Stopped,
        Play,
        Stopping
    };
    
    void changeState(TransportState newState);
    
    TransportState state;
};


#endif /* PlayerAudio_hpp */
