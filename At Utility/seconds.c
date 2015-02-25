#include <stdio.h>
/* This program shows use of popen() function, which runs a
command and redirects its I/O.*/

int second_till_now();
main()
{
printf("Current time in seconds since midenight = %d\n", second_till_now());
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

