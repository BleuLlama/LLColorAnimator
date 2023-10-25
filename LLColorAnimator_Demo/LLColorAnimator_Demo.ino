// LLColorAnimator Demo (WS2801+Neopixel)
//  yorgle@gmail.com
//
//	Pattern manager and runtime for Addressable LED strands
//
//  2023-10-24  - Support for SSMicro instead of Uno
//  2022-01-09  - transition support starting
//  2022-01-02  - Support for Neopixels
//  2020-12-20  - initial version

#define kVersion "LCADemo - 2023-10-24"

#include "header.h"


/*****************************************************************************
   Color Anomator configuration
*/

#include "LLColorAnimator.h"

extern const unsigned long palette[];
extern const char * sequences[];

LLColorAnimator ca = LLColorAnimator( palette, sequences );

/*****************************************************************************
   LED strand configuration
*/

// if we're using a 4-wire, WS2801 based strand...
#ifdef kStrand_WS2801
  #include <Adafruit_WS2801.h>
  #include <SPI.h>
  Adafruit_WS2801 strip = Adafruit_WS2801(kNumberOfLights, kWS2801_Data, kWS2801_Clock);
#endif

// or if we're using a 3-wire, neopixel based strand...
#ifdef kStrand_NeoPixel
  #include <Adafruit_NeoPixel.h>
  Adafruit_NeoPixel strip(kNumberOfLights, kNeoPixelPin, NEO_GRB + NEO_KHZ800);
#endif


// button input helper classes
Button buttonA = Button( kButtonA );
Button buttonB = Button( kButtonB );
TapTempo buttonC = TapTempo( kButtonC );
Button buttonD = Button( kButtonD );

#ifdef kUSE_BUTTONS_FOR_SPEED
int buttonSpeed = 100;
Button buttonFaster = Button( kButtonFaster );
Button buttonSlower = Button( kButtonSlower );
#endif

int viewMode = 0;
Button buttonMode = Button( kButtonMode );
int buttonBrightness = 128;

Settings settings = Settings();


void setup()
{
  // serial console setup
  Serial.begin( 115200 );
  
  Serial.println( F( kVersion ));

  ca.AnimRange( kNumberOfLights );
  ca.SequenceSet( settings.Get( kSetting_Pattern ) );
  //ca.Dump();
  
  // random setup
  randomSeed( analogRead( 0 ) + analogRead( 1 ) );

#ifdef kUSE_ANALOG_KNOBS
  pinMode( kKnobA, INPUT );
  pinMode( kKnobB, INPUT );
#endif

  // Builtin LED setup
  pinMode( LED_BUILTIN, OUTPUT );
  digitalWrite( LED_BUILTIN, LOW );

  // strip setup
  strip.begin();
  strip.setPixelColor( 0, COLOR( 32, 0, 0 ));
  strip.show();
  // Update LED contents, to start they are all 'off'
  
  Serial.println( F( " Hellorld." ));

}



float getBrightness()
{
#ifdef kUSE_ANALOG_KNOBS
  int v = 1024 - analogRead( kKnobB );
#else
  int v = buttonBrightness;
#endif

  // add some dead spots
  if( v < 3 ) { v = 0; }
  if( v > 1020 ) { v= 1024; }
  
  float b = (float) v / 1024.0;
  
  return( b );
}

int pollButtons()
{
  int seq = 0;
  int buttonHandled = 0;
  //int p = settings.Get( kSetting_Pattern );
  
#ifdef kUSE_BUTTONS_FOR_SPEED
  buttonFaster.Poll();
  buttonSlower.Poll();

  if( buttonFaster.WasStarted() ) {
    buttonSpeed += 10;
    if( buttonSpeed > 1024 ) { buttonSpeed = 1024; }
    
    Serial.print( F("+ Speed : ") );
    Serial.println( buttonSpeed );
  }
  
  if( buttonSlower.WasStarted() ) {
    buttonSpeed -= 10;
    if( buttonSpeed < 1 ) { buttonSpeed = 1; }
    
    Serial.print( F("- Speed : ") );
    Serial.println( buttonSpeed );
  }
#endif
  
  buttonA.Poll();
  buttonB.Poll();

  if( buttonA.WasStarted() ) {
    
    seq = ca.SequencePrev();
    settings.Set( kSetting_Pattern , seq );
    buttonHandled = 1;
    Serial.print( F("- Pattern # ") );
    Serial.println( seq );
  }

  if( buttonB.WasStarted() ) {
    //p++;
    seq = ca.SequenceNext();
    settings.Set( kSetting_Pattern , seq );
    buttonHandled = 1;
    Serial.print( F("+ Pattern # ") );
    Serial.println( seq );
  }

  // button C is tap tempo
  buttonC.Poll();

#ifdef kButtonDFunction_Transition
#endif
  buttonMode.Poll();
  if( buttonMode.WasStarted() ) {
     viewMode++;
     if( viewMode > 4 ) { viewMode = 0; }
     if( viewMode == 0 ) { Serial.println( F("Cut Out, Cut In") ); }
     if( viewMode == 1 ) { Serial.println( F("Cut Out, Fade In") ); }
     if( viewMode == 2 ) { Serial.println( F("Fade Out, Cut In") ); }
     if( viewMode == 3 ) { Serial.println( F("Fade Out, Fade In") ); }
     if( viewMode == 4 ) { Serial.println( F("Blend") ); }
  }

#ifdef kButtonDFunction_Flash
  // button D triggers a flash
  buttonD.Poll();
  if( buttonD.IsPressing() ) {
      
      while( buttonD.StartTime() ) {
        unsigned long dt = millis() - buttonD.StartTime();
        
        if( dt > 100 ) {
          fillPixels( 0 );
        } else {
          dt = 100-(dt);
          /*
          if( buttonD.PressCount() & 1 ) {
            fillPixelsAlternating( COLOR( dt,dt,dt ), 0 );
          } else {
            fillPixelsAlternating( 0, COLOR( dt,dt,dt ) );
          }*/
          fillPixels( COLOR( dt, dt, dt ));
          
        }
        buttonD.Poll();
      }
  }
 #endif

#ifdef kButtonDFunction_Brightness
  // button D triggers a flash
  buttonD.Poll();
  if( buttonD.WasPressed() ) {
    
    if( buttonBrightness > 700 ) buttonBrightness -= 100;
    else if( buttonBrightness > 500 ) buttonBrightness -= 50;
    else if( buttonBrightness > 100 ) buttonBrightness -= 20;
    else if( buttonBrightness > 50 ) buttonBrightness -= 7;
    else if( buttonBrightness > 20 ) buttonBrightness -= 5;
    else if( buttonBrightness > 9 ) buttonBrightness -= 1;
    else buttonBrightness = 1024;

    
    if( buttonBrightness < 1 ) {
      buttonBrightness = 1024;
    }
    Serial.print( F("Brightness: ") );
    Serial.println( buttonBrightness );
  }
#endif


  if ( buttonHandled ) {
    return 1;
  }
  return 0;
}

void fillPixels( uint32_t c ) 
{
  for (uint16_t i = 0; i < strip.numPixels(); i++ ) {
    strip.setPixelColor( i, c );
  }
  strip.show();
}

void fillPixelsAlternating( uint32_t c1, uint32_t c2 )
{
  for (uint16_t i = 0; i < strip.numPixels(); i++ ) {
    if( i & 1 ) {
      strip.setPixelColor( i, c1 );
    } else {
      strip.setPixelColor( i, c2 );
    }
  }
  strip.show();
}

void renderPixels()
{
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, ca.GetColor( i ) );
  }
  strip.show();
}


void loop() {
  digitalWrite( LED_BUILTIN, millis() & 0x80 );
  pollButtons();

  // tap tempo routine
  int d = buttonC.Get();
  if( d == 0 ) {
#ifdef kUSE_ANALOG_KNOBS
    ca.DurationA( analogRead( kKnobA ));
#else
    ca.DurationA( buttonSpeed );
#endif
  } else {
    ca.DurationA( d );  // if you want to be tapping whole notes of 4/4 time, then divide by 4
  }

  // brightness adjust
  ca.Brightness( getBrightness( ));
  ca.Update();
  renderPixels();
}
