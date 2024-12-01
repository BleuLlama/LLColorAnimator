/*  Sequences
 *   Here's where we store all of the frames of animation data.
 */


////////////////////////////////
// Palette

// These are the colors available to us for the sequences
const unsigned long palette[] = {
  // each entry is <character ID>, <R>, <G>, <B>
  LLCA_COLOR( 'W', 100, 192, 192 ), // white
  LLCA_COLOR( '-',   0,   0,   0 ), // black (off)
  LLCA_COLOR( 'R', 192,   0,   0 ), // red
  LLCA_COLOR( 'O', 100,  20,   0 ), // orange 
  LLCA_COLOR( 'Y', 192, 100,   0 ), // yellow
  LLCA_COLOR( 'G',   0, 192,   0 ), // green
  LLCA_COLOR( 'C',   0, 192,  80 ), // cyan
  LLCA_COLOR( 'B',   0,   0,  90 ), // blue
  LLCA_COLOR( 'P', 100,   0,  30 ), // purple
  
  LLCA_COLOR( 'V', 100,   0, 100 ), // violet
  
  LLCA_COLOR( 'D',   0,   0,   2 ), // dark blue
  LLCA_COLOR( 'M',   2,   0,   0 ), // dark red
  
  LLCA_COLOR( 'J', 192,  50,   0 ), // LTorange 
  LLCA_COLOR( 'K', 255,  30,   0 ), // LTorange 
  LLCA_COLOR( 'L', 255,  70,   0 ), // LTorange 
  LLCA_END  // end of the list sentinel
};


////////////////////////////////
// sequences

// these are just char strings where each frame is separated by a pipe |
// the end of the string signifies the end of the frame list, after a pipe |

// the first character can be a special pattern display identifier:
//  z - phaser.  the single frame moves down the entire line of lights
//  s - Sensor Maze tunnel style,  colors roll down the line
//  a - arctic twilight - dim colors defined as color[0], one pops bright to color [1]
//  m - arcade machine simulation
//  c - candles!
//  h - haunted display

const char seq_all_off[]            SEQLOC = "-|";
const char seq_yellow_4_marquee[]   SEQLOC = "Y---|-Y--|--Y-|---Y|";
const char seq_yellow_purple_marquee[]   SEQLOC = 
  "O---P---|"
  "-O---P--|"
  "--O---P-|"
  "---O---P|"
  "P---O---|"
  "-P---O--|"
  "--P---O-|"
  "---P---O|";
const char seq_cyan_5_marquee[]     SEQLOC = "CC---|-CC--|--CC-|---CC|C---C|";
  
// group of colors, flowing down the whole line
const char seq_phazer[]             SEQLOC = "z-YCBDD|";
const char seq_phazer2[]            SEQLOC = "z-WVBGYORM|";
const char seq_phazerxmas[]         SEQLOC = "z-GGYRRM|";

const char seq_xmas_twinkle[]       SEQLOC = "RG|GR|";
const char seq_xmas_marquee[]       SEQLOC = "RG----|-RG---|--RG--|---RG-|----RG|G----R|";
const char seq_xmas_marquee1[]       SEQLOC = "R---G---|-R---G--|--R---G-|---R---G|G---R---|-G---R--|--G---R-|---G---R|";
const char seq_xmas_marquee2[]       SEQLOC = "RGGG|GRGG|GGRG|GGGR|";
const char seq_xmas_marquee3[]       SEQLOC = "GRRR|RGRR|RRGR|RRRG|";

const char seq_fairy_traditional[]  SEQLOC = "GRPOB|";
const char seq_fairy_cycling[]      SEQLOC = "GRPOB|BGRPO|OBGRP|POBGR|RPOBG|";

const char seq_fairy_four[]         SEQLOC = "GRBY|";
const char seq_fairy_four_cycling[] SEQLOC = "GRBY|YGRB|BYGR|RBYG|";

const char seq_color_flash[]        SEQLOC = "R|O|Y|G|C|B|P|";
const char seq_rainbow[]            SEQLOC = "ROYGCBP|OYGCBPR|YGCBPRO|GCBPROY|CBPROYG|BPROYGC|PROYGCB|";
const char seq_sensor_maze[]        SEQLOC = "s-ROYGV|";

const char seq_arctic_twilight[]    SEQLOC = "aDW|";

const char seq_fireworks[] SEQLOC =
  "-|"
  "W---------------|"
  "YW--------------|"
  "-YW-------------|"
  "--YW------------|"
  "---YW-----------|"
  "----YW----------|"
  "-----YW---------|"
  "------YW--------|"
  "-------W--------|"
  "------WCW-------|"
  "-----RYBYR------|"
  "----RYB-BYR-----|"
  "---ROG---GOR----|"
  "---RR-----RR----|"
  "---O-------O----|"
  "--O---------O---|"
  "-|";               // frames can be different lengths, this one fills with <off>


const char seq_cylon[] SEQLOC =
  "R------|" // the compiler will assemble these into one big string
  "-R-----|" // if we don't add commas after each of these. Fun fact!
  "--R----|"
  "---R---|"
  "----R--|"
  "-----R-|"
  "------R|"
  "-----R-|"
  "----R--|"
  "---R---|"
  "--R----|"
  "-R-----|";

  // expand from center
const char seq_expanding[] SEQLOC = 
  "---R----|"
  "--RRR---|"
  "-RRRRR--|"
  "RRRRRRR-|"
  "RRR-RRRR|"
  "RR---RRR|"
  "R-----RR|"
  "-------R|"
  "-|";

 const char seq_build_breakdown[] SEQLOC  =
  "R------R|"
  "RR------|"
  "RRR-----|"
  "RRRR----|"
  "RRRRR---|"
  "RRRRRR--|"
  "RRRRRRR-|"
  "RRRRRRRR|"
  "-RRRRRRR|"
  "--RRRRRR|"
  "---RRRRR|"
  "----RRRR|"
  "-----RRR|"
  "------RR|";

  const char seq_crawler[] SEQLOC = 
  "Y-----------|"
  "O-----------|"
  "O-----------|"
  "R-----------|"
  "RR----------|"
  "RRR---------|"
  "RRRR--------|"
  "RRRRR-------|"
  "RRRRR-------|"
  "-RRRR-------|"
  "--RRR-------|"
  "---RR-------|"
  "----R-------|"
  "----O-------|"
  "----O-------|"
  "----Y-------|"
  "----YY------|"
  "----YYY-----|"
  "----YYYY----|"
  "----YYYYY---|"
  "----YYYYY---|"
  "-----YYYY---|"
  "------YYY---|"
  "-------YY---|"
  "--------Y---|"
  "--------Y---|"
  "--------G---|"
  "--------G---|"
  "--------GG--|"
  "--------GGG-|"
  "--------GGGG|"
  "G-------GGGG|"
  "G-------GGGG|"
  "G-------GGGG|"
  "G--------GGG|"
  "G---------GG|"
  "G=---------G|"
  ;
  

const char seq_jasper_catterpillar[] SEQLOC =
  "B-------|"
  "GB------|"
  "GGB-----|"
  "GGGB----|"
  "GGGGB---|"
  "GGGGGB--|"
  "GGGGGGB-|"
  "GGGGGGGB|"
  "BGGGGGGG|"
  "B-GGGGGG|"
  "B--GGGGG|"
  "B---GGGG|"
  "B----GGG|"
  "B-----GG|"
  "B------G|";
  
const char seq_jasper_catterpillarXMAS[] SEQLOC =
  "R-------|"
  "GR------|"
  "GGR-----|"
  "GGGR----|"
  "GGGGR---|"
  "GGGGGR--|"
  "GGGGGGR-|"
  "GGGGGGGR|"
  "RGGGGGGG|"
  "R-GGGGGG|"
  "R--GGGGG|"
  "R---GGGG|"
  "R----GGG|"
  "R-----GG|"
  "R------G|";
  
const char seq_jasper_catterpillarXMAS2[] SEQLOC =
  "G-------|"
  "GR------|"
  "GGR-----|"
  "GGGR----|"
  "GGGGR---|"
  "GGGGGR--|"
  "GGGGGGR-|"
  "GGGGGGGR|"
  "RGGGGGGG|"
  "R-GGGGGG|"
  "R--GGGGG|"
  "R---GGGG|"
  "R----GGG|"
  "R-----GG|"
  "R------G|"
  "R-------|"
  "RG------|"
  "RRG-----|"
  "RRRG----|"
  "RRRRG---|"
  "RRRRRG--|"
  "RRRRRRG-|"
  "RRRRRRRG|"
  "GRRRRRRR|"
  "G-RRRRRR|"
  "G--RRRRR|"
  "G---RRRR|"
  "G----RRR|"
  "G-----RR|"
  "G------R|"
  ;
const char seq_catterpillarXMAS3[] SEQLOC =
  "G-----|"
  "GR----|"
  "GGR---|"
  "GGGR--|"
  "-GGR--|"
  "--GR--|"
  "---R--|"
  "---RG-|"
  "---RRG|"
  "G--RRR|"
  "G---RR|"
  "G----R|"
  ;


/*

const char seq_catterpillarXMAS4[] SEQLOC =
  // Really a marquee.
  "GGG-RRR---|"
  "--GGG-RRR-|"
  "---GGG-RRR|"
  "R---GGG-RR|"
  "RR---GGG-R|"
  "RRR---GGG-|"
  "-RRR---GGG|"
  "G-RRR---GG|"
  "GG-RRR---G|"
;
*/

const char seq_catterpillarXMAS4[] SEQLOC =
  "GGG--RRR--|"
  "-GG---RR--|"
  "-GGG--RRR-|"
  "--GG---RR-|"
  "--GGG--RRR|"
  "---GG---RR|"
  "R--GGG--RR|"
  "R---GG---R|"
  "RR--GGG--R|"
  "RR---GG---|"
  
  "RRR--GGG--|"
  "-RR---GG--|"
  "-RRR--GGG-|"
  "--RR---GG-|"
  "--RRR--GGG|"
  "---RR---GG|"
  "G--RRR--GG|"
  "G---RR---G|"
  "GG--RRR--G|"
  "GG---RR---|"
  "GGG--RRR--|"
  ;

const char seq_xmas_xcross[] SEQLOC = 
  "RR-----GG-|"
  "-RR---GG--|"
  "--RR-GG---|"
  "---RYG----|"
  "---GYR----|"
  "--GG-RR---|"
  "-GG---RR--|"
  "GG-----RR-|"
  "G-------RY|"
  "R-------GY|"
  ;
  

const char seq_arcade[]  SEQLOC = "m"; // special case for arcade machine
const char seq_candles[]  SEQLOC = "c"; // special case for candle use
const char seq_lightning[]  SEQLOC = "l"; // special case for lightning use
const char seq_haunt[]  SEQLOC = "h"; // special case for haunted display use

const char * seq_names[] = {
  "Off",
  "Rainbo",
  "C.flash",
  "Y4 mrq",
  "YP mrq",
  "C5 mrq",
  "expand",
  "bld.bkd",

  "xmas.Tw",
  "xmas.M0",
  "xmas.M1",
  "xmas.M2",
  "xmas.M3",
  
  "x.Cat 1",
  "x.Cat 2",
  "x.Cat 3",
  "x.Cat 4",
  "x.Phasr",
  "G>> <<R",
  "Fairy.t",
  "Fairy.c",
  "Fairy.4",
  "Fairy4C"
  "sensor",
  "cndle.1",
  "lghtng",

#ifndef kLowMemory
  "Firwork",
  "catter",
  "crawlr",
  "phasr1",
  "phasr2",
  "arcade",
  "haunt",
  //"arctic",
#endif
};

const char * getSeqName( int idx ) 
{
  return seq_names[ idx ];
}

const char * sequences[] = {
  seq_all_off,      // 0
  seq_rainbow,      // 1
  seq_color_flash,  // 2
  
  seq_yellow_4_marquee,     // 3
  seq_yellow_purple_marquee,
  seq_cyan_5_marquee,
  seq_expanding,
  seq_build_breakdown,
  
  seq_xmas_twinkle,   // 8
  seq_xmas_marquee,
  seq_xmas_marquee1,
  seq_xmas_marquee2,
  seq_xmas_marquee3,
  
  seq_jasper_catterpillarXMAS,
  seq_jasper_catterpillarXMAS2,
  seq_catterpillarXMAS3, // 15
  seq_catterpillarXMAS4, // 16
  seq_phazerxmas,
  seq_xmas_xcross, // 18
  seq_fairy_traditional,
  seq_fairy_cycling,
  seq_fairy_four,
  seq_fairy_four_cycling,

  seq_sensor_maze,    // 21
  seq_candles,  // 22
  seq_lightning,  // 23 // "lDW|";
  
#ifndef kLowMemory
  seq_fireworks,          // 24
  seq_jasper_catterpillar,

  seq_crawler, //  colors crawl and change
  
  seq_phazer,   //  blast
  seq_phazer2,  // rainbow blast
  
  seq_arcade,   //
  seq_haunt,     // 31 haunted display 

  //seq_arctic_twilight,  // 26 *revisit* // "aDW|";
#endif
  LLCA_END
};
