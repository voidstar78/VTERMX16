//#include <stdarg.h>          //< va_list, va_start, va_arg
//#include <string.h>          //< memcpy, memset, strlen
#include <stdlib.h>          //< Used for itoa, srand and exit
//#include <stdio.h>         //< printf - consumes a lot of code space
#include <conio.h>           //< cgetc
#include <cx16.h>

// TOOLS SUPPORT LIBRARY (could be useful across many applications)
#include <core_x16.h>

#define TRUE  1
#define FALSE 0

#define CURSOR_SYMBOL_INDEX_MAX 3
#define CURSOR_COLOR_INDEX_MAX 6
unsigned char cursor_symbols[] =
{
	227, 225, 226, 97
};
unsigned char cursor_colors[] =
{
	// ROY G BIV	
	CX16_BG_RED,     
	CX16_BG_ORANGE, 
	CX16_BG_YELLOW,
	CX16_BG_GREEN,
	CX16_BG_BLUE,
	CX16_BG_LT_BLUE,
	CX16_BG_PURPLE
};

#define BAUD_RATE_INDEX_MAX 10
unsigned long baud_rates[] =
{  // L for "unsigned long type"
	    50UL,  // 0
	   110UL,  // 1
	   300UL,  // 2
	  1200UL,  // 3
	  2400UL,  // 4
	  4800UL,  // 5
	  9600UL,  // 6
	 19200UL,  // 7
	 38400UL,  // 8
	 57600UL,  // 9
	115200UL   // 10
};

typedef struct 
{
	unsigned char curr_width;   // emulated terminal width (max. 255)
	unsigned char curr_height;  // emulated terminal height (max. 255)
	
	unsigned char curr_x;  // cursor location x (across col)
	unsigned char curr_y;  // cursor location y (vertical row)
	
	unsigned char curr_cursor_symbol_index;
	unsigned char curr_cursor_color_index;
	
	unsigned char mode_bits;    // 8
	unsigned char mode_parity;  // N
	unsigned char mode_stop;    // 1
	
	unsigned char curr_baud_rate_index;
	
} Terminal_configuration;
Terminal_configuration global_terminal_configuration;

CX16_clock_type cx16_clock;

/*

BAUD NEWLINE:xx FGCOLOR:xx BGCOLOR:xx LOG:off

    SETTINGS
		  DATA BITS        8|7
			PARITY           E|O|N   None Even Odd None
			STOP BITS        1|2
			BAUD             50|300|1200|2400|4800
		  NEWLINE AT       16|32|40|64|80
			FG_COLOR
			BG_COLOR
			
		COLORS     FG  BG
*/

void print_xy_ulong_as_decimal(unsigned char x, unsigned char y, unsigned long value, char color, unsigned char left_pad)
{
	unsigned char b_index;  // buffer index
	unsigned char str_len;
	char buffer[20];
	char ch;
	unsigned char i;
	unsigned char target_x;
	
	ltoa(value, buffer, 10);  // buffer will be null terminated \0    base-10 (10 == decimal)
	
	if (left_pad > 0)
	{
		str_len = 0;
		while (TRUE)
		{
			ch = buffer[str_len];
			if (buffer[str_len] == '\0')
			{
				break;  // found the null terminator, break out of the loop
			}
			++str_len;
		}
		
		// str_len is now the LENGTH of the string
		if (left_pad >= str_len)
		{
		  ch = (left_pad - str_len);		  
		  for (i = 0; i < ch; ++i)  // write the remaining left pads
		  {
				CX16_WRITE_XY(x, y, CX16_M2_CHAR_SPACE);
				CX16_COLOR_XY(x, y, color);		
				++x;
		  }
			goto full_output;
		}
		else
		{
			// the length of the "value" is longer than the pad, just output the full value
			goto full_output;
		}
	}
	else
	{
full_output:		
		b_index = 0;
		while (TRUE)
		{
			ch = buffer[b_index];

			target_x = x+b_index;
			CX16_WRITE_XY(target_x, y, ch);  //ascii_to_x16[i2]);  
			// because ASCII and X16 intersect on '0' to '9', no extra lookup is needed for numbers
			
			CX16_COLOR_XY(target_x, y, color);		
			
			++b_index;
			if (buffer[b_index] == '\0')
			{
				break;  // found the null terminator, break out of the loop
			}
			
			if (b_index > 18)  // safety margin
			{
				break;
			}
		}	
	}
}

void set_background(unsigned char bg_color)
{
	int x;
	int y;
	for (x = 0; x < global_terminal_configuration.curr_width; ++x)
	{
		for (y = 0; y < global_terminal_configuration.curr_width; ++y)
		{
			CX16_COLOR_XY(x, y, bg_color);
		}
	}
}

void draw_main_screen_overlay()
{
	/*
	80x25  terminal screen
	26 ==========================================  row 26
	27
	28
	29
	30
	31
	32
	33
	34
	35 ======================================
	36                    
	37                    
	38                    
	39                    
	40                    
	41
	*/
	
	unsigned char i;	
	unsigned long baud_rate;
	
	for (i = 0; i < global_terminal_configuration.curr_width; ++i)
	{
		CX16_WRITE_XY(i, 25, CX16_M2_CHAR_UPPER_BAR);		
		CX16_COLOR_XY(i, 25, CX16_BG_BLACK | CX16_FG_WHITE);
	}	

	CX16_WRITE_XY(0, 26, CX16_M2_CHAR_M + 64);  // +64 to make upper case
	CX16_WRITE(CX16_M2_CHAR_O + 64);
	CX16_WRITE(CX16_M2_CHAR_D + 64);
	CX16_WRITE(CX16_M2_CHAR_E + 64);
	CX16_WRITE(CX16_M2_CHAR_COLON);
	
	CX16_COLOR_XY(0, 26, CX16_BG_BLACK | CX16_FG_WHITE);
	CX16_COLOR(CX16_BG_BLACK | CX16_FG_WHITE);
	CX16_COLOR(CX16_BG_BLACK | CX16_FG_WHITE);
	CX16_COLOR(CX16_BG_BLACK | CX16_FG_WHITE);
	CX16_COLOR(CX16_BG_BLACK | CX16_FG_WHITE);
	
	CX16_WRITE_XY(5, 26, global_terminal_configuration.mode_bits + CX16_M2_CHAR_0); 
	CX16_COLOR_XY(5, 26, CX16_BG_BLACK | CX16_FG_YELLOW);
	
	CX16_WRITE_XY(7, 26, global_terminal_configuration.mode_parity); 
	CX16_COLOR_XY(7, 26, CX16_BG_BLACK | CX16_FG_YELLOW);
	
	CX16_WRITE_XY(9, 26, global_terminal_configuration.mode_stop + CX16_M2_CHAR_0); 
	CX16_COLOR_XY(9, 26, CX16_BG_BLACK | CX16_FG_YELLOW);
	
	CX16_WRITE_XY(11, 26, CX16_M2_CHAR_B + 64);
	CX16_WRITE(CX16_M2_CHAR_A + 64);
	CX16_WRITE(CX16_M2_CHAR_U + 64);
	CX16_WRITE(CX16_M2_CHAR_D + 64);
	CX16_WRITE(CX16_M2_CHAR_COLON);
	
	CX16_COLOR_XY(11, 26, CX16_BG_BLACK | CX16_FG_WHITE);
	CX16_COLOR(CX16_BG_BLACK | CX16_FG_WHITE);
	CX16_COLOR(CX16_BG_BLACK | CX16_FG_WHITE);
	CX16_COLOR(CX16_BG_BLACK | CX16_FG_WHITE);
	CX16_COLOR(CX16_BG_BLACK | CX16_FG_WHITE);	
	
/*
012345678901234567890
MODE: 8-N-1 BAUD: 115200
*/	
  // Clear out the current baud rate			
	baud_rate = baud_rates[global_terminal_configuration.curr_baud_rate_index];
	print_xy_ulong_as_decimal(16, 26, baud_rate, CX16_BG_BLACK | CX16_FG_YELLOW, 6);
	
}

void main(void)
{
	unsigned char valid_key;
	unsigned char ch;
	unsigned char ch_modifier;
	
	//unsigned int a, b, c, d;
	
	global_terminal_configuration.curr_width = 80;
	global_terminal_configuration.curr_height = 25;
	
	global_terminal_configuration.curr_x = 0;
	global_terminal_configuration.curr_y = 0;
	
	global_terminal_configuration.mode_bits = 8;
	global_terminal_configuration.mode_parity = 78;  // 78 == 'N' NONE
	global_terminal_configuration.mode_stop = 1;
	
	global_terminal_configuration.curr_baud_rate_index = 10;
	
	cx16_init_clock();
	
	ENABLE_SCREEN_MODE_1;
	  
	CLRSCR;  // necessary to clear out X16 initial startup logo
	set_background(CX16_BG_BLACK);	
		
	ENABLE_TEXT_MODE_2;  // want lower case support in terminal output	
	
	draw_main_screen_overlay();
	
	while (TRUE)
	{
		cx16_update_clock();
		
/*
          1         2         3         4         5         6         7         8  
0123456789012345678901234567890123456789
                                        0123456789012345678901234567890123456789
																				123 16    123 04 29 15 34 12 255
																				          1234567890123456789012
*/		
		// DISPLAY CLOCK TIME
		{
			print_xy_ulong_as_decimal(69,26,  cx16_clock.minutes, CX16_BG_BLACK | CX16_FG_CYAN, 3);
			print_xy_ulong_as_decimal(73,26,  cx16_clock.seconds, CX16_BG_BLACK | CX16_FG_CYAN, 3);
			print_xy_ulong_as_decimal(77,26,  cx16_clock.jiffies, CX16_BG_BLACK | CX16_FG_CYAN, 3);
		}						
		
		
		// DRAW THE SYMBOL AND COLOR OF THE CURRENT-POSITION CURSOR
		CX16_WRITE_XY(
		  global_terminal_configuration.curr_x, 
			global_terminal_configuration.curr_y, 
			cursor_symbols[global_terminal_configuration.curr_cursor_symbol_index]
		);
		CX16_COLOR_XY(
		  global_terminal_configuration.curr_x, 
			global_terminal_configuration.curr_y, 
			CX16_BG_BLACK | cursor_colors[global_terminal_configuration.curr_cursor_color_index]
	  );		
		
		// "ANIMATED" THE CURSOR (cycle through cursor symbol index and color)
		++global_terminal_configuration.curr_cursor_symbol_index;
		if (global_terminal_configuration.curr_cursor_symbol_index > CURSOR_SYMBOL_INDEX_MAX)
		{
			global_terminal_configuration.curr_cursor_symbol_index = 0;
		}
				
		++global_terminal_configuration.curr_cursor_color_index;
		if (global_terminal_configuration.curr_cursor_color_index > CURSOR_COLOR_INDEX_MAX)
		{
			global_terminal_configuration.curr_cursor_color_index = 0;
		}		
			
    // IF A KEYBOARD KEYPRESS WAS DETECTED, TAKE ACTION BASED ON THE KEY THAT WAS PRESSED...			
		if (check_kbd() > 0)
		{
			ch = cgetc();
			ch_modifier = check_kbd_modifiers();
			
			valid_key = TRUE;  // assume some valid key was pressed
			
			if (
			 ((ch >= 'A') && (ch <= 'Z'))  // upper case
			)
			{
				// no adjustment is needed
			}
			else if (
			 ((ch >= 'a') && (ch <= 'z'))  // lower case
			)
			{
				ch -= 64;
				ch += 128;
			}
			else if (
			 ((ch >= 48) && (ch <= 57))  // 0 through 9
      )
			{
				// do nothing - accept the "ch" as-is
				ch += 128;
			}
			else if (ch == '\b')  // backspace
			{
				if (global_terminal_configuration.curr_x > 0)
				{
					// clear the "cursor" symbol at the current position
					CX16_WRITE_XY(
						global_terminal_configuration.curr_x, 
						global_terminal_configuration.curr_y, 
						32+128
					);
					CX16_COLOR_XY(
						global_terminal_configuration.curr_x, 
						global_terminal_configuration.curr_y, 
						CX16_BG_BLACK | CX16_BG_WHITE
					);		
					
					--global_terminal_configuration.curr_x;
				}
				valid_key = FALSE;  // the key is valid, but nothing to draw
			}
			else if (ch == '\r')  // carriage return
			{
				// do nothing (key remains valid)
			}
			else if (ch == '\n')
			{
				// clear the "cursor" symbol at the current position
				CX16_WRITE_XY(
					global_terminal_configuration.curr_x, 
					global_terminal_configuration.curr_y, 
					32+128
				);
				CX16_COLOR_XY(
					global_terminal_configuration.curr_x, 
					global_terminal_configuration.curr_y, 
					CX16_BG_BLACK | CX16_BG_WHITE
				);		
				
        global_terminal_configuration.curr_x = 0;
				++global_terminal_configuration.curr_y;
				if (global_terminal_configuration.curr_y >= global_terminal_configuration.curr_height)
				{
					global_terminal_configuration.curr_y = 0;
				}
				valid_key = FALSE;  // the key is valid, but nothing to draw
			}
			else  // "special key"
			{
			  switch (ch)
			  {
					case ' ': ch = 32 + 128; break;
					
				  case '!': ch = 33 + 128; break;
				  case '@': ch =  0 + 128; break;
				  case '#': ch = 35 + 128; break;
				  case '$': ch = 36 + 128; break;
				  case '%': ch = 37 + 128; break;
				  //case '^': ch = 00; break;      no translation available
				  case '&': ch = 38 + 128; break;
				  case '*': ch = 42 + 128; break;
				  case '(': ch = 40 + 128; break;
				  case ')': ch = 41 + 128; break;
					
					//case '_': ch = 111; break;
					case '+': ch = 43 + 128; break;
					case '-': ch = 45 + 128; break;
					case '=': ch = 61 + 128; break;					
					
					case '[': ch = 27 + 128; break;										
					case ']': ch = 29 + 128; break;										
					case '|': ch = 41 + 128; break;  //ch = 93 + 128; break;										
					//case '{': ch = 00; break;										
					//case '}': ch = 00; break;										
					//case '\': ch = 00; break;										
					
					case ';': ch = 59 + 128; break;										
					case '\'': ch = 39 + 128; break;										
					case ':': ch = 58 + 128; break;										
					case '"': ch = 34 + 128; break;										
					
					case '<': ch = 60 + 128; break;										
					case '>': ch = 62 + 128; break;										
					case '?': ch = 63 + 128; break;										
					case ',': ch = 44 + 128; break;										
					case '.': ch = 46 + 128; break;										
					case '/': ch = 47 + 128; break;										
					
		      default:
					  { 
						  // check for command related keypress
							if (ch_modifier == CX16_KEY_MOD_ALT)
							{
							  switch (ch)
							  {
  								case CX16_KEY_ARROW_UP:
									  {									    
											if (global_terminal_configuration.curr_baud_rate_index == BAUD_RATE_INDEX_MAX)
											{
												global_terminal_configuration.curr_baud_rate_index = 0;
											}
											else
											{
												++global_terminal_configuration.curr_baud_rate_index;
											}
											draw_main_screen_overlay();
										}
								    break;
									
  								case CX16_KEY_ARROW_DOWN:
									  {									
											if (global_terminal_configuration.curr_baud_rate_index == 0)
											{
												global_terminal_configuration.curr_baud_rate_index = BAUD_RATE_INDEX_MAX;
											}
											else
											{
												--global_terminal_configuration.curr_baud_rate_index;
											}
											draw_main_screen_overlay();
									  }
	 		  					  break;
		  					}
							}
					  }
					  valid_key = FALSE;						
  				  break;
			  }
			}			
			
			if (valid_key == TRUE)  // valid means: something worth showing on the terminal
			{				
					
				// Write and output the key was that valid
				CX16_WRITE_XY(
					global_terminal_configuration.curr_x, 
					global_terminal_configuration.curr_y, 
					ch
				);
				CX16_COLOR_XY(
					global_terminal_configuration.curr_x, 
					global_terminal_configuration.curr_y, 
					CX16_BG_BLACK | CX16_BG_WHITE
				);		
				// TBD: output ch to serial I/O
				
				// move cursor to the next column
				++global_terminal_configuration.curr_x;
        // handle possible cursor wrap				
				if (global_terminal_configuration.curr_x >= global_terminal_configuration.curr_width)
				{
					global_terminal_configuration.curr_x = 0;  // wrap back to first column
					
					++global_terminal_configuration.curr_y;  // move to next row
					if (global_terminal_configuration.curr_y >= global_terminal_configuration.curr_height)
					{
						// we could scroll; for now just wrap back to first row
						global_terminal_configuration.curr_y = 0;
					}
				}
			}
				
      // DISPLAY LAST ch keycode and modifier
			{
				CX16_WRITE_XY(40, 26, CX16_M2_CHAR_SPACE);
				CX16_WRITE(CX16_M2_CHAR_SPACE);
				CX16_WRITE(CX16_M2_CHAR_SPACE);
				
        print_xy_ulong_as_decimal(40, 26, ch, CX16_BG_BLACK | CX16_FG_YELLOW, 0);
				
				CX16_WRITE_XY(44, 26, CX16_M2_CHAR_SPACE);
				CX16_WRITE(CX16_M2_CHAR_SPACE);
				
        print_xy_ulong_as_decimal(44, 26, ch_modifier, CX16_BG_BLACK | CX16_FG_YELLOW, 0);
			}						
		}
		ch = 0;
	}  // end while (TRUE) (main loop)

}
