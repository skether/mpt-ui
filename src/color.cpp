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
}