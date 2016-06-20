# djlights
cheap multichannel light controller for tractor.

the microcontroller I used is the teensy 2.0 which can be bought for 16$
https://www.pjrc.com/store/teensy.html

The current code will support only one RGB led strip.
This well be increased to 3 in the near future.

The current code will run run a series of 7 different music effects. 
Each will run for 64 beats before continuing to the next one. The seven effects will run in a loop continously.

In order to feed the teensy controller with the midi data needed a generic midi device needs to be imported in tractor using a custom tsi file. This file is included "djlights.tsi"

the Music effects are synced to the beat and amplitude of the song loaded in tractor.



