//Joshua Lawson
//Bryan Fowles
/*
ref: 
https://www.geeksforgeeks.org/stack-set-2-infix-to-postfix/
*/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

struct Stack
{
    int top;
    unsigned capacity;
    char array[256][256];
};

struct Stack* createStack( unsigned capacity )
{
    struct Stack* stack = (struct Stack*) malloc(sizeof(struct Stack));
    if (!stack) return NULL;
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}
int isEmpty(struct Stack* stack)
{
    return stack->top == -1 ;
}
int gettop(struct Stack* stack){
  return stack->top;
}
char * peek(struct Stack* stack)
{
    return stack->array[stack->top];
}
char * pop(struct Stack* stack)
{
    if (!isEmpty(stack))
        return stack->array[stack->top--] ;
    return "Empty";
}
void push(struct Stack* stack,char *op)
{
  strcpy(stack->array[++stack->top],op);
}

//TODO - Function - Addition
double addition(double n1, double n2);
//TODO - Function - Subtraction
double subtraction(double n1, double n2);
//TODO - Function - Multiplication
double product(double n1, double n2);
//TODO - Function - Division
double division(double n1, double n2);
//TODO - Function - Modulus
double remainder(double n1, double n2);
//TODO - Function - Exponent
double exponent(double n1, double n2);
//TODO - Function - clear()

int isanum(char c);
unsigned int slen(const char *s);
unsigned int is_operator(char symbol);




void infix_to_postfix(char infix[256][256],struct Stack* operand, struct Stack* operator, int m);

double operation(char op, double n1, double n2);
double conversion(char a[]);
int priority(char  operation);

int main(void) {
  //TODO - Implementation of user input
  int resume = 1;
  do{
  int i = 0, a, numstart = 0, m = 0, len, numcount = 0;
  char s[256],number[256],op[2];
  op[1] = '\0';
  char token[256][256];\
  double operands[256];
  double answer;
  int opf = -1;
  
  printf("Enter Expression: ");
  scanf("%s", s);
  a = slen(s);
  if(a == 1){
    return 0;
  }
  //Tokenization - not done
  for(i = 0; i <= a;i++){
    if(isanum(s[i]) == 0){
      op[0] = s[i];
      s[i] = '\0';
      for(i = numstart; s[i] != '\0';i++){
        number[numcount] = s[i];
        numcount++;
      }
      number[numcount] = '\0';
      numcount = 0;
      numstart = i+1;
      if(slen(number) > 0){
        // token[m] = malloc(slen(number) + 1);
        strcpy(token[m],number);
        m++;
      }
      if(slen(op) > 0){
        // token[m] = malloc(slen(op) + 1);
        strcpy(token[m],op);
        m++;
      }
    } 
  }
  //Use the token array(which is a 2d array) and m(which is the amount of tokens stored in the array) when you need to pass the token array or its size as parameters. 

  // printf("%c",*token[0]);
  struct Stack* postfix = createStack(m);
  struct Stack* operator = createStack(m);
 
  infix_to_postfix(token,postfix,operator,m);
  char *expression[256];
  int k = gettop(postfix);
  
  for(int i = k; i >= 0; i--){
    expression[i] = peek(postfix);
    pop(postfix);
  }

  
  //evaluation - not done
  for(i = 0; i <= k; i++){//k is the size of the token postfix array/expression is the array itself
    if(priority(expression[i][0]) != 0){
      //answer is the final result
      //operands is the double array that holds the operands once they are passed into the conversion function, as well as the answer.
      answer = operation(expression[i][0], operands[opf-1], operands[opf]);//this does the math itself
      opf = opf - 1;//decrement opf(operands index) in order to store the answer in the proper position. Otherwise, when you have the result of an operation as an operand, it would not be the correct number. Example
      operands[opf] = answer;//store the answer in the operand array so that it can be potentially used in any operation that happens later.
    } else {
      opf = opf + 1;//increment before you input an element
      operands[opf] = conversion(expression[i]);//input result of passing in the current token into the conversion function.
    }
  }

  printf("\nAnswer: %f\n",operands[0]);
  }while(resume == 1);
  return 0;
}
//end main
//DONE
int priority(char  operation){
  if(operation == '^'){
    return 3;
  }
  if(operation == '*' || operation == '/' || operation == '%'){
    return 2;
  }
   else if(operation == '+' || operation == '-'){
    return 1;
  }else{
    return 0;
  }
} 



 void infix_to_postfix(char infix[256][256],struct Stack* operand, struct Stack* operator, int m){
  int i; //index for infix
  int j; //index for postfix
  

  for(int i = 0; i < m; i++){
    if(is_operator(infix[i][0]) == 1){//if its not an operator push to the operator stack
      if(infix[i][0] == '('){
        push(operator,infix[i]);
        
      } else if(infix[i][0] == ')'){ 
        while(*peek(operator) != '('){
          push(operand,peek(operator));
          pop(operator); 
        }
        pop(operator);
  
      }
      else if((priority(infix[i][0]) > priority(*peek(operator))) || (isEmpty(operator))){
        push(operator,infix[i]);
         
      } else if(priority(infix[i][0]) <= priority(*peek(operator))){
        push(operand,peek(operator));
        pop(operator);
        push(operator,infix[i]);
         
      } 
      
    } else {
      push(operand,infix[i]);
    }
    
  }

  while(isEmpty(operator) != 1){
    if((*peek(operator) == '(') || (*peek(operator) == ')')){
      pop(operator);
    } else {
      push(operand,peek(operator));
      pop(operator);
    }
  }
}

//Technically all done
double addition(double n1, double n2){
  double sum = n1 + n2;
  return sum;
}

double subtraction(double n1, double n2){
  double sub = n1 - n2;
  return sub;
}

double product(double n1, double n2){
  double product = n1 * n2;
  return product;
}

double division(double n1, double n2){
  double division = n1 / n2;
  return division;
}

double remainder(double n1, double n2){
  double remainder = fmod(n1,n2);
  return remainder;
}

double exponent(double n1, double exp){
  int pow = 1;
  double result;
  for(double i = 0; i < exp; i++){
    result = n1 * pow;
    pow = pow * n1;
  }
  return result;
}
//Done
int isanum(char c){
  int isnum = 0;
  if (c == '.'){
    isnum = 1;
  } else if(((c <= 57) && (c >= 48))){
    isnum = 1;
  }
  return isnum;
}
//DONE
unsigned int slen(const char *s){
  unsigned int count = 0;
  for(count = 0; s[count] != '\0';count++);
  return count;
}
//Done 
unsigned int is_operator(char symbol)
{
	if(symbol == '^' || symbol == '*' || symbol == '/' || symbol == '+' || symbol =='-' || symbol == '%' || symbol == ')'|| symbol == '(')
	{
		return 1;
	}
	else
	{
	return 0;
	}
}
//DONE
double conversion(char a[]){
    int pow10 = 1;
    double b = 0;
    for(int i = slen(a) - 1; i >= 0; i--) {
      if(a[i] == '.'){
        b = b/pow10;
        pow10 = 1;
      } else {
        b += (a[i] - '0')  * pow10;
        pow10 = pow10 * 10;
      }
    }
    return b;
  }

//DONE
double operation(char op, double n1, double n2){
    double result;
    if(op == '+'){
      result = addition(n1, n2);
    } else if(op == '-'){
      result = subtraction(n1, n2);
    } else if(op == '/'){
      result = division(n1, n2);
    } else if(op == '*'){
      result = product(n1,n2);
    } else if(op == '%'){
      result = remainder(n1, n2);
    } else if(op == '^'){
      result = exponent(n1, n2);
    }
    return result;
  }