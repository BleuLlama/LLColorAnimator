

#ifndef __HEADER_H__
#define __HEADER_H__

/*****************************************************************************
   Standard librarires, misc
*/
#include <avr/pgmspace.h>


////////////////////////////////////////////////////////////////
// Settings



// are the sequences in PROGMEM (flash)?
// Probably worthwhile to do...
#define SEQUENCES_IN_PROGMEM

#ifdef SEQUENCES_IN_PROGMEM
  #define SEQLOC PROGMEM
#else
  #define SEQLOC
#endif



////////////////////////////////////////////////////////////////
// Hardware Configuration
//
//  D11 --- WS2801 Clock (GREEN)
//  D12 --- WS2801 Data (WHITE)
//
//  A1 --- Button A --- [gnd]     (previous sequence)
//  A0 --- Button B --- [gnd]     (next sequence)
//  A4 --- Button C --- [gnd]     (tap tempo)
//  A5 --- Button D --- [gnd]     (flash/accent)
//
//  A2 --- 10k pot wiper          (animation speed)
//  A3 --- 10k pot wiper          (display brightness)
//    pot poles are wired to +5v on one side, ground on the other
//
//

/* The strand that I have has four wires:
     Red    +5v
     White  Data
     Green  Clock
     Blue   Ground
*/
#define kNumberOfLights (42)        // # lights in the strand

/* pin configuration on Arduino */
#define kWS2801_Data  (12)    // data line (white wire)
#define kWS2801_Clock (11)    // clock line (green wire)


#define kKnobA (A2)     // Duration / update interval
#define kKnobB (A3)     // Brightness

#define kButtonA  (A1)  // previous sequence
#define kButtonB  (A0)  // next sequence
#define kButtonC  (A4)  // tap-tempo
#define kButtonD  (A5)  // flash/accent


////////////////////////////////////////////////////////////////

class Button {
  protected:
    int pin;
    bool isPressing;
    bool wasPressed;
    bool wasStarted;
    unsigned long nextWait;
    unsigned long startTime;
    
  public:
    Button( int _pin );
    ~Button();

  public:
    void Poll( void );
    bool WasStarted( void );
    bool WasPressed( void );
    bool IsPressing( void ) { return this->isPressing; }
    unsigned long StartTime( void ) { return this->startTime; }
};

#define kTempoCt (8)

class TapTempo: public Button {
  private:
    unsigned long taps[ kTempoCt ];
    unsigned long previousStartTime;
    unsigned long lastGet = 0;
  
  public:
    TapTempo( int _pin );

  private:
    void AddNow();

  public:
    void Clear();
    void Dump();

  public:
    void Poll( void );
    unsigned long Get( void );
};

////////////////////////////////////////////////////////////////

class Settings {
  private:
    bool verified;
    void Initialize();
    void Verify();

  private:
    void Read_All();
    void SetDefaults();
    
  public:
    unsigned char s_pattern;
    
  public:
    Settings();
    ~Settings();

  public:
    // v1: no buffering.  direct io.
    unsigned char Get( unsigned char key );
    void Set( int key, unsigned char value );
};

// where in eeprom we store various setting.
#define kSetting_User     (5)
#define kSetting_Pattern  (kSetting_User + 0)



#endif
