# include <stdio.h> 
# include "isMirrored.h"

int isMirrored(int x)
{
int length = snprintf(NULL, 0,  "%d", x );
char xasc[length+1];
snprintf(xasc, length+1, "%d", x);


int i = 0;
int end = length-1;


for (i; i<end;i++,end--)
{
if(xasc[i]!=xasc[end]){return 0;}
}
return 1;
}
