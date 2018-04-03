#include <string>
#include <iostream>
#include <fstream>

namespace editor {
	void err(const std::string &str){
		std::cerr<<str<<std::endl;
		exit(-1);
	}
}

int main(int argc, char **argv){
	using std::string;
	if(argc > 2) editor::err("too many argument.");
	return 0;
}
