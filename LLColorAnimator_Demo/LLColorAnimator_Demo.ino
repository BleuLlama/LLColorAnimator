// LLColorAnimator Demo (WS2801)
//  yorgle@gmail.com
//
//	Pattern manager and runtime for Addressable LED strands
//
//  2020-12-20  - initial version

#define kVersion "LCADemo - 2020-12-27"

#include "header.h"


/*****************************************************************************
   Color Anomator configuration
*/

#include "LLColorAnimator.h"

extern const unsigned long palette[];
extern const char * sequences[];

LLColorAnimator ca = LLColorAnimator( palette, sequences );

/*****************************************************************************
   WS2801 configuration
*/
#include <Adafruit_WS2801.h>
#include <SPI.h>    /* for comms */

/* create our "strip" class */
Adafruit_WS2801 strip = Adafruit_WS2801(kNumberOfLights, kWS2801_Data, kWS2801_Clock);

// helper classes
Button buttonA = Button( kButtonA );
Button buttonB = Button( kButtonB );
TapTempo buttonC = TapTempo( kButtonC );
Button buttonD = Button( kButtonD );


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

  // Builtin LED setup
  pinMode( LED_BUILTIN, OUTPUT );
  digitalWrite( LED_BUILTIN, LOW );

  // strip setup
  strip.begin();
  strip.setPixelColor( 0, COLOR( 32, 0, 0 ));
  strip.show();
  // Update LED contents, to start they are all 'off'
  
  Serial.println( F( " Ready." ));

}



float getBrightness()
{
  int v = 1024 - analogRead( kKnobB );

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
  
  buttonA.Poll();
  buttonB.Poll();

  if( buttonA.WasStarted() ) {
    
    seq = ca.SequencePrev();
    settings.Set( kSetting_Pattern , seq );
    buttonHandled = 1;
  }

  if( buttonB.WasStarted() ) {
    //p++;
    seq = ca.SequenceNext();
    settings.Set( kSetting_Pattern , seq );
    buttonHandled = 1;
  }

  // button C is tap tempo
  buttonC.Poll();

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


  int d = buttonC.Get();
  if( d == 0 ) {
    ca.DurationA( analogRead( kKnobA ));
  } else {
    ca.DurationA( d );  // if you want to be tapping whole notes of 4/4 time, then divide by 4
  }

  
  ca.Brightness( getBrightness( ));
  ca.Update();
  renderPixels();
}
