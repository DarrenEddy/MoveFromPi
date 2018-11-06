# include <stdio.h>
# include <softTone.h>
# include <wiringPi.h>
# include <time.h>
# include "ifttt.h"
# include <stdlib.h>

int main(int argc, char *argv[])
{
if (argv[1] == NULL)
{
printf("Missing Argument please include device id\n");
}

char path[1024];
snprintf(path,sizeof(path),"/sys/bus/w1/devices/%s/w1_slave",argv[1]);


int error = 0;

/*
once a second **

if it changes by more than one degree then it should ifttt to my phone
with temp, lowest temp, highest temp
*/

wiringPiSetup();
float temp, initial_temp;
float highest, lowest;

FILE *fd;
int n;
char buf[101];
int first = 1;

for (;;)
{
if ((fd = fopen(path,"r")) == (FILE *)NULL)
{
perror("Reading of thermometer failed");
(void) exit(1);
}
n = fread(buf, 1, 100, fd);
if (n == 0)
{
perror("read failed");
exit(1);
}

int i;
for (i = 0; i < 100;i++)
{
/*this makes sure the file is not disconnecting*/
if(buf[i]=='c'&& buf[i+1] == 'r' && buf[i+2] == 'c')
{
if (buf[i+4] == '0' && buf[i+5] == '0')
{
printf("Device lost\n");
error = 1;
first = 1;
}
else 
{
error = 0;
}

}

if(buf[i] == 't' && buf[i+1] == '=')
{
temp = buf[i+3] - '0';
temp += (buf[i+2] - '0')*10;
temp += (buf[i+4] - '0')*0.1;
temp += (buf[i+5] - '0')*0.01;
}
}

/*close the file*/

fclose(fd);


if (error == 0){

printf("current temp is %.2f || The init is %.2f    ||DIF %.2f\n", temp,initial_temp, initial_temp-temp);

if (first) /*this will run to set the max, min and initla temps*/
{
highest = temp;
lowest = temp;
initial_temp = temp;
first = 0;
}

if (temp > highest){highest = temp;}
if (temp < lowest){lowest = temp;}

if ((temp - initial_temp) >= 1 || (temp - initial_temp) <= -1){

char minsum[32];
char maxsum[32];
char tempch[32];

sprintf(minsum, "Min: %.2f",lowest);
sprintf(maxsum, "Highest: %.2f",highest);
sprintf(tempch, "Current: %.2f",temp);

ifttt("https://maker.ifttt.com/trigger/temp_change > 1/with/key/LX1MgHQQ8QHLFmEKyjmJi", minsum, tempch, maxsum);

printf("TEMP CHANGE  max: %.2f  min: %.2f\n",highest,lowest);

initial_temp = temp;
}
}
delay(900);
}
/*NEVER REACHED*/
return 1;
}
