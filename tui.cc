#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
#include "tui.hpp"

static termios org_term;

void Tui::enter_rawmode(){
	termios now, raw;
	cfmakeraw(&raw);
	tcgetattr(STDIN_FILENO, &now); // 今のターミナルの設定を保存
	org_term = now;
	tcsetattr(STDIN_FILENO, 0, &raw); // raw modeに移行
}

void Tui::exit_rawmode(){
	tcsetattr(STDIN_FILENO, 0, &org_term); // 元々のターミナルの設定に戻す
}

size_t Tui::term_width;
size_t Tui::term_height;
void Tui::update_term_size(){
	winsize ws;
	if(ioctl(STDIN_FILENO, TIOCGWINSZ, &ws) == -1){
		term_width = term_height = 0;
		return;
	}
	term_width = ws.ws_col;
	term_height= ws.ws_row;
}
