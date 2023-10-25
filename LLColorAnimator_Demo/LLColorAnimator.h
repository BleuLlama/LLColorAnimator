
#ifndef __LLCOLORANIMATOR_H__
#define __LLCOLORANIMATOR_H__

#define LLCA_END 0

#define LLCA_COLOR( X, R, G, B ) \
  ( ((uint32_t)(X) << 24 )\
  | ((uint32_t)(R) << 16 )\
  | ((uint32_t)(G) <<  8 )\
  | ((uint32_t)(B)       )\
  )

#define COLOR( R, G, B )\
  LLCA_COLOR( 0, (R), (G), (B) )


#define LLCA_COLOR_ID( C )  (char)( ((C)>>24) & 0x00000FF )
#define LLCA_COLOR_C( C )   (uint32_t)(  (C)      & 0x0FFFFFF )
#define LLCA_COLOR_R( C )   (uint8_t)( ((C)>>16) & 0x00000FF )
#define LLCA_COLOR_G( C )   (uint8_t)( ((C)>> 8) & 0x00000FF )
#define LLCA_COLOR_B( C )   (uint8_t)(  (C)      & 0x00000FF )

#define kMaxFrameSize (16)

// frame render types
#define kMode_Frames         ('f')  // "RGB|ABC|"

#define kMode_Pattern        ('p')  // "RGB|"  or "pRGB"
#define kMode_ArcticTwilight ('a')  // "aBW|"
#define kMode_SensorMaze     ('s')  // "sROYGV|"
#define kMode_Phazer         ('z')  // "zWCCB|"
#define kMode_RandomFade     ('f')  // "fRGB"

class LLColorAnimator {
  // data
  private:
  const uint32_t * palette;
  const char ** sequences;

  uint8_t animationMode;

  // animation variables
  unsigned long startTime;
  
  uint32_t durationA;
  uint32_t durationB;

  float brightness;

  int animVal;
  int animRange;

  const char * currSequence;
  int nSequences;
  int currSequenceNo;
  const char * currFrame;
  uint16_t frameSize;

  uint16_t frameTick;
  
  uint32_t currColors[kMaxFrameSize];
  //unsigned int nextColors[kMaxFrameSize]; // future-- for dissolve fades?

  public:
    LLColorAnimator( const uint32_t * userPalette, const char ** userSequences );
    ~LLColorAnimator();

    void Dump( void );

    void DurationA( uint32_t v ) { this->durationA = v; }
    void DurationB( uint32_t v ) { this->durationB = v; }
    void Brightness( float v ) { this->brightness = v; }
    void AnimRange( int v ) { this->animRange = v; }
    
  private:
    void ColorsProcess( void );

  public:
    int SequenceSet( int seqNo );
    int SequenceNext( void );
    int SequencePrev( void );

  private:
    void FrameLoad( void );
    void FrameNext( void );

  public:
    void Update( void );
    uint32_t GetColor( int pos );
};

#endif
