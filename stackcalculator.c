/************************
���� ���� ����  
*************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 30			//stack ������ 

char stack[MAX_STACK_SIZE];			//���ü��� 
int stack_cal[MAX_STACK_SIZE];		//���� ���� ���� 
int top = -1;
int c_top = -1;

int is_full()		// ������ �� á�� ��� 
{
	if(top >= MAX_STACK_SIZE-1) return 1;
	else return 0;
}

int is_empty()		// ������ ���������� 
{
	if(top<0) return 1;
	else return 0;
}

void init()			// ���� �ʱ�ȭ 
{
	int i;
	for (i = top;i>=0;i--)
		stack[i] = ' ';
	top = -1;
}

void push(char value)	// ���� �� ���� 
{
	if (is_full()) printf("stack is full!!\n");
	else stack[++top] = value;
}

void cal_push(int value)  // ��� �� ���� �� ���� 
{
	stack[++c_top] = value;
		
}


char pop()		// ���� �� ���� 
{
	if (is_empty()) 
	{
		printf("stack is empty!!\n");
		return '\0';
	}
	else 
		return stack[top--];
}

int cal_pop()	 // ��� �� ���� �� ���� 
{
	return stack[c_top--]; 
}

int func(char c,int x, int y)	// ��� �Լ� 
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

void calculator()			// ������ �̿��� ���� 
{
	int i, j = 0, k;
	int a, b;
	char dest[MAX_STACK_SIZE]; 
	char src[MAX_STACK_SIZE];
	char temp[10];
	int result=0;
	printf("���� �Է� 1+2-3/4 : "); //���� ���� �����ڸ��� �ϰ� �����ڸ� �Է� 
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
			printf("�Է� ����.");		// �߸� �Է����� ����  
			exit(1); 
		}
	}
	while (top > -1)
	{
		if (stack[top] == '(')
			pop();
		else dest[j++] = pop();
	}
		
	printf("���� ����� : %s\n",dest); 		//�߰����� ������ �̿��� ���� ���� ����� ��� 

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
			printf("%d %c %d = %d \n",a,dest[i], b, result);		//�߰� ��� ��� ��� 
			cal_push(result);
		}
		
	}
	result = cal_pop();

	printf("���� ��� : %d\n", result); 		// ���� ��� ��� 
	
}



int main(void)		//���� �Լ� 
{
	
	calculator();

	return 0; 
}
