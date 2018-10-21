#include "color.h"

#include <ncurses.h>

void setupColors()
{
	//Window Inactive Normal
	init_color(Color_Window_Inactive_Background, Color_Window_Inactive_Background_ColorCode);
	init_pair(Color_Window_Inactive_Normal, COLOR_WHITE, Color_Window_Inactive_Background);

	//Window Active Normal
	init_color(Color_Window_Active_Background, Color_Window_Active_Background_ColorCode);
	init_pair(Color_Window_Active_Normal, COLOR_WHITE, Color_Window_Active_Background);

	//TextBox Defocused
	init_color(Color_TextBox_Defocused_Background, Color_TextBox_Defocused_Background_ColorCode);
	init_pair(Color_TextBox_Defocused, COLOR_BLACK, Color_TextBox_Defocused_Background);

	//TextBox Focused
	init_color(Color_TextBox_Focused_Background, Color_TextBox_Focused_Background_ColorCode);
	init_pair(Color_TextBox_Focused, COLOR_BLACK, Color_TextBox_Focused_Background);

	//TextBox Cursor
	init_color(Color_TextBox_Focused_Cursor_Foreground, Color_TextBox_Focused_Cursor_Foreground_ColorCode);
	init_pair(Color_TextBox_Cursor, COLOR_BLACK, Color_TextBox_Focused_Cursor_Foreground);
}