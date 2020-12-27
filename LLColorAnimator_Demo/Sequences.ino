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
  LLCA_END  // end of the list sentinel
};


////////////////////////////////
// sequences

// these are just char strings where each frame is separated by a pipe |
// the end of the string signifies the end of the frame list, after a pipe |

const char seq_all_off[]            SEQLOC = "-|";
const char seq_yellow_4_marquee[]   SEQLOC = "Y---|-Y--|--Y-|---Y|";
const char seq_cyan_5_marquee[]     SEQLOC = "CC---|-CC--|--CC-|---CC|C---C|";
  

const char seq_phazer[]             SEQLOC = "z-YCBDD|";
const char seq_phazer2[]            SEQLOC = "z-WVBGYORM|";
  
const char seq_xmas_twinkle[]       SEQLOC = "RG|GR|";
const char seq_xmas_marquee[]       SEQLOC = "RG----|-RG---|--RG--|---RG-|----RG|G----R|";

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



const char * sequences[] = {
  seq_all_off,
  seq_rainbow,
  seq_color_flash,
  
  seq_yellow_4_marquee,
  seq_cyan_5_marquee,
  seq_expanding,
  seq_build_breakdown,
  
  seq_xmas_twinkle,
  seq_xmas_marquee,
  seq_fairy_traditional,
  seq_fairy_cycling,
  
  seq_fireworks,
  seq_jasper_catterpillar,
  
  seq_sensor_maze,
  
  seq_arctic_twilight,

  seq_crawler,
  seq_phazer,
  seq_phazer2,
  
  LLCA_END
};
