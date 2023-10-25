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
const char seq_color_flash[]        SEQLOC = "R|O|Y|G|C|B|P|";
const char seq_rainbow[]            SEQLOC = "ROYGCBP|";
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


const char seq_dickens1[]        SEQLOC =  "YY00|YO00|YO00|OO00|0Y00|YO00|OY00|";
//"0OOY|JKLY|KLYJ|L0JK|YJKL|JK0O|KLYJ|LYJK|";


const char * sequences[] = {
  seq_all_off,
  seq_rainbow,
  seq_color_flash,
  
  seq_yellow_4_marquee,
  seq_yellow_purple_marquee,
  seq_cyan_5_marquee,
  seq_expanding,
  seq_build_breakdown,
  
  seq_xmas_twinkle,
  seq_xmas_marquee,
  seq_xmas_marquee1,
  seq_xmas_marquee2,
  seq_xmas_marquee3,
  seq_jasper_catterpillarXMAS,
  seq_jasper_catterpillarXMAS2,
  seq_phazerxmas,
  seq_fairy_traditional,
  seq_fairy_cycling,
  
  seq_fireworks,
  seq_jasper_catterpillar,
  
  seq_sensor_maze,
  
  seq_arctic_twilight,

  seq_crawler, // colors crawl and change
  
  seq_phazer,  
  seq_phazer2,
  
  seq_dickens1,
  
  LLCA_END
};
