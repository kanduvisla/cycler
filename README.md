# Cycler

C Library to create a cool Arduino tool to use with the Elektron Model: Cycles

It adds some different modes to turn you Model: Cycles into a polyphonic FM synthesizer. And more...

This is written with the Elektron Model: Cycles in mind, but basically it will work with any device that handles 6 different midi channels (or multiple devices, be creative!)

## Modes

1. 6-Voice polyphony
2. 3/3 Voice polyphony
3. 3/1 Voice polyphony
4. 4-Voice polyphony
5. 4/1 Voice polyphony

### 6 Voice polyphony

This mode will re-route incoming midi signals on channel 1 to channel 1-6 depending on:

- Which channel is free
- If more than 1 channel is free: which one has been free the longest (to mess as little as possible with long decay tails).
- If all channels are occupied: sacrifice the channel that currently is playing with the lowest velocity.

#### Usage

Make use of the [standard Arduino Midi library](https://github.com/FortySevenEffects/arduino_midi_library) and place the Cycler code in-between:

```c
// WIP / Not tested yet:
void handleNoteOn(byte inChannel, byte inNote, byte inVelocity)
{
    // Register our note with Cycler.
    // Cycler will give us the next free channel, that we can use to pass the information through:
    byte channel = cycler_note_on(inNote, inVelocity, channel);
    // TODO: Check if this does not result in an infinite loop:
    MIDI.sendNoteOn(inNote, inVelocity, channel);
}

void handleNoteOff(byte inChannel, byte inNote, byte inVelocity)
{
    // If it's a note off, we need to inform cycler that there is a note off.
    // Cycler will return the channel that was assigned, so we can pass it through:
    byte channel = cycler_note_off(inNote);
    // TODO: Check if this does not result in an infinite loop:
    MIDI.sendNoteOff(inNote, inVelocity, channel);
}

void setup()
{
    // Register note handlers
    MIDI.setHandleNoteOn(handleNoteOn);
    MIDI.setHandleNoteOff(handleNoteOff);
    // Launch MIDI, listening to channel 1.
    MIDI.begin(1);
}

void loop()
{
    if (MIDI.read()) {
        switch(MIDI.getType()) {
            case midi::Clock:       
                // If it is a Clock tick, we need to inform Cycler that there has been a clock tick.
                cycler_tick();
                break;
        }
    }
}
```

### 3/3 Voice polyphony

This is the same as the 6-Voice polyphony, only with the keybed divided on the center note (C5 by default). Everything below that note is (polyphonicly) divided over channel 1 to 3, everything from that note and higher is divided over channel 4 to 6.

### 3/1 Voice polyphony

This is the same as 3/3 voice polyphony, with the only difference that everything above the center note is polyphonic (this will play in channel 4). As with 4 voice polyphony, channel 5 and 6 are unused, so you can use those to create a pattern to accompany you.

### 4 Voice polyphony

This is the same as the 6-Voice polyphony, only then with 4 channels (1 to 4). Channel 5 and 6 are never used, so you can use these two channels to create a pattern like you would do normally on the Model: Cycles (but then with 2 tracks instead of 6). You will be amazed how creative you can get with 2 tracks and trig locks.

### 4/1 Voice polyphony

This is the same as 3/1 voice polyphony, with the only difference that you have 4 channels below the center note, and 1 note above the center note (this will play in channel 5). Channel 6 is unused, so you can use that to create a funky pattern to accompany you.

## Contributing

If you want to contribute, feel free to fork and create a pull request.

### Testing

To be honest, this is my first real C project, so I don't have experience with default C unit-test frameworks. I do however have a test target with some test code that validates certain stuff. You can test the code by running `make test`. If you want to add extra tests, just edit the [test.c](test.c) file.

## License

See the [LICENSE](LICENSE) file.
