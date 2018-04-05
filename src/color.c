#include <ncurses.h>
#include "color.h"

extern void color::setupColorPairs()
{
	init_color(CN_BGWBG, CC_BGWBG);
	init_pair(P_BGW, COLOR_WHITE, CN_BGWBG);

	init_color(CN_BGWBGH, CC_BGWBGH);
	init_pair(P_BGWH, COLOR_GREEN, CN_BGWBGH);

	init_color(CN_FGWBG, CC_FGWBG);
	init_pair(P_FGW, COLOR_WHITE, CN_FGWBG);

	init_color(CN_FGWBGH, CC_FGWBGH);
	init_pair(P_FGWH, COLOR_BLACK, CN_FGWBGH);
}