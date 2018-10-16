#include <stdio.h>
int main(int argc, char *argv[])
{
char name[]= "Darren Eddy";
int stn = 215019193;
char dob[] = "July 1st 1998";
printf("{\"name\":\"%s\", \"number\":\"%d\", \"date\": \"%s\" }",name,stn,dob);
return 0;
}
