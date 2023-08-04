#ifndef CORE_X16H
#define CORE_X16H

#define POKE(addr,val)     (*(unsigned char*) (addr) = (val))
#define POKEW(addr,val)    (*(unsigned*) (addr) = (val))
#define PEEK(addr)         (*(unsigned char*) (addr))
#define PEEKW(addr)        (*(unsigned*) (addr))

#define CX16_BG_BLACK	   0x00
#define CX16_BG_WHITE	   0x10
#define CX16_BG_RED 	   0x20
#define CX16_BG_CYAN 	   0x30
#define CX16_BG_PURPLE   0x40
#define CX16_BG_GREEN    0x50
#define CX16_BG_BLUE	   0x60
#define CX16_BG_YELLOW   0x70
#define CX16_BG_ORANGE   0x80
#define CX16_BG_BROWN    0x90
#define CX16_BG_LT_RED   0xA0
#define CX16_BG_DK_GRAY  0xB0
#define CX16_BG_LT_GRAY  0xC0
#define CX16_BG_LT_GREEN 0xD0
#define CX16_BG_LT_BLUE  0xE0
#define CX16_BG_MED_GRAY 0xF0

#define CX16_FG_BLACK	   0x00
#define CX16_FG_WHITE	   0x01
#define CX16_FG_RED 	   0x02
#define CX16_FG_CYAN 	   0x03
#define CX16_FG_PURPLE   0x04
#define CX16_FG_GREEN    0x05
#define CX16_FG_BLUE	   0x06
#define CX16_FG_YELLOW   0x07
#define CX16_FG_ORANGE   0x08
#define CX16_FG_BROWN    0x09
#define CX16_FG_LT_RED   0x0A
#define CX16_FG_DK_GRAY  0x0B
#define CX16_FG_LT_GRAY  0x0C
#define CX16_FG_LT_GREEN 0x0D
#define CX16_FG_LT_BLUE  0x0E
#define CX16_FG_MED_GRAY 0x0F

#define CX16_KEY_MOD_SHIFT   1
#define CX16_KEY_MOD_ALT     2
#define CX16_KEY_MOD_CTRL    4
#define CX16_KEY_MOD_CAPS   16  // caps lock on

// "mode 2" characters (as output to screen)
#define CX16_M2_CHAR_SPACE  32  // blank space
#define CX16_M2_CHAR_DASH   64  // - symbol
#define CX16_M2_CHAR_UPPER_BAR  120
#define CX16_M2_CHAR_AT      0  // @ symbol
#define CX16_M2_CHAR_COLON  58  // ; symbol
#define CX16_M2_CHAR_A       1  // lower case
#define CX16_M2_CHAR_B       2
#define CX16_M2_CHAR_C       3
#define CX16_M2_CHAR_D       4
#define CX16_M2_CHAR_E       5
#define CX16_M2_CHAR_F       6
#define CX16_M2_CHAR_G       7
#define CX16_M2_CHAR_H       8
#define CX16_M2_CHAR_I       9
#define CX16_M2_CHAR_J      10
#define CX16_M2_CHAR_K      11
#define CX16_M2_CHAR_L      12
#define CX16_M2_CHAR_M      13
#define CX16_M2_CHAR_N      14
#define CX16_M2_CHAR_O      15
#define CX16_M2_CHAR_P      16
#define CX16_M2_CHAR_Q      17
#define CX16_M2_CHAR_R      18
#define CX16_M2_CHAR_S      19
#define CX16_M2_CHAR_T      20
#define CX16_M2_CHAR_U      21
#define CX16_M2_CHAR_V      22
#define CX16_M2_CHAR_W      23
#define CX16_M2_CHAR_X      24
#define CX16_M2_CHAR_Y      25
#define CX16_M2_CHAR_Z      26
#define CX16_M2_CHAR_0      48
#define CX16_M2_CHAR_1      49
#define CX16_M2_CHAR_2      50
#define CX16_M2_CHAR_3      51
#define CX16_M2_CHAR_4      52
#define CX16_M2_CHAR_5      53
#define CX16_M2_CHAR_6      54
#define CX16_M2_CHAR_7      55
#define CX16_M2_CHAR_8      56
#define CX16_M2_CHAR_9      57

#define CX16_KEY_ALT_A      176
#define CX16_KEY_ALT_B      191
#define CX16_KEY_ALT_C      188
#define CX16_KEY_ALT_D      172
#define CX16_KEY_ALT_E      177
#define CX16_KEY_ALT_F      187
#define CX16_KEY_ALT_G      165
#define CX16_KEY_ALT_H      180
#define CX16_KEY_ALT_I      162
#define CX16_KEY_ALT_J      181
#define CX16_KEY_ALT_K      161
#define CX16_KEY_ALT_L      182
#define CX16_KEY_ALT_M      167
#define CX16_KEY_ALT_N      170
#define CX16_KEY_ALT_O      185
#define CX16_KEY_ALT_P      175
#define CX16_KEY_ALT_Q      171
#define CX16_KEY_ALT_R      178
#define CX16_KEY_ALT_S      174
#define CX16_KEY_ALT_T      163
#define CX16_KEY_ALT_U      184
#define CX16_KEY_ALT_V      190
#define CX16_KEY_ALT_W      179
#define CX16_KEY_ALT_X      189
#define CX16_KEY_ALT_Y      183
#define CX16_KEY_ALT_Z      173

#define CX16_KEY_ALT_0      0     // undefined
#define CX16_KEY_ALT_1      129
#define CX16_KEY_ALT_2      149
#define CX16_KEY_ALT_3      150
#define CX16_KEY_ALT_4      151
#define CX16_KEY_ALT_5      152
#define CX16_KEY_ALT_6      153
#define CX16_KEY_ALT_7      154
#define CX16_KEY_ALT_8      155
#define CX16_KEY_ALT_9      0     // undefined!

#define CX16_KEY_F1         133
#define CX16_KEY_F2         137
#define CX16_KEY_F3         134
#define CX16_KEY_F4         138
#define CX16_KEY_F5         135
#define CX16_KEY_F6         139
#define CX16_KEY_F7         136
#define CX16_KEY_F8         140
#define CX16_KEY_F9         141   // also change language in emulator
#define CX16_KEY_F10        21
#define CX16_KEY_F11        22
#define CX16_KEY_F12        23

#define CX16_KEY_ARROW_LEFT 157
#define CX16_KEY_ARROW_RIGHT 29
#define CX16_KEY_ARROW_UP   145
#define CX16_KEY_ARROW_DOWN 17

#define CX16_KEY_INSERT     148
#define CX16_KEY_DELETE     25
#define CX16_KEY_HOME       19
#define CX16_KEY_END        4
#define CX16_KEY_PGUP       130
#define CX16_KEY_PGDN       2




// For default startup graphics mode...  640x480 with 8x8 font (80x60)
static unsigned char screen_row_offset[] = {
0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,
0xBA,0xBB,0xBC,0xBD,0xBE,0xBF,0xC0,0xC1,0xC2,0xC3,
0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,
0xCE,0xCF,0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,
0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF,0xE0,0xE1,
0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB
};

static unsigned char ascii_to_x16[] = {             // 0123456789
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  //             0   - 9
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  //             10  - 19
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  //             20
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  //   _!"#$%&'  30
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  48,  49,  // ()*+,-./01  40
  50,  51,  52,  53,  54,  55,  56,  57,0x00,0x00,  // 23456789:;  50
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  // <=>?@ABCDE  60
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  // FGHIJKLMNO  70
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  // PQRSTUVWXY  80
0x00,0x00,0x00,0x00,0x00,0x00,0x00,   1,   2,   3,  // Z[\]^_`abc  90
   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  // defghijklm  100
  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,  // nopqrstuvw  110
  24,  25,  26,   0,   0,   0,   0,   0,   0,0x00,  // xyz         120
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  //             130
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  //             140
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  //             150
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  //             160
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  //             170
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  //             180
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  //             190
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  //             200
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  //             210
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  //             220
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  //             230
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  //             240 - 249
0x00,0x00,0x00,0x00,0x00,0x00                       //             250 - 255
};


#define CX16_WRITE_XY(x, y, disp_out)   \
	POKE(0x9F20, x << 1);                 \
	POKE(0x9F21, screen_row_offset[y] );  \
	POKE(0x9F22, 0x21);                   \
	POKE(0x9F23, disp_out);

#define CX16_WRITE_X(x, disp_out)       \
	POKE(0x9F20, x << 1);                 \
	POKE(0x9F22, 0x21);                   \
	POKE(0x9F23, disp_out);               

#define CX16_WRITE_Y(y, disp_out)       \
	POKE(0x9F21, screen_row_offset[y] );  \
	POKE(0x9F22, 0x21);                   \
	POKE(0x9F23, disp_out);

#define CX16_WRITE(disp_out)            \
	POKE(0x9F22, 0x21);                   \
	POKE(0x9F23, disp_out);

// col_out = <background> | <foreground>
// example: CX16_COLOR_XY(10, 5, CX16_BG_BLACK | CX16_FG_WHITE);
#define CX16_COLOR_XY(x, y, col_out)    \
	POKE(0x9F20, (x << 1)+1);             \
	POKE(0x9F21, screen_row_offset[y] );  \
	POKE(0x9F22, 0x21);                   \
	POKE(0x9F23, col_out);

#define CX16_COLOR_X(x, col_out)        \
	POKE(0x9F20, (x << 1)+1);             \
	POKE(0x9F22, 0x21);                   \
	POKE(0x9F23, col_out);

#define CX16_COLOR_Y(y, col_out)        \
	POKE(0x9F21, screen_row_offset[y] );  \
	POKE(0x9F22, 0x21);                   \
	POKE(0x9F23, col_out);

#define CX16_COLOR(col_out)             \
	POKE(0x9F22, 0x21);                   \
	POKE(0x9F23, col_out);

// enable graphic mode #1
#define ENABLE_SCREEN_MODE_1  \
  __asm__("lda #$01");  \
	__asm__("clc");  \
  __asm__("jsr $ff5f");

// enable character set #1 (upper-case only and symbols)
#define ENABLE_TEXT_MODE_1  \
  __asm__("lda #$8E");  \
  __asm__("jsr $ffd2");

// MODE_2 has both lower and upper case characters and different symbols
#define ENABLE_TEXT_MODE_2  \
  __asm__("lda #$0E");  \
  __asm__("jsr $ffd2");

#define CLRSCR \
  __asm__("lda #$93"); \
  __asm__("jsr $ffd2");
		
// Returns the NUMBER OF KEYS currently buffered
// (does not return or extract the next buffered key)
unsigned char check_kbd()
{	
  static unsigned char keys;	

  __asm__("jsr $febd");  // kbdbuf_peek
  __asm__("txa");        // transfer RegX to RegA
  __asm__("sta     %v", keys);	// %o (local) or %v (global) [%o seems broken?]  [store RegA]
	
  return keys;	
}

unsigned char check_kbd_modifiers()
{
  static unsigned char modifiers;	
	
	/*
	modifiers  76543210
	              ^^^^^
								||||+- shift     (1)
								|||+-- alt       (2)
								||+--- ctrl      (4)
								|+---- logo      (8) like Windows key, or X16-key
								+----- caps lock (16)
	*/

  __asm__("jsr $fec0");  // kbdbuf_get_modifiers
  __asm__("sta     %v", modifiers);	  // %o (local) or %v (global) [%o seems broken?]  [store RegA]
	
  return modifiers;	
}

typedef struct {	
	unsigned char minutes;
	unsigned char seconds;
	unsigned char jiffies;
} CX16_clock_type;
extern CX16_clock_type cx16_clock;

void cx16_init_clock()
{
	__asm__("LDA #0");    // jiffies
	__asm__("LDX #$FF");  // seconds
	__asm__("LDY #$FF");  // minutes
	__asm__("JSR $FFDB");
}

void cx16_update_clock()
{
	static unsigned char reg_a;	
	static unsigned char reg_x;	
	static unsigned char reg_y;	
	
  __asm__("JSR $FFDE");
	__asm__("STA %v", reg_a);
	__asm__("STX %v", reg_x);
  __asm__("STY %v", reg_y);  
	
	cx16_clock.jiffies = reg_a;
	cx16_clock.seconds = reg_x;
	cx16_clock.minutes = reg_y;  	
}

/*
.... main example ...
  char ch, x, y;

  ch = 0;
  for (y = 0; y < 60; y += 2)
  {		
    CX16_WRITE_XY(0, y, ch);		  // write first character for this row
		
    for (x = 1; x < 80; ++x)
    {	
      ++ch;
      CX16_WRITE(ch);  // automatically write to the next column of the current row
    }
  }
*/

#endif
