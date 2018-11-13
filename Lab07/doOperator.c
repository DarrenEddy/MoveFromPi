#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "doOperator.h"
#include "tokenStack.h"
#include "lexical.h"

static int op_quit(struct tokenStack *stack);
static int op_print(struct tokenStack *stack);
static int op_dump(struct tokenStack *stack);
static int op_add(struct tokenStack *stack);
static int op_sub(struct tokenStack *stack);
static int op_mul(struct tokenStack *stack);
static int op_div(struct tokenStack *stack);
static int op_gt(struct tokenStack *stack);
static int op_lt(struct tokenStack *stack);
static int op_ge(struct tokenStack *stack);
static int op_le(struct tokenStack *stack);
static int op_eq(struct tokenStack *stack);
static int op_mod(struct tokenStack *stack);
static int op_if(struct tokenStack *stack);
static int op_modquot(struct tokenStack *stack);
static int op_swap(struct tokenStack *stack);
static int op_help(struct tokenStack *stack);
static int op_rot(struct tokenStack *stack);
static int op_rotminus(struct tokenStack *stack);
static int op_drop(struct tokenStack *stack);
static int op_s(struct tokenStack *stack);

static struct operator_struct {
  char *name;
  int (*fn_ptr)(struct tokenStack *);
} ops[] = {
  {"quit", op_quit},
  {"print", op_print},
  {"dump", op_dump},
  {"+", op_add},
  {"-", op_sub},
  {"*", op_mul},
  {"/", op_div},
  {"GT", op_gt},
  {"LT", op_lt},
  {"GE", op_ge},
  {"LE", op_le},
  {"EQ", op_eq},
  {"MOD", op_mod},
  {"IF", op_if},
  {"MODQUOT", op_modquot},
  {"SWAP", op_swap},
  {"HELP", op_help},
  {"ROT", op_rot},
  {"ROTMINUS", op_rotminus},
  {"DROP", op_drop},
  {"S", op_s},
  {(char *)NULL, (int(*)(struct tokenStack *)) NULL}
};


/* YOU WRITE THIS */
static int popInt(struct tokenStack *s)
{
int i, result;

struct lexToken *popped;
popped = popTokenStack(s);

result = 0;
if (popped->symbol[0] == '-')
{
	for (i = 1; i<strlen(popped->symbol); i++)
	{
		result = result * 10 + ( popped->symbol[i] - '0');
	}
result = result * -1;
}
else
{
	for(i=0; i<strlen(popped->symbol); i++)
	{
		result = result * 10 + ( popped->symbol[i] - '0');
	}
}

return result;  
}

/* YOU WRITE THIS */
static void pushInt(struct tokenStack *s, int v)
{
struct lexToken *pushing;
char buffer[MAX_SYMBOL_LENGTH];
sprintf(buffer, "%d", v);

pushing = allocToken();

strcpy(pushing->symbol, buffer);
pushing->kind = LEX_TOKEN_NUMBER;
pushTokenStack(s,pushing);

}



int doOperator(struct tokenStack *stack, char *o) 
{
  struct operator_struct *op = ops;
  for(op=ops;op->name != (char *)NULL; op++) {
    if(!strcmp(op->name, o))
      return op->fn_ptr(stack);
  }
  return(-1);
}

/*ARGSUSED*/
static int op_quit(struct tokenStack *stack)
{
  printf("[quit]\n");
  exit(0);
  /*NOTREACHED*/
}

static int op_print(struct tokenStack *stack)
{
  struct lexToken *t = popTokenStack(stack);
  printToken(stdout, t);
  freeToken(t);
  return(0);
}

static int op_dump(struct tokenStack *stack)
{
  struct lexToken *t = popTokenStack(stack);
  dumpToken(stdout, t);
  freeToken(t);
  return(0);
}

static int op_add(struct tokenStack *stack)
{
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  pushInt(stack, v1+v2);
  return(0);
}

static int op_sub(struct tokenStack *stack)
{
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  pushInt(stack, v2-v1);
  return 0;
}

static int op_mul(struct tokenStack *stack)
{
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  pushInt(stack, v1*v2);
  return 0;
}

static int op_div(struct tokenStack *stack)
{
  int v1, v2;
  v1 = popInt(stack); 
  v2 = popInt(stack);
  pushInt(stack, v2/v1);
  return 0;
}


static int op_gt(struct tokenStack *stack)
{
 int v1, v2;
 v1 = popInt(stack);
 v2 = popInt(stack);
 pushInt(stack, v2>v1);
 return 0;
}
static int op_lt(struct tokenStack *stack)
{
 int v1, v2;
 v1 = popInt(stack);
 v2 = popInt(stack);
 pushInt(stack, v2<v1);
 return 0;
}
static int op_ge(struct tokenStack *stack)
{
 int v1, v2;
 v1 = popInt(stack);
 v2 = popInt(stack);
 pushInt(stack, v2>=v1);
 return 0;
}
static int op_le(struct tokenStack *stack)
{
 int v1, v2;
 v1 = popInt(stack);
 v2 = popInt(stack);
 pushInt(stack, v2<=v1);
 return 0;
}
static int op_eq(struct tokenStack *stack)
{
 int v1, v2;
 v1 = popInt(stack);
 v2 = popInt(stack);
 pushInt(stack, v1==v2);
return 0;
}
static int op_mod(struct tokenStack *stack)
{
int v1;
v1 = popInt(stack);
pushInt(stack,v1);
pushInt(stack,v1);
return 0;
}
static int op_if(struct tokenStack *stack)
{
 int c, v1,v2;
 c = popInt(stack);
 v1 = popInt(stack);
 v2 = popInt(stack);
if (c != 0){pushInt(stack,v2);}
else {pushInt(stack,v1);}
return 0;
}
static int op_modquot(struct tokenStack *stack)
{
 int v1, v2, quot, rem;
 v1 = popInt(stack);
 v2 = popInt(stack);

quot = (int)v2/v1;
rem = v2 % v1;

pushInt(stack, rem);
pushInt(stack, quot);
return 0;
}

static int op_swap(struct tokenStack *stack)
{

 int v1, v2;
 v1 = popInt(stack);
 v2 = popInt(stack);
pushInt(stack,v1);
pushInt(stack,v2);

return 0;
}

static int op_help(struct tokenStack *stack)
{
printf("\n====HELP====\n");
printf("rpn Calculator is a Reverse Polish Notation calculator\n");
printf("here you can find a list of instructions:");
printf("\'+\' - Adds the top two items on the stack and pushes the result\n");
printf("\'-\' - Subtracts the top two items on the stack and pushes the result\n");
printf("\"GT\" - states if the second item on the stack is greate than the first\n");
printf("\"LT\" - pushes 1 if the second item is less that the top\n");
printf("\"GE\" - pushes 1 if second item is greater than or equal to the top\n");
printf("\"LE\" - pushes 1 if second item is less than or equal the top\n");
printf("\"EQ\" - pushes 1 if top two items are equal\n");
printf("\"MOD\" - (int) MOD puts the integer back on to the stack twice\n");
printf("\"IF\" - if the top item is non zero it pushes the top item back on the stack else it pushes the 3rd item\n");
printf("\"MODQUOT\" - pushes the remainder then quotient of the top two items\n");
printf("\"SWAP\" - switches the top two items\n");
printf("\"HELP\" - Does what you think\n");
printf("\"ROT\" - rotatest the top three items on the stack\n");
printf("\"ROTMINUS\" - rotates the top three items the opposite direction as ROT\n");
printf("\"DROP\" - removes the top item off the stack\n");
printf("\"S\" - prints the stack in an organized form non destructivley\n");







return 0;
}
static int op_rot(struct tokenStack *stack)
{
int v1, v2, v3;
v1 = popInt(stack);
v2 = popInt(stack);
v3 = popInt(stack);

pushInt(stack,v1);
pushInt(stack,v3);
pushInt(stack,v2);
return 0;
}
static int op_rotminus(struct tokenStack *stack)
{
 int v1, v2, v3;
 v1 = popInt(stack);
 v2 = popInt(stack);
 v3 = popInt(stack);

 pushInt(stack,v2);
 pushInt(stack,v1);
 pushInt(stack,v3);

return 0;
}

static int op_drop(struct tokenStack *stack)
{
popTokenStack(stack);
return 0;
}



static int op_s(struct tokenStack *stack)
{
struct tokenStack *next = createTokenStack();
printf("\n==TOP==\n");

while(stack-> top != 0)
{
struct lexToken *temp;
temp = popTokenStack(stack);
printf("-%s-\n",temp->symbol);
pushTokenStack(next, temp);
}
printf("==Bottom==\n\n");

while(next->top != 0)
{
struct lexToken *temp;
temp = popTokenStack(next);
pushTokenStack(stack, temp);
}
return 0;
}

