#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <queue>
#include "tui.hpp"

namespace editor {
	void err(const std::string &str){
		Tui::exit();
		std::cerr<<str<<std::endl;
		exit(-1);
	}

	void read_file(const std::string &filename, std::list<std::string> &data){
		std::ifstream ifs(filename);
		if(ifs.fail()){
			err("cannot open file.");
		}

		std::string str;
		while(getline(ifs, str)){
			data.push_back(str);
		}
	}

	struct Key {
		bool is_print;
		bool alt, ctrl;
		bool fn;
		char c;
	};

	Key read_key(){
		Key k;
		k.is_print = k.alt = k.ctrl = k.fn = false;
		char buf[7];
		buf[1] = 0x00;
		read(1, buf, 7);
		char& c = buf[0];
		if(c != 0x1b){
			k.c = c;
			if(0x20 <= c && c <= 0x7f){
				k.is_print = (c==0x7f ? true : false); // BackSpace以外なら普通の文字
				return k;
			}else if(0x00 < c && c < 0x1b){
				switch(c){
				case 0x09: k.is_print = true; break; // Tab
				case 0x0d: break; // Enter
				default:
					k.ctrl = true;
					k.c += 0x60;
					break;
				}
				return k;
			}
			k.c = 0x00;
			return k;
		}

		char& c2 = buf[1];
		if(c2 == 0x00){
			err("Esc");
		}else if(0x27 <= c2 && c2 <= 0x5a){
			k.c = c2;
			k.alt = true;
			if(c2 == 0x4f && 0x50 <= buf[2] && buf[2] <= 0x53){
				k.alt = false;
				k.fn = true;
				k.c = buf[2] - 0x50 + 1;
			}
		}else if(c2 == 0x5b){
			char& c3 = buf[2];
			if(c3 == 0x31){
				char& c4 = buf[3];
				if(0x35 <= c4 && c4 <= 0x39){
					k.fn = true;
					k.c = c4 - 0x30;
					if(c4 != 0x35) k.c--;
					if(buf[4] != 0x7e){
						if(buf[4] == 0x3b && buf[5]==0x32 && buf[6]==0x7e){
							// Shift
						}else err("not implemented.");
					}
				}else if(c4 == 0x3b && buf[4] == 0x32){
					switch(buf[5]){
					case 0x41: err("Shift+↑ ");
					case 0x42: err("Shift+↓ ");
					case 0x43: err("Shift+→ ");
					case 0x44: err("Shift+← ");
					case 0x50: err("Shift+F1");
					case 0x51: err("Shift+F2");
					case 0x52: err("Shift+F3");
					case 0x53: err("Shift+F4");
					default:
						err("not implemented.");
						break;
					}
				}
			}else if(c3 == 0x32){
				char& c4 = buf[3];
				if(c4 == 0x7e) err("Insert");
				k.fn = true;
				k.c = c4 - 0x27;
				if(c4 == 0x34) k.c--;
				if(buf[4] != 0x7e){
					// Shift
				}
			}else{
				switch(c3){
				case 0x33: err("Delete"); break;
				case 0x35: err("PgUp");   break;
				case 0x36: err("PgDown"); break;
				case 0x41: err("↑ ");     break;
				case 0x42: err("↓ ");     break;
				case 0x43: err("→ ");     break;
				case 0x44: err("← ");     break;
				case 0x46: err("End");    break;
				case 0x48: err("Home");   break;
				default:
					   err("not implemented.");
					   break;
				}
			}
		}else{
			if(0x5c <= c2 && c2 <= 0x7c){
				k.alt = true;
				k.c = c2;
			}else err("not implemented.");
		}
		return k;
	}
}

int main(int argc, char **argv){
try{
	using namespace editor;
	using std::string;

	if(argc > 2) editor::err("too many argument.");

	Tui tui;
	Tui::clear();

	string filename(argv[1]);
	std::list<std::string> data;
	if(!filename.empty()) read_file(filename, data);

//	tui.print(2, 3, "hello");

	size_t line = 1;
	for(const string &str : data){
		tui.print(1, line, str);
		line++;
	}

	tui.draw();

	std::queue<Key> key_queue;

	for(;;){
		key_queue.push(editor::read_key());
		auto& k = key_queue.back();
		if(k.ctrl) printf("Ctrl+");
		if(k.alt) printf("Alt+");
		if(k.fn) printf("F%d\n", (int)k.c);
		else if(k.c) printf("%c\n", k.c);

		if(k.c == 'q') break;
/*
		char c = getchar();
		switch(c){
		case 'q': goto fin;
		case 'h': tui.move_cur_left(); break;
		case 'j': tui.move_cur_down(); break;
		case 'k': tui.move_cur_up(); break;
		case 'l': tui.move_cur_right(); break;
		default:
			//printf("%x", c);
			break;
		}
*/
//		tui.draw();
	}

fin:
	Tui::clear();
	return 0;
}catch(...){
	editor::err("exception");
}
}
