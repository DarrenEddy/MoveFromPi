# include <stdio.h>
# include <softTone.h>
# include <wiringPi.h>
# include <time.h>
# include <stdlib.h>
# include <string.h>

int tempread(char device[], int verb);

int main(int argc, char *argv[])
{

char *device = "28-0118423e95ff";
int verbose = 0; 

/* process the arguments */
 argc--; argv++;
 while(argc > 0) {
 if(!strcmp("-v", argv[0])) {
 verbose = 1;
 } else if(!strcmp("-d", argv[0])) {
 if(argc == 0)
	printf("USAGE()"); 
//usage();
 argc--; argv++;
 device = argv[0];
 } else
	printf("USAGE()"); 
// usage();
 argc--; argv++;
 }
 tempread(device, verbose);
 exit(0); 
}

/*====================================*/
int tempread(char device[], int verb)
{
char path[1024];
snprintf(path,sizeof(path),"/sys/bus/w1/devices/%s/w1_slave", device);
wiringPiSetup();
int temp;

FILE *fd, *dest;
int n;
char buf[101];

if ((fd = fopen(path,"r")) == (FILE *)NULL)
{
exit(1);
}

n = fread(buf, 1, 100, fd);
if (n == 0)
{
exit(1);
}

if(verb)
{
if ((dest = fopen("stdout.txt","w")) == (FILE *)NULL)
{
exit(1);
}



fprintf(dest, "%s\n",buf);
fclose(dest);
}


int i;
for (i = 0; i < 100;i++)
{

if(buf[i]=='c'&& buf[i+1] == 'r' && buf[i+2] == 'c')
{
if (buf[i+4] == '0' && buf[i+5] == '0')
{
exit(1);
}
}


if(buf[i] == 't' && buf[i+1] == '=')
{
temp = (buf[i+2] - '0')*10000;
temp += (buf[i+3] - '0')*1000;
temp += (buf[i+4] - '0')*100;
temp += (buf[i+5] - '0')*10;
temp += (buf[i+6] - '0');
}
}
printf("%i\n",temp);
fclose(fd);
return 1;
}



