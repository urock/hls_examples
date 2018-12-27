#include <stdio.h>
#include <cmath>
#include <stdlib.h>
#include <iostream>
#include <sys/time.h>
#include <unistd.h>

#include "fpga.h"


template<int N> struct bits_adder {

	template<typename T>
	static int ff(T a) {
		int b[N/2];
		for (int i=0; i<N/2; ++i) {
			b[i] = a[2*i] + a[2*i+1];
		}
		return bits_adder<N/2>::ff(b);
	}
};

// Termination condition
template<> struct bits_adder<2> {
	template<typename T>
	static int ff(T a) {
		return a[0] + a[1];
	}
};

void top(int *a_in, int *c_out) {
	*c_out = bits_adder<L>::ff(a_in);
}


int main() {

	int a[L]; // = {1, 0, 0, 1, 1, 0, 1, 1};
	int c, g;
	word_t a_word;
	int c_word;

	for (int i = 0; i < L; ++i) {
		a[i] = static_cast<bit_t>(i);
		a_word[i] = a[i];
	}

	// calc golden result
	g = 0;
	for (int i = 0; i < L; ++i)
		g += a[i];

	top(a, &c);

	bits_adder_top(a_word, &c_word);


	printf("golden   -> %d\n", g);
	printf("int temp -> %d\n", c);
	printf("fpga bit templ-> %d\n", c);


	return 0;
}
