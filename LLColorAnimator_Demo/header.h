

#ifndef __HEADER_H__
#define __HEADER_H__

/*****************************************************************************
   Standard librarires, misc
*/
#include <avr/pgmspace.h>

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

#define kSetting_User     (5)
#define kSetting_Pattern  (kSetting_User + 0)



#endif
