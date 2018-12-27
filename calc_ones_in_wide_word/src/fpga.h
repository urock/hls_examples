#ifndef FPGA_H
#define FPGA_H

#define AP_INT_MAX_W 2048
#include "ap_int.h"

#define L 2048

typedef ap_uint<1> bit_t;
typedef ap_uint<L> word_t;



void bits_adder_top(word_t a_in, int *c_out);



#endif
