# Cycler

C Library to create a cool Arduino tool to use with the Elektron Model: Cycles

It adds some different modes to turn you Model: Cycles into a polyphonic FM synthesizer. And more...

## Modes

1. 6-Voice polyphony
2. 3/3 Voice polyphony
3. 4-Voice polyphony
4. 3/1 Voice polyphony

### 1. 6 Voice polyphony

This mode will re-route incoming midi signals on channel 1 to channel 1-6 depending on:

- Which channel is free
- If more than 1 channel is free: which one has been free the longest (to mess as little as possible with long decay tails).
- If all channels are occupied: sacrifice the channel that currently is playing with the lowest velocity.

### 2. 3/3 Voice polyphony

This is the same as the 6-Voice polyphony, only with the keybed divided on the center note (C5 by default). Everything below that note is (polyphonicly) divided over channel 1 to 3, everything from that note and higher is divided over channel 4 to 6.

### 3. 4 Voice polyphony

This is the same as the 6-Voice polyphony, only then with 4 channels (1 to 4). Channel 5 and 6 are never used, so you can use these two channels to create a pattern like you would do normally on the Model: Cycles (but then with 2 tracks instead of 6). You will be amazed how creative you can get with 2 tracks and trig locks.

### 4. 3/1 Voice polyphony

This is the same as 3/3 voice polyphony, with the only difference that everything above the center note is polyphonic (this will play in channel 4). As with 4 voice polyphony, channel 5 and 6 are unused, so you can use those to create a pattern to accompany you.

## Contributing

tbd

## License

See the <LICENSE> file.
