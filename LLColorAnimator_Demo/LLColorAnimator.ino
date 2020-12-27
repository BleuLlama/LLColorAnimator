

#include <avr/pgmspace.h>
#include "LLColorAnimator.h"


// here's a macro we'll use to access the sequence data
// we do it this way since we can have sequences in 
// progmem (flash) or RAM, defineable at build time.

#ifdef SEQUENCES_IN_PROGMEM
  #define FRAMEP( I ) \
    (uint8_t) pgm_read_byte_near( this->currFrame + (I) )

#else
  #define FRAMEP( I ) \
    (uint8_t) this->currFrame[ (I) ]
    
#endif



LLColorAnimator::LLColorAnimator( const uint32_t * userPalette, const char * userSequences[] )
  : palette( userPalette )
  , sequences( userSequences )
  , animationMode( kMode_Frames )
  , startTime( 0L )
  , durationA( 500 )
  , durationB( 500 )
  , brightness( 1.0 )
  , animVal( 0 )
  , animRange( 0 )
  , nSequences( 0 )
  , currSequenceNo( 0 )
  , frameTick( 0 )
{
  // count the number of sequences
  int i = 0;
  for( i = 0; (this->sequences[ i ] != LLCA_END)  && (i<100) ; i++ );
  //Serial.println( i );
  this->nSequences = i;

  this->SequenceSet( 0 );
}

LLColorAnimator::~LLColorAnimator()
{
  // never called
}

void LLColorAnimator::Dump( void )
{
  Serial.println(  F( "LLColorAnimator Dump" ));

  Serial.println(  F( "Palette:" ));
  char buf[ 32 ];

  
  for( int i=0
      ; this->palette[i] != LLCA_END
      ; i++ )
  {
    sprintf( buf, "  %d:  '%c'  %3d %3d %3d", 
        i, 
        LLCA_COLOR_ID( this->palette[i] ), 
        LLCA_COLOR_R( this->palette[i] ),
        LLCA_COLOR_G( this->palette[i] ),
        LLCA_COLOR_B( this->palette[i] )
      );
    Serial.println( buf );
  }

/*
  Serial.println( F( "Sequences:" ));
  for( int i=0;
        this->sequences[i] != LLCA_END
        ;i++ )
  {
    sprintf( buf, "  %d:  ", i );
    Serial.print( buf );
    Serial.println( this->sequences[i] );
  }
  */
}


void LLColorAnimator::Update( void )
{
  if( millis() > this->startTime + this->durationA ) {
    
    if( this->animationMode == kMode_ArcticTwilight ) {
      this->animVal = random( 0, animRange ); // pixel that gets sparkly
      this->startTime = millis();
      
    } else {
      this->startTime = millis();
      this->FrameNext();
    }
  }
  /*
  char buf[32];
  sprintf( buf, "%ld  %ld  %d\n", millis(), this->startTime + this->durationA, this->animVal );
  Serial.print( buf );
  */
}


#define kAT_Duration (333)

// RYVOG
// ROYGB  
const unsigned char SensorRemap[] = { 2, 5, 3, 6, 4 };

uint32_t LLColorAnimator::GetColor( int pos )
{
  int ccidx = pos;
  int r,g,b;
  
  if( this->animationMode == kMode_SensorMaze ) {
    int idxp = (this->frameTick + (pos * 18)) % 55;   // position in the virtual "tape" of colors to roll through each light
    // each item is offset 18 positions over the previous, and is 55 items long.
    // each color segment is 11 items long, the first 4 elements are the color, the remaining 7 are black.

    if( ( idxp % 11 ) > 3 ) {
      ccidx = 1; // black.
    } else {
      ccidx = SensorRemap[ (int) floor( (float)idxp / 11.0 ) ];
      // remap to the colors in the list.
    }
     
  }

  else if( this->animationMode == kMode_Phazer ) {
    // "z-WCBD|";
    //  012345

    ccidx = 1;
    unsigned long zp = (this->frameTick + 50 - pos) % 30;

    if( zp < (this->frameSize-2)) {
      ccidx = zp + 2;
    }
  }
  
  else if( this->animationMode == kMode_ArcticTwilight ) {
    //Serial.println( this->animVal );
    if( pos == this->animVal ) {
      unsigned long  m = millis();
      if( m < this->startTime + kAT_Duration ){
        float td = (((float)this->startTime + (float)kAT_Duration) - m)/ (float)kAT_Duration;
        
        r = max( (int)(td * LLCA_COLOR_R( this->currColors[ 1 ] )), LLCA_COLOR_R( this->currColors[ 0 ] ) );
        g = max( (int)(td * LLCA_COLOR_G( this->currColors[ 1 ] )), LLCA_COLOR_G( this->currColors[ 0 ] ) );
        b = max( (int)(td * LLCA_COLOR_B( this->currColors[ 1 ] )), LLCA_COLOR_B( this->currColors[ 0 ] ) );
        
        return COLOR( r,g,b ); // foreground
      } else {
        ccidx = 0; // background
        
      }
    } 
    
    ccidx = 0; // background
  } else {
    ccidx = pos;
  }

  uint32_t c = this->currColors[ ccidx % this->frameSize ];

  r = (int) (this->brightness * (float)LLCA_COLOR_R( c ));
  g = (int) (this->brightness * (float)LLCA_COLOR_G( c ));
  b = (int) (this->brightness * (float)LLCA_COLOR_B( c ));

  return COLOR( r, g, b );
  //return LLCA_COLOR_C( this->currColors[ pos % this->frameSize ] ); 
}

int LLColorAnimator::SequenceSet( int seqNo )
{
  this->currSequenceNo = seqNo % this->nSequences;
  
  this->currSequence = this->sequences[ seqNo ];
  
  this->currFrame = this->currSequence;
  this->FrameLoad();
  this->startTime = millis();

  /*
  Serial.print( F( "Sequence " ));
  Serial.print( this->currSequenceNo );
  Serial.println( this->currSequence );
  */
  return this->currSequenceNo;
}

int LLColorAnimator::SequenceNext( void )
{
  if( this->currSequenceNo >= this->nSequences-1 ) {
    this->currSequenceNo = 0;
  } else {
    this->currSequenceNo = this->currSequenceNo+1;
  }
  return this->SequenceSet( this->currSequenceNo );
}

int LLColorAnimator::SequencePrev( void )
{
  if( this->currSequenceNo > 0 ) {
    return this->SequenceSet( currSequenceNo-1 );
  } else {
    return this->SequenceSet( this->nSequences-1 );
  }
}


// FrameLoad
//  load in the current sequence into the frame current colors.
void LLColorAnimator::FrameLoad( void )
{
  int offset = 0;
  
  if( FRAMEP( 0 ) == kMode_SensorMaze ) {
    this->animationMode = kMode_SensorMaze;
    offset = 1;
  }
  else if( FRAMEP( 0 ) == kMode_ArcticTwilight ) {
    this->animationMode = kMode_ArcticTwilight;
    offset = 1;
    
  } else if( FRAMEP( 0 ) == kMode_Phazer ) {
    this->animationMode = kMode_Phazer;
    offset = 1;
    
  } else {
    // frames but no character to say so
    this->animationMode = kMode_Frames;
    offset = 0;
  }

  // move check for frame render type in here
  for( int i=offset ;
           (i < kMaxFrameSize)
        && (FRAMEP( i ) != '|') 
        && (FRAMEP( i ) != '\0')
        ; i++ )
  {
    this->currColors[ i ] = 0L; // if not found, it'll be black
    for( int p=0
      ; this->palette[p] != LLCA_END
      ; p++ )
    {
      if( LLCA_COLOR_ID( this->palette[p] ) == FRAMEP( i ) ) {
        this->currColors[ i ] = LLCA_COLOR_C( this->palette[p] );
      }
    }


    //Serial.print( FRAMEP( i ) );
    
    this->frameSize = i;
  }
  this->frameSize++;

  
  ///Serial.println( this->frameSize);
}

// FrameNext
//  advance to the next frame in the animation sequene
void LLColorAnimator::FrameNext( void )
{
  int i = 0;

  while(     FRAMEP( i ) != '|' 
          && FRAMEP( i ) != '\0' )
  {
    i++;
  }
  
  if( FRAMEP( i ) == '|' ) {
    i++; // go to the next byte. (end of string)
  }

  if( FRAMEP( i ) == '\0' ) {
    // end of the frame list, loop around
    this->currFrame = this->currSequence;
  } else {
    this->currFrame = this->currFrame + i; // das pointermaths!
  }
  
  this->frameTick++;
  this->FrameLoad();
}
