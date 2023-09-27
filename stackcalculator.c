/************************
스택 계산기 구현  
*************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 30			//stack 사이즈 

char stack[MAX_STACK_SIZE];			//스택선언 
int stack_cal[MAX_STACK_SIZE];		//int형 스택 선언 
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

void cal_push(int value)  // 계산 용 int형  스택 값 삽입 
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

int cal_pop()	 // 계산 용 int형 스택 값 추출 
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

	for (i = 0; i < strlen(src)-1; i++)					//중위 표기법을 계산하기 쉽게 후위 표기볍으로 바꿔준다 
	{
		if (src[i] >= '0' && src[i] <= '9')				//피연산자는 바로 옮긴 다 
			dest[j++] = src[i];
		else if (src[i] == '*'|| src[i] =='/')			// *, / 연산자를 만나 면 
		{
			if (top == -1 || stack[top] == '(')			// 스택에 연산자가 비어있으면 스택에 담는다 
				push(src[i]);							// ( 뒤에 똑같이 비어있으면 스택에 담는다 
			else if (stack[top] == '+' || stack[top] == '-')	// 자신보다 우선순위가 낮은 연산자+, -를 만났으므로 
				push(src[i]);								// 스택에 연산자를 바로 쌓는다 
			else
			{
				dest[j++] = pop();							// 자신보다 우선순위가 같은 연산자 *, /를 만나면 
				push(src[i]);								// 스택에 담긴 연산자를 꺼내고 다음 연산자를 쌓는다 
			}
		}
		else if (src[i] == '+'||src[i] == '-')				// +, - 연산자를 만나면  
		{
			if (top == -1|| stack[top] == '(') 				// 스택에 연산자가 비어있거나 (를 만나면  
				push(src[i]);								// 스택에 담는다 
			else
			{
				while(stack[top] == '+' || stack[top] == '-'||stack[top] == '*' || stack[top] == '/')
				{								// 자신보다 우선순위가 같거나 높은 연산자를 만나면 
					dest[j++] = pop();			// 스택에 담긴 연산자를 꺼내고  
					
				}
				push(src[i]);					// 다음 연산자를 쌓는다					
			}
		}
		else if (src[i] == '(')					// (를 만나면 스택에 담는다 
			push(src[i]);
		else if (src[i] == ')')					// )를 만나면 
		{
			while (stack[top] != '(')			// ( 를 만날때까지 스택에 담긴 연산자를 전부 꺼낸다 
				dest[j++] = pop();
			pop();								// (는 따로 꺼내서 제거한다 
		}			
		else 
		{
			printf("입력 오류.");		// 잘못 입력됬을때 종료  
			exit(1); 
		}
	}
	while (top > -1)					// 마지막에 스택에 남은 연산자를 전부 꺼내주고 (은 따로 꺼내서 제거한다  
	{
		if (stack[top] == '(')			// (은 따로 꺼내서 제거한다
			pop();
		else dest[j++] = pop();
	}
		
	printf("후위 연산식 : %s\n",dest); 		//중간과정 스택을 이용해 만든 후위 연산식 출력 

	for (i = 0; i < strlen(dest); i++)
	{
		if (dest[i] >= '0' && dest[i] <= '9')	// 피연산자를 만나면 
		{
			k = dest[i] - 48;				// 문자로 된 연산식을 숫자로 변환 
			cal_push(k);					// int형으로 된 다른 스택에 담는다 
		}
		else if (dest[i] == '+' || dest[i] == '-' || dest[i] == '*' || dest[i] == '/')
		{									// 연산자를 만나면 
			b = cal_pop();					// 처음 꺼내는 값을 알으로 
			a = cal_pop();					// 두번째 꺼내는 값을 뒤로 해서 
			result = func(dest[i],a,b);		// 함수를 출력해 계산을 한다 
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
