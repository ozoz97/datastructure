/************************
스택 계산기 구현  
*************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 30			//stack 사이즈 

char stack[MAX_STACK_SIZE];			//스택선언 
int stack_cal[MAX_STACK_SIZE];		//계산용 스택 선언 
int top = -1;
int c_top = -1;

int is_full()		// 스택이 꽉 찼을 경우 
{
	if(top >= MAX_STACK_SIZE-1) return 1;
	else return 0;
}

int is_empty()		// 스택이 비어있을경우 
{
	if(top<0) return 1;
	else return 0;
}

void init()			// 스택 초기화 
{
	int i;
	for (i = top;i>=0;i--)
		stack[i] = ' ';
	top = -1;
}

void push(char value)	// 스택 값 삽입 
{
	if (is_full()) printf("stack is full!!\n");
	else stack[++top] = value;
}

void cal_push(int value)  // 계산 용 스택 값 삽입 
{
	stack[++c_top] = value;
		
}


char pop()		// 스택 값 추출 
{
	if (is_empty()) 
	{
		printf("stack is empty!!\n");
		return '\0';
	}
	else 
		return stack[top--];
}

int cal_pop()	 // 계산 용 스택 값 추출 
{
	return stack[c_top--]; 
}

int func(char c,int x, int y)	// 계산 함수 
{
	int temp = 0;
	
	switch(c)
	{
		case '+':
			temp = x + y;
			break;
		case '-':
			temp = x - y;
			break;
		case '*':
			temp = x * y;
			break;
		case '/':
			temp = x / y;
			break;
		default:
			break;
	}
	
	return temp;
}

void calculator()			// 스택을 이용한 계산기 
{
	int i, j = 0, k;
	int a, b;
	char dest[MAX_STACK_SIZE]; 
	char src[MAX_STACK_SIZE];
	char temp[10];
	int result=0;
	printf("계산식 입력 1+2-3/4 : "); //띄어쓰기 없이 일의자릿수 하고 연산자만 입력 
	fgets(src,MAX_STACK_SIZE,stdin);

	for (i = 0; i < strlen(src)-1; i++)
	{
		if (src[i] >= '0' && src[i] <= '9')
			dest[j++] = src[i];
		else if (src[i] == '*'|| src[i] =='/')
		{
			if (top == -1 || stack[top] == '(')
				push(src[i]);
			else if (stack[top] == '+' || stack[top] == '-')
				push(src[i]);
			else
			{
				dest[j++] = pop();
				push(src[i]);
			}
		}
		else if (src[i] == '+'||src[i] == '-')
		{
			if (top == -1|| stack[top] == '(') 
				push(src[i]);
			else
			{
				while(stack[top] == '+' || stack[top] == '-'||stack[top] == '*' || stack[top] == '/')
				{
					dest[j++] = pop();
					
				}
				push(src[i]);
			}
		}
		else if (src[i] == '(')
			push(src[i]);
		else if (src[i] == ')')
			while (stack[top] != '(')
				dest[j++] = pop();
		else 
		{
			printf("입력 오류.");		// 잘못 입력됬을때 종료  
			exit(1); 
		}
	}
	while (top > -1)
	{
		if (stack[top] == '(')
			pop();
		else dest[j++] = pop();
	}
		
	printf("후위 연산식 : %s\n",dest); 		//중간과정 스택을 이용해 만든 후위 연산식 출력 

	for (i = 0; i < strlen(dest); i++)
	{
		if (dest[i] >= '0' && dest[i] <= '9')
		{
			k = dest[i] - 48;
			cal_push(k);
		}
		else if (dest[i] == '+' || dest[i] == '-' || dest[i] == '*' || dest[i] == '/')
		{
			b = cal_pop();
			a = cal_pop();
			result = func(dest[i],a,b);
			printf("%d %c %d = %d \n",a,dest[i], b, result);		//중간 계산 결과 출력 
			cal_push(result);
		}
		
	}
	result = cal_pop();

	printf("계산식 결과 : %d\n", result); 		// 최종 결과 출력 
	
}



int main(void)		//메인 함수 
{
	
	calculator();

	return 0; 
}
