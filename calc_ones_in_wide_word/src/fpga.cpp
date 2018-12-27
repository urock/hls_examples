#include "fpga.h"


template<int N, int K> struct bits_adder2 {

	template<typename T>
	static int calc(T a) {
#pragma HLS PIPELINE
		ap_uint<K*2> b[N/2];
#pragma HLS ARRAY_PARTITION variable=b complete dim=1
		calc_loop: for (int i=0; i<N/2; ++i) {
			b[i] = a[2*i] + a[2*i+1];
		}

		return bits_adder2<N/2, K*2>::calc(b);
	}
};

// Termination condition
template<int K> struct bits_adder2<2, K> {
	template<typename T>
	static int calc(T a) {
#pragma HLS PIPELINE
		return a[0] + a[1];
	}
};

void bits_adder_top(word_t a_in, int *c_out) {
#pragma HLS PIPELINE
	*c_out = bits_adder2<L, 1>::calc(a_in);
}



