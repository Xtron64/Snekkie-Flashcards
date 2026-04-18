#include <stddef.h>
#include <getopt.h>


struct option const create_options[] = {
	{  "overwrite", no_argument, NULL, 'o'  },
	{  NULL, 0, NULL, 0  }
};


struct option const revise_options[] = {
	{  NULL, 0, NULL, 0  }
};


int read_flags(const int argc, char *argv[], struct option getopt_options) {
	int c;
	while ((c = getopt_long(argc, argv, "n:", create_options, NULL)) != -1) {
		
	}
	return 0; // shut up, compiler
}
