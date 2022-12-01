/*
    This is an example where a push button is used to change through the different modes
    4 LEDs are used as a binary counter.
*/

#include <cycler.h>
#include <MIDI.h>

const int buttonPin = 2;
const int led1Pin   = 4;
const int led2Pin   = 5;
const int led3Pin   = 6;
const int led4Pin   = 7;

int buttonState;
int lastButtonState = LOW;
int mode = CYCLER_MODE_6_POLY;

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

MIDI_CREATE_DEFAULT_INSTANCE();

void updateLEDs() {
  digitalWrite(led1Pin, bitRead(mode, 0) == 1);
  digitalWrite(led2Pin, bitRead(mode, 1) == 1);
  digitalWrite(led3Pin, bitRead(mode, 2) == 1);
  digitalWrite(led4Pin, bitRead(mode, 3) == 1);
}

void handleNoteOn(byte inChannel, byte inNote, byte inVelocity)
{
    // Register our note with Cycler.
    // Cycler will give us the next free channel, that we can use to pass the information through:
    byte channel = cycler_note_on(inNote, inVelocity);
    MIDI.sendNoteOn(inNote, inVelocity, channel);
}

void handleNoteOff(byte inChannel, byte inNote, byte inVelocity)
{
    // If it's a note off, we need to inform cycler that there is a note off.
    // Cycler will return the channel that was assigned, so we can pass it through:
    byte channel = cycler_note_off(inNote);
    MIDI.sendNoteOff(inNote, inVelocity, channel);
}

void readModeButton() {
  int reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == HIGH) {
        // Increase mode:
        mode += 1;
        if (mode == 6) {
          mode = CYCLER_MODE_NONE;
        }
        cycler_set_mode(mode);
        updateLEDs();
      }
    }
  }

  lastButtonState = reading;
}

void setup()
{
    pinMode(buttonPin, INPUT);
    pinMode(led1Pin, OUTPUT);
    pinMode(led2Pin, OUTPUT);
    pinMode(led3Pin, OUTPUT);
    pinMode(led4Pin, OUTPUT);
  
    // set initial LED state
    updateLEDs();
  
    // Register note handlers
    MIDI.setHandleNoteOn(handleNoteOn);
    MIDI.setHandleNoteOff(handleNoteOff);
    
    // Launch MIDI, listening to channel 1.
    MIDI.begin(1); 
    cycler_set_mode(mode);
}

void loop()
{
    // @TODO: Let the clock through
    readModeButton();
    if (MIDI.read()) {
        switch(MIDI.getType()) {
            case midi::Clock:       
                // If it is a Clock tick, we need to inform Cycler that there has been a clock tick.
                cycler_tick();
                break;
        }
    }
}