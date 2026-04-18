#ifndef GETOPT_LONG_OPTIONS_H
#define GETOPT_LONG_OPTIONS_H
#include <getopt.h>


extern struct option const create_options[];
extern struct option const crevise_options[];


int read_flags(const int argc, char *argv[], struct option getopt_options);
#endif
