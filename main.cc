#include <sksat/cmdline.hpp>

int main(int argc, char **argv){
	sksat::optparse op;
	op.parse(argc, argv);
	return 0;
}
