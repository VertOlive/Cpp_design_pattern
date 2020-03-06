#include <iostream>

#include "acts_and_brain.h"

int main(int argc, char* argv[]) {
	Actionner act(0);
	Actionner act_2(0);

	Brain brn;
	act.add_observer((Brain*)&brn);
	act_2.add_observer((Brain*)&brn);

	act.change_x_value(5);
	brn.print_value();

	act_2.change_x_value(6);
	brn.print_value();
	
	return EXIT_SUCCESS;
}

