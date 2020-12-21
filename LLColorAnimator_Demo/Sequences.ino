

const char seq_all_off[]  =           "-|";
const char seq_yellow_4_marquee[]  =   "Y---|-Y--|--Y-|---Y|";
const char seq_cyan_5_marquee[]  =     "CC---|-CC--|--CC-|---CC|C---C|";
  
const char seq_cylon[]  =
  "R------|"
  "-R-----|"
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

const char seq_fireworks[]  =
  "-|"
  "W---------------|"
  /*
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
  "-|";
*/
;

  // expand from center
const char seq_expanding[]  = 
  "---R----|"
  "--RRR---|"
  "-RRRRR--|"
  "RRRRRRR-|"
  "RRR-RRRR|"
  "RR---RRR|"
  "R-----RR|"
  "-------R|"
  "-|";

 const char seq_build_breakdown[]  =
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

  const char seq_crawler[] = 
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
  

const char seq_jasper_catterpillar[]  =
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
 
  
const char seq_xmas_twinkle[] = "RG|GR|";
const char seq_xmas_marquee[] = "RG----|-RG---|--RG--|---RG-|----RG|G----R|";

const char seq_fairy_traditional[]  = "GRPOB|";
const char seq_fairy_cycling[]      = "GRPOB|BGRPO|OBGRP|POBGR|RPOBG|";
const char seq_color_flash[]        = "R|O|Y|G|C|B|P|";
const char seq_rainbow[]            = "ROYGCBP|";
const char seq_sensor_maze[]        = "s-ROYGV|";

const char seq_arctic_twilight[]    = "aDW";


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
  
  LLCA_END
};

#ifdef NEVER
/*
  seq_fairy_cycling,
  seq_fairy_traditional,
  seq_sensor_maze,
  LLCA_END,
  
  // "frames" of the sequences have a transition character
  //  at the end of the color lists.
  //  xxx|yyy - jump cut right into Y
  //  xxx/yyy - cut to black, fade in Y
  //  xxx\yyy - fade out X to black, show Y
  //  xxx^yyy - dissolve X to Y
 
  // all off
  "-|",

  // 4-marquee
  "Y---|-Y--|--Y-|---Y|",
  
  // 5-cyan-marquee
  "CC---|-CC--|--CC-|---CC|C---C|",

  // Cylon(ish)
  "R------|"
  "-R-----|"
  "--R----|"
  "---R---|"
  "----R--|"
  "-----R-|"
  "------R|"
  "-----R-|"
  "----R--|"
  "---R---|"
  "--R----|"
  "-R-----|",

  // firework?
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
  "-|",

  // expand from center
  "---R----|"
  "--RRR---|"
  "-RRRRR--|"
  "RRRRRRR-|"
  "RRR-RRRR|"
  "RR---RRR|"
  "R-----RR|"
  "-------R|"
  "-|",
  
  // Build and break down
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
  "------RR|",
  
  // Jasper Catterpillar
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
  "B------G|",
  
  // xmas twinkle
  "RG|GR|",
  
  // xmas marquee
  "RG----|-RG---|--RG--|---RG-|----RG|G----R|",

  // traditional xmas
  "GRPOB|",
  
  // cycling traditional xmas
  "GRPOB|BGRPO|OBGRP|POBGR|RPOBG|",
  
  // flash colors
  "R|O|Y|G|C|B|P|",

  // full rainbow
  "ROYGCBP|",
  
  // Sensor Maze Rainbow (ish)
  /*
  "R--R--R--R--|"
  "-O-R--R--R--|"
  "-O--O-R--R--|"
  "-O--O--O-R--|"
  "-O--O--O--O-|"
  "--Y-O--O--O-|"
  "--Y--Y-O--O-|"
  "--Y--Y--Y-O-|"
  "G-Y--Y--Y--Y|"
  "G--G-Y--Y--Y|"
  "G--G--G-Y--Y|"
  "G--G--G--G-Y|"
  "-V-G--G--G--|"
  "-V--V-G--G--|"
  "-V--V--V-G--|"
  "-V--V--V--V-|"
  "--R-V--V--V-|"
  "--R--R-V--V-|"
  "--R--R--R-V-|"
  "R-R--R--R---|",
  "

  
  "s-ROYGV|",  // Sensor Tunnel Cycling

  // Arctic Twilight
  //"aDW|R|C|RG|",
  // animation starts with 'a': Arctic Twilight mode using the following two colors

  
  /* demo examples:
  // rnd sizes
  "CR|ROYGBP|W--|",
  

  LLCA_END // end of list sentinel
};
*/
#endif
