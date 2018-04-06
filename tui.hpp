#ifndef TUI_HPP_
#define TUI_HPP_

#include <vector>
#include <string>

class Tui {
public:
	Tui(){
		enter_rawmode();
		data = std::vector<char>(get_height()*get_width(), ' ');
	//	printf("height: %d, width: %d, data: %d", (int)get_height(), (int)get_width(), (int)data.size());
	//	getchar();
	}

	~Tui(){
		exit();
	}

	const char get_data(size_t x, size_t y){
		size_t addr = (y-1)*term_width + (x-1);
		return data[addr];
	}
	void set_data(size_t x, size_t y, char c){
		size_t addr = (y-1)*term_width + (x-1);
		data[addr] = c;
	}

	void putchar(const char &c){ putchar(x, y, c); }
	void putchar(const size_t &x, const size_t &y, const char &c){
		set_data(x, y, c);
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
		for(size_t y_=1;y_<=term_height;y_++){
			for(size_t x_=1;x_<=term_width;x_++){
				if(x_ == this->x && y_ == this->y)
					printf("\e[7m%c\e[0m", get_data(x,y));
				else
					printf("%c", get_data(x_, y_));
			}
		}
		fflush(0);
	}

	void move_cur(const size_t &x, const size_t &y){
		this->x = (x<=term_width ? x : term_width);
		this->y = (y<=term_height? y : term_height);
		if(!this->x) this->x++;
		if(!this->y) this->y++;
		update_cur();
	}
	void move_cur_up(){   move_cur(this->x, this->y-1); }
	void move_cur_down(){ move_cur(this->x, this->y+1); }
	void move_cur_left(){ move_cur(this->x-1, this->y); }
	void move_cur_right(){move_cur(this->x+1, this->y); }
	void update_cur(){ Tui::move_cursor(x, y); }

	static size_t get_width(){  update_term_size(); return term_width; }
	static size_t get_height(){ update_term_size(); return term_height; }
	static void move_cursor(const size_t &x, const size_t &y){
		printf("\e[%d;%dH", static_cast<int>(y), static_cast<int>(x));
	}
	static void clear(){
		printf("\e[;H\e[2J");
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
