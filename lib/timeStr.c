#include <stdio.h>

#include <time.h>

time_t rawtime;
struct tm * timeinfo;
char buffer[80];
//time (&rawtime);
//timeinfo = localtime (&rawtime);
//printf ("Time: %s\n", asctime(timeinfo));

char *getTimeString()
{
		time (&rawtime);
		timeinfo = localtime (&rawtime);
		
		strftime (buffer,80,"%T %d/%m/%y %Z",timeinfo);
		//printf("%s\n", buffer );
		return buffer;

}