#include <iostream>
#include <fstream>
#include <string>
#include <list>
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
	for(;;){
		char c = getchar();
		if(c == 'q') break;
		tui.draw();
	}

	Tui::clear();
	return 0;
}catch(...){
	editor::err("exception");
}
}
