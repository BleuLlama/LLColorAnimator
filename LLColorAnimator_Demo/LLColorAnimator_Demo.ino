// LLColorAnimator Demo (WS2801)
//  yorgle@gmail.com
//
//	Pattern manager and runtime for Addressable LED strands
//
// HARDWARE CONFIGURATION:
//
//  D11 --- WS2801 Clock (GREEN)
//  D12 --- WS2801 Data (WHITE)
//
//  A1 --- Button A --- [gnd]     (previous sequence)
//  A0 --- Button B --- [gnd]     (next sequence)
//
//  A2 --- 10k pot wiper          (animation speed)
//  A3 --- 10k pot wiper          (display brightness)
//    pot poles are wired to +5v on one side, ground on the other
//
//
//  2020-12-20  - initial version

#define kVersion "LCADemo - 2020-12-20"

#include "header.h"

/*****************************************************************************
   Color Anomator configuration
*/

#include "LLColorAnimator.h"

const unsigned long palette[12] = {
  LLCA_COLOR( 'W', 100, 192, 192 ),
  LLCA_COLOR( '-',   0,   0,   0 ),
  LLCA_COLOR( 'R', 192,   0,   0 ),
  LLCA_COLOR( 'O', 100,  20,   0 ),
  LLCA_COLOR( 'Y', 192, 100,   0 ),
  LLCA_COLOR( 'G',   0, 192,   0 ),
  LLCA_COLOR( 'C',   0, 192,  80 ),
  LLCA_COLOR( 'B',   0,   0,  90 ),
  LLCA_COLOR( 'P', 100,   0,  30 ),
  
  LLCA_COLOR( 'V', 100,   0, 100 ),
  
  LLCA_COLOR( 'D',   0,   0,   2 ), // dark blue
  LLCA_END
};


extern const char * sequences[];

LLColorAnimator ca = LLColorAnimator( palette, sequences );

/*****************************************************************************
   WS2801 configuration
*/
#include <Adafruit_WS2801.h>
#include <SPI.h>    /* for comms */

/* The strand that I have has four wires:
     Red    +5v
     White  Data
     Green  Clock
     Blue   Ground
*/
#define kNumberOfLights (42)

/* pin configuration on Arduino */
#define kWS2801_Data  (12)
#define kWS2801_Clock (11)

/* create our "strip" class */
Adafruit_WS2801 strip = Adafruit_WS2801(kNumberOfLights, kWS2801_Data, kWS2801_Clock);


#define kKnobA (A2)
#define kKnobB (A3)

#define kButtonA  (A1)
#define kButtonB  (A0)

// helper classes
Button buttonA = Button( kButtonA );
Button buttonB = Button( kButtonB );


Settings settings = Settings();


void setup()
{
  // serial console setup
  Serial.begin( 115200 );
  
  Serial.println( F( "v. " kVersion ));

  ca.AnimRange( kNumberOfLights );
  ca.SequenceSet( settings.Get( kSetting_Pattern ) );
  ca.Dump();
  
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

  if ( buttonHandled ) {
    return 1;
  }
  return 0;
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

  ca.DurationA( analogRead( kKnobA ));
  ca.Brightness( getBrightness( ));
  ca.Update();
  renderPixels();
}
