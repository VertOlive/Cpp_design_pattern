#ifndef EXAMPLE_DECORATOR_H
#define EXAMPLE_DECORATOR_H

#include "decorator.h"

int test_function(int x, int y) {
	return x + y;
}

int test_at_exit(int z) {
	return z*z;
}

#endif /* EXAMPLE_DECORATOR_H */
