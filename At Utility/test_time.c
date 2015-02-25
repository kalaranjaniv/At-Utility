#include <stdio.h>
#include <time.h>
main()
{
	char day[20], month[20];
	struct tm *T;
	time_t ltime=1;
	time(&ltime);
	T = localtime(&ltime);
	printf("sec=%d, min=%d, hour=%d\n", T->tm_sec, T->tm_min, T->tm_hour);
	printf("%22.20s\n",	ctime(&ltime));
	sscanf(ctime(&ltime), "%s %s", day, month);
	printf("day=%s, month=%s\n", day, month);
}

