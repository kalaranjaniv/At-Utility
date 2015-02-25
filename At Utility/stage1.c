#include <stdio.h>
#include <stdlib.h>

char* subString(const char* input, int offset, int len, char* dest);
int process_arguments(int argc, char *argv[]);

int main(int argc, char *argv[]) {

	int seconds = process_arguments(argc,argv);
	printf("%d", seconds);

}
int process_arguments(int argc, char *argv[]) {
	if (argc < 3) {
		printf("Usage <At> <Time> <command> <<arguments>>");
		exit(0);
	} else {
		char *at = argv[1];
		if (strcmp(at, "At") != 0) {
			printf("Usage <At> <Time> <command> <<arguments>>");
			exit(0);
		}
		else {
			char *time = argv[2];
			char hours[10];
			char minutes[10];
			char sec[10];
			int seconds = 0;
			if (subString(time, 1, 2, hours)) {
				seconds = seconds + (atoi(hours) * 60 * 60);
			}
			if (subString(time, 5, 2, minutes)) {
				seconds = seconds + (atoi(minutes) * 60);
			}
			if (subString(time, 5, 2, sec)) {
				seconds = seconds + (atoi(sec) * 60);
			}

			return seconds;
		}
	}
}
char* subString(const char* input, int offset, int len, char* dest) {
	int input_len = strlen(input);

	if (offset + len > input_len) {
		return NULL;
	}

	strncpy(dest, input + offset, len);
	return dest;
}

