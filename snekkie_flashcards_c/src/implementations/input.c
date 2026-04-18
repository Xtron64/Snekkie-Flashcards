#include "../headers/shared_typedefs.h"
#include "../headers/input.h"


/*int int_input(const char *message) {
	inputStart:
	int value = 0;
	char input [128] = {0};
	bool flag_eof = true;
	printf("%s", message);
	// Keep reading input until the user enters a valid integer
	while (fgets(input, sizeof(input), stdin)!=NULL) {		
		size_t len = strlen(input);
		if (len > 0 && input[len-1] != '\n') {
			int ch;
			while ((ch = getchar()) != '\n' && ch != EOF)
				continue;
			printf("Input is too long. Try again: ");
			continue;
		}
		char* end = NULL;
		errno = 0;
		const long int longIndex = strtol(argv[i], &end, 0);
		if (errno == ERANGE 
			|| end == argv[i] 
			|| *end != '\0' 
			|| longIndex<0 
			|| longIndex > INT_MAX) {
			printf("ERROR: Number too large.\n")
			goto inputStart;
		}
	}
	if (flag_eof) {
		//exit(1);
	}
	return value;
}
*/
