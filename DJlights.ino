/* Print Incoming Message USB MIDI Example
   Use the Arduino Serial Monitor to view the messages
   as Teensy receives them by USB MIDI

   You must select MIDI from the "Tools > USB Type" menu

   This example code is in the public domain.
*/
#define REDPIN 14
#define GREENPIN 15
#define BLUEPIN 12
int channel=14;
int t=1;
int tt=1;
int x=1;
int xx=1;
int setx=1;
int r,g,b,xr,xg,xb;
unsigned int r2, g2, b2;
void setup() {
  Serial.begin(115200);
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
  usbMIDI.setHandleControlChange(OnControlChange);

}

void loop() {
  usbMIDI.read(channel); // USB MIDI receive
}

void OnControlChange(byte channel, byte control, byte value) {
  if ( control == 0 || control == 1 || control == 2 ) {
    if ((x > 0 && x <= 64)&& (control == 2)){
      colorwheelbeat(value);
    }
    if ((x > 64 && x <= 128) && (control == 0 || control == 1)){ 
      fixcolorflash(value);
    }
    if ((x > 128 && x <= 196) && (control == 0 || control == 1 || control == 2 )){ 
      strobecolorwheel(value,control);
    }  
    if ((x > 196 && x <= 256) && (control == 0 || control == 1 || control == 2 )){ 
      colorwheelflash(value,control);
    }  
    if ((x > 256 && x <= 320) && (control == 0 || control == 1)){ 
      randombeatcolor(value);
    }    
    if ((x > 320 && x <= 384) && (control == 0 || control == 1 || control == 2 )){ 
      vubeatcolor(value,control);
    }  
    if ((x > 384 && x <= 448)&& (control == 0 || control == 1)){
      triplewhitestrobe(value);
    }
    if ((x > 448) && (control == 0 || control == 1)){ 
      x = 1;
    }
    if ((control == 0 || control == 1) && (value > 0 && value < 6)){
      x = x + 1;
    }
  }
}
int colorwheelbeat(int value) {
    int test=value ;
    HSBToRGB(test, 255, 255, &r2, &g2, &b2);
    analogWrite(REDPIN, r2);
    analogWrite(GREENPIN, g2);
    analogWrite(BLUEPIN, b2);
}

int strobecolorwheel(int value,int control) {
  if ((value > 0 && value < 16) || (value > 64 && value < 80) && (control == 0 || control == 1) ){
  //if ((value > 0 && value < 16) || (value > 32 && value < 48) || (value > 64 && value < 80 || value > 96  && value < 112) && (control == 0 || control == 1) ){
    if ( setx == 1 ) {
      HSBToRGB(tt, 255, 255, &r2, &g2, &b2);
    }
    setx = 0;
    analogWrite(REDPIN, r2);
    analogWrite(GREENPIN, g2);
    analogWrite(BLUEPIN, b2);
  } else {
    setx = 1;
    analogWrite(GREENPIN, 0);
    analogWrite(REDPIN, 0);
    analogWrite(BLUEPIN, 0);
  }
  if ((value > 0 && value < 5) && (control == 0 || control == 1)){
    tt = tt + 10;
  }
  if (tt > 254) {
    tt = 0;
  }  
}

int colorwheelflash(int value,int control) {
     if (control == 2) {
       HSBToRGB(tt, 255, value * 2, &r2, &g2, &b2);
       analogWrite(REDPIN, r2);
       analogWrite(GREENPIN, g2);
       analogWrite(BLUEPIN, b2);
    }
    if ((value > 0 && value < 5) && (control == 0 || control == 1)){
      tt = tt + 20;
      analogWrite(REDPIN, 255);
      analogWrite(GREENPIN, 255);
      analogWrite(BLUEPIN, 255);
    }
    if (tt > 254) {
      tt = 0;
    }    
}


int vubeatcolor(int value,int control) {
    if ( tt > 0 && tt <= 2 && control == 2) {
      analogWrite(REDPIN, 0 + (value * 2));
      analogWrite(GREENPIN, 0);
      analogWrite(BLUEPIN, 0);
    }
    if ( tt > 2 && tt <= 4 && control == 2) {
      analogWrite(REDPIN, 0 + (value * 2));
      analogWrite(GREENPIN, 0);
      analogWrite(BLUEPIN, 0 + (value * 2));
    }  
    if ( tt > 4 && tt <= 6 && control == 2) {
      analogWrite(REDPIN, 0);
      analogWrite(GREENPIN, 0);
      analogWrite(BLUEPIN, 0  + (value * 2));
    }
    if ( tt > 6 && tt <= 8 && control == 2) {
      analogWrite(REDPIN, 0);
      analogWrite(GREENPIN, 0 + (value * 2));
      analogWrite(BLUEPIN, 0 + (value * 2));
    }
    if ( tt > 8 && tt <= 10 && control == 2) {
      analogWrite(REDPIN, 0);
      analogWrite(GREENPIN, 0 + (value * 2));
      analogWrite(BLUEPIN, 0);
    }
    if ( tt > 10 && tt <= 12 && control == 2) {
      analogWrite(REDPIN, 0 + (value * 2));
      analogWrite(GREENPIN, 0 + (value * 2));
      analogWrite(BLUEPIN, 0);
    }
    if ( tt > 12 && control == 2) {
      tt = 1;
    }
    if ((value > 0 && value < 3) && (control == 0 || control == 1)){
      tt = tt + 1;
    }
}


int triplewhitestrobe(int value) {
  if (value > 0 && value < 16 || value > 32 && value < 48 || value > 64 && value < 80){
    analogWrite(GREENPIN, 255);
    analogWrite(REDPIN, 255);
    analogWrite(BLUEPIN, 255);
  } else {
    analogWrite(GREENPIN, 0);
    analogWrite(REDPIN, 0);
    analogWrite(BLUEPIN, 0);
  }
}

int randombeatcolor(int value) {
  if (value > 0 && value < 6){
    int r = random(255);
    int g = random(255);
    int b = random(255);
    analogWrite(GREENPIN, g);
    analogWrite(REDPIN, r);
    analogWrite(BLUEPIN, b);
  }
}

int fixcolorflash(int value) {
    if ( t > 0 && t <= 16 )
{
    analogWrite(GREENPIN, 0);
    analogWrite(BLUEPIN, 0);
    analogWrite(REDPIN, value * 2);
}
    if ( t > 16 && t <= 32 )
{
    analogWrite(GREENPIN, 0);
    analogWrite(BLUEPIN, value * 2);
    analogWrite(REDPIN, 0);
}
  if ( t > 32 && t <= 48 )
  {
    analogWrite(GREENPIN, value * 2);
    analogWrite(BLUEPIN, 0);
    analogWrite(REDPIN, 0);
}
  if ( t > 48 )
  {
    t = 1;
}
    if (value > 0 && value < 6){
    analogWrite(GREENPIN, 255);
    analogWrite(REDPIN, 255);
    analogWrite(BLUEPIN, 255);
    t = t + 1;
}

}



void HSBToRGB(
    unsigned int inHue, unsigned int inSaturation, unsigned int inBrightness,
    unsigned int *oR, unsigned int *oG, unsigned int *oB )
{
    if (inSaturation == 0)
    {
        // achromatic (grey)
        *oR = *oG = *oB = inBrightness;
    }
    else
    {
        unsigned int scaledHue = (inHue * 6);
        unsigned int sector = scaledHue >> 8; // sector 0 to 5 around the color wheel
        unsigned int offsetInSector = scaledHue - (sector << 8);	// position within the sector         
        unsigned int p = (inBrightness * ( 255 - inSaturation )) >> 8;
        unsigned int q = (inBrightness * ( 255 - ((inSaturation * offsetInSector) >> 8) )) >> 8;
        unsigned int t = (inBrightness * ( 255 - ((inSaturation * ( 255 - offsetInSector )) >> 8) )) >> 8;

        switch( sector ) {
        case 0:
            *oR = inBrightness;
            *oG = t;
            *oB = p;
            break;
        case 1:
            *oR = q;
            *oG = inBrightness;
            *oB = p;
            break;
        case 2:
            *oR = p;
            *oG = inBrightness;
            *oB = t;
            break;
        case 3:
            *oR = p;
            *oG = q;
            *oB = inBrightness;
            break;
        case 4:
            *oR = t;
            *oG = p;
            *oB = inBrightness;
            break;
        default:    // case 5:
            *oR = inBrightness;
            *oG = p;
            *oB = q;
            break;
        }
    }
}
