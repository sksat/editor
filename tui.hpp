#ifndef TUI_HPP_
#define TUI_HPP_

#include <vector>
#include <string>

class Tui {
public:
	Tui(){
		enter_rawmode();
		data = std::vector<char>(get_height()*get_width(), ' ');
//		printf("height: %d, width: %d, data: %d", (int)get_height(), (int)get_width(), (int)data.size());
//		getchar();
		term_width = 123;
	}

	~Tui(){
		exit();
	}

	char& get_data(size_t x, size_t y){
		return data[(y-1)*123 + (x-1)];
	}

	void putchar(const char &c){ putchar(x, y, c); }
	void putchar(const size_t &x, const size_t &y, const char &c){
		get_data(x, y) = c;
	}

	void print(const size_t &x, const size_t &y, const std::string &str){
		size_t line = 0;
		for(size_t i=0;i<str.size();i++){
			char c = str[i];
			switch(c){
//			case '\n': line++; break;
			default:
				   putchar(x+i, y, c);
				   break;
			}
		}
	}

	void draw(){
		clear();
		for(size_t y=1;y<=term_height;y++){
			for(size_t x=1;x<=term_width;x++){
				move_cur(x, y);
				printf("%c", get_data(x, y));
			}
		}
	}

	void update_cur(){ move_cur(x, y); }

	static size_t get_width(){  update_term_size(); return term_width; }
	static size_t get_height(){ update_term_size(); return term_height; }
	static void move_cur(size_t x, size_t y){ printf("\e[%d;%dH", static_cast<int>(y), static_cast<int>(x)); }
	static void clear(){
		printf("\e[2J");
		move_cur(1, 1);
	}
	static void exit(){ exit_rawmode(); }
private:
	size_t x=1, y=1;
	std::vector<char> data;

	static constexpr char esc = 0x1b;
	static size_t term_width, term_height;
	static void enter_rawmode();
	static void exit_rawmode();
	static void update_term_size();
};

#endif
