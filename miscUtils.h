#ifndef MISCUTILS_H
#define MISCUTILS_H

#include <string>
#include <cstdio>
#include <cstdlib>

using namespace std;


inline void ASSERT (bool condition, string panic_string = "") {
	if (!condition) {
		printf ("\n!! PANIC : %s !!\n\n", panic_string.c_str () );
		exit (0);
	}
}
		

#endif // MISCUTILS_H
