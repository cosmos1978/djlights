# djlights
cheap multichannel light controller for tractor.

the microcontroller I used is the teensy 2.0 which can be bought for 16$
https://www.pjrc.com/store/teensy.html

The current code will support only one RGB led strip.
This well be increased to 3 in the near future.

circuit board setup is based on http://www.jerome-bernard.com/blog/2013/01/12/rgb-led-strip-controlled-by-an-arduino/
the 3 resistors can be skipped but then from the moment the teensy board is connected to tractor the lights will light up. So it is best to add the pullup resistors. I used mosfet's P16NF06 from stmicroelectronics http://www.st.com/content/ccc/resource/technical/document/datasheet/f3/e2/b6/5c/fc/9c/41/16/CD00002501.pdf/files/CD00002501.pdf/jcr:content/translations/en.CD00002501.pdf
 This mosfet can pull 16 amps so thats at least 750 5050 led's.

The current code will run run a series of 7 different music effects. 
Each will run for 64 beats before continuing to the next one. The seven effects will run in a loop continously.

In order to feed the teensy controller with the midi data needed a generic midi device needs to be imported in tractor using a custom tsi file. This file is included "djlights.tsi"

the Music effects are synced to the beat and amplitude of the song loaded in tractor depending on the light effect currently in use.





