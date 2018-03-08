#include <slang.h>
int main()
{
        SLtt_get_terminfo ();
        SLang_init_tty (-1, 0, 0);
        SLsmg_init_smg ();
 
	SLsmg_utf8_enable (1);
	SLtt_utf8_enable (1);
 
	SLsmg_Newline_Behavior = SLSMG_NEWLINE_MOVES;
 
	SLtt_set_color(0,NULL, "green", "blue");
	SLsmg_write_string("Első\n");
 
 
	SLsmg_refresh();
	SLang_getkey();
 
	SLtt_set_color(0,NULL, "white", "red");
	SLsmg_write_string("Első\n");
	SLsmg_refresh();
	SLang_getkey();
 
 
        SLsmg_reset_smg ();
        SLang_reset_tty ();

    return 0;
}