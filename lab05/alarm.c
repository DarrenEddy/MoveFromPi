# include <stdio.h>
# include <softTone.h>
# include <wiringPi.h>
# include <time.h>
# include "ifttt.h"
/*
wiring pins : Desc : purpose
0:input for motion detector: input
1:LED 1 "Yellow": output
2:LED 2 "RED": output
3:Button: input
4:Buzzer: to annoy (output)
*/


int main(int argc, char *argv[])
{
wiringPiSetup();
pinMode(0, INPUT);
pinMode(1, OUTPUT);
pinMode(2, OUTPUT);
pinMode(3, INPUT);
softToneCreate(4);
pullUpDnControl(3, PUD_UP);

double start, end;
int toggle_flash = 1;

int state = 0;

/*
list of states
0 = off
1 = arming
2 = armed
3 = triggered
4 = sounding

*/
for(;;)
{
if (state == 0)
{
digitalWrite(1, HIGH);
if (digitalRead(3)==0){
start = (double)time(NULL);
state = 1;
}
delay(20);
digitalWrite(1,LOW); 
}

else if (state == 1)
{
end = (double) time(NULL);

digitalWrite(1,HIGH);delay(1000);digitalWrite(1,LOW);delay(1000);
if (end-start > 10){state = 2;}
}

else if (state == 2)
{
digitalWrite(2,HIGH);
if (digitalRead(3) == 0){state = 0;delay(500);}
if (digitalRead(0) == 1){state = 3; delay(500);start = (double) time(NULL);}
digitalWrite(2,LOW);
}

else if (state == 3)
{
end = (double) time(NULL);
int seconds = (int)(end-start);
if (seconds > 10){state = 4; delay(500);seconds=10;ifttt("https://maker.ifttt.com/trigger/alarm_triggered/with/key/LX1MgHQQ8QHLFmEKyjmJi","Sent From Darren's Pi","Alarm Triggered","Made By Darren");}
if (digitalRead(3) == 0){state = 0;delay(500);seconds=10;}

if (seconds % 4 == 0)
{
digitalWrite(1,HIGH);
digitalWrite(2,HIGH);
}

else if (seconds % 2 == 0)
{
digitalWrite(1,LOW);
digitalWrite(2,LOW);
}

}

else if (state == 4)
{
softToneWrite(4,36);
if (digitalRead(3)==0){state = 0;delay(500);}
softToneWrite(4,0);
}
}

/*NEVER REACHED*/

return 0;
}
