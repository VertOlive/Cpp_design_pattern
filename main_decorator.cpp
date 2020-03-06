#include <iostream>

#include "example_decorator.h"

int main(int argc, char *argv[]) {
	
	decorator<int, int, int> dec(test_at_exit);
	int z = test_function(1, 1); 
	std::cout << z << std::endl;

	std::function<int(int, int)> test_function_with_decorator = dec.make_decorator(test_function);

	z = test_function_with_decorator(1, 1);
	std::cout << z << std::endl;

	return EXIT_SUCCESS;
}
