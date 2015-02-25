#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <unistd.h>
#include <signal.h>

int process_arguments(int argc, char *argv[]);
int get_time_compute_delay(char *time);
char* substring(const char* input, int offset, int len, char* dest);
int second_till_now();
void At_cmd (int delay);
void test_signals();
char **arglist;
char *pathdetails;
void sig_catcher();
int At_cmd_id;
int main(int argc, char *argv[]) {

	int delay =0;
	 delay = process_arguments(argc, argv);
	 if((At_cmd_id=fork()) == 0)
	 {
		 At_cmd (delay);
	 }
	 else
	 {
		 test_signals();
	 }

	return 0;
}
void At_cmd (int delay)
{

	signal(SIGALRM, sig_catcher); //Tell kernel to transfer to sig_catcher(), when alarm goes off
	signal (SIGINT, SIG_IGN);
	//printf("from At_cmd\n");
	alarm(delay); //set an alarm to go off at the end of given delay period
	printf("before  execv");
	pause(); //go to sleep until interrupted by alarm or some other signal

	execv(pathdetails,arglist);
	printf("After execv kala");
}
void sig_catcher()
{
printf("Snooze\n");
}

void test_signals()
{
	sleep(2);
//	printf("from test signals\n");
	kill(At_cmd_id, SIGINT);
	sleep(2);
	kill(At_cmd_id,SIGALRM);
	sleep(2);
	kill(At_cmd_id,SIGALRM);
}
int process_arguments(int argc, char *argv[]) {
	char time[10];
	int count;
	int i;
	int length;
	int seconds;
	strcpy(time, argv[1]);
	count = argc - 2;
	arglist = (char**) malloc(count * sizeof(char*));
	for (i = 0; i < count; i++) {
		length = strlen(argv[i + 2]) + 1;
		arglist[i] = (char*) malloc(length * sizeof(char));
		strcpy(arglist[i], argv[i + 2]);
	}
	arglist[i] = NULL;
	printf("Time: %s\n", time);
	for (i = 0; i < count; i++) {
		printf("arglist[%d]=%s\t", i, arglist[i]);
	}
	printf("\n");
	seconds = get_time_compute_delay(time);
	pathdetails = pathfind(getenv("PATH"), arglist[0], "rx");
	if(pathdetails != NULL)
	{
	printf("%s\n",pathdetails);
	}
	else
	{
		printf("Command %s not found\n", arglist[0]);
		exit(1);
	}
	return seconds;
}

int get_time_compute_delay(char *time) {
	char hours[10]="";
	char minutes[10]="";
	char sec[10]="";
	int seconds = 0;
	char delaychar[2]="";
	if (substring(time, 0, 1, delaychar)) {
			if (substring(time, 1, 2, hours)) {
				if (atoi(hours) < 24) {
					seconds = seconds + (atoi(hours) * 60 * 60);
				} else {
					printf("Hours should be less than 24\n");
					exit(1);
				}
			}
			if (substring(time, 4, 2, minutes)) {
				if (atoi(minutes) <60) {
					seconds = seconds + (atoi(minutes) * 60);
				} else {
					printf("Minutes should be less than 60\n");
					exit(1);
				}
			}
			if (substring(time, 7, 2, sec)) {
				if (atoi(sec)< 60 ) {
					seconds = seconds + (atoi(sec));
				} else {
					printf("Seconds should be less than 60\n");
					exit(1);
				}
			}

			if (strcmp(delaychar,"+")==0) {
			printf("Delay +:%d\n", seconds);
			}
			else{

					int secondsfrommidnight = second_till_now();
					if(secondsfrommidnight>seconds)
					{
						seconds = 86400 - secondsfrommidnight + seconds;
					}
					else
					{
						seconds = seconds - secondsfrommidnight;
					}
					printf("Delay @:%d\n", seconds);
				}
		}
	return seconds;
}

char* substring(const char* input, int offset, int len, char* dest) {
	int input_len = strlen(input);

	if (offset + len > input_len) {
		return NULL;
	}

	strncpy(dest, input + offset, len);
	return dest;
}

int second_till_now()
{FILE *dt, *popen();
 int hr, min, sec;
 char shr[3], smin[3], ssec[3];

 /* popen runs the command with its argument specified in the
 form of a string. Its output is directed into file opened for
 reading or writing. */

 if ((dt = popen("/bin/date '+%H %M %S'", "r")) < 0)
	printf("popen failed \n");
 fscanf(dt, "%s %s %s", shr, smin, ssec);
 hr = atoi(shr); min = atoi(smin); sec = atoi(ssec);
 pclose(dt);
 return (60*60*hr + 60*min + sec);
 }

