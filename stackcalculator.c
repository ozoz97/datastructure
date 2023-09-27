/************************
���� ���� ����  
*************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 30			//stack ������ 

char stack[MAX_STACK_SIZE];			//���ü��� 
int stack_cal[MAX_STACK_SIZE];		//int�� ���� ���� 
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

void cal_push(int value)  // ��� �� int��  ���� �� ���� 
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

int cal_pop()	 // ��� �� int�� ���� �� ���� 
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

	for (i = 0; i < strlen(src)-1; i++)					//���� ǥ����� ����ϱ� ���� ���� ǥ�⺱���� �ٲ��ش� 
	{
		if (src[i] >= '0' && src[i] <= '9')				//�ǿ����ڴ� �ٷ� �ű� �� 
			dest[j++] = src[i];
		else if (src[i] == '*'|| src[i] =='/')			// *, / �����ڸ� ���� �� 
		{
			if (top == -1 || stack[top] == '(')			// ���ÿ� �����ڰ� ��������� ���ÿ� ��´� 
				push(src[i]);							// ( �ڿ� �Ȱ��� ��������� ���ÿ� ��´� 
			else if (stack[top] == '+' || stack[top] == '-')	// �ڽź��� �켱������ ���� ������+, -�� �������Ƿ� 
				push(src[i]);								// ���ÿ� �����ڸ� �ٷ� �״´� 
			else
			{
				dest[j++] = pop();							// �ڽź��� �켱������ ���� ������ *, /�� ������ 
				push(src[i]);								// ���ÿ� ��� �����ڸ� ������ ���� �����ڸ� �״´� 
			}
		}
		else if (src[i] == '+'||src[i] == '-')				// +, - �����ڸ� ������  
		{
			if (top == -1|| stack[top] == '(') 				// ���ÿ� �����ڰ� ����ְų� (�� ������  
				push(src[i]);								// ���ÿ� ��´� 
			else
			{
				while(stack[top] == '+' || stack[top] == '-'||stack[top] == '*' || stack[top] == '/')
				{								// �ڽź��� �켱������ ���ų� ���� �����ڸ� ������ 
					dest[j++] = pop();			// ���ÿ� ��� �����ڸ� ������  
					
				}
				push(src[i]);					// ���� �����ڸ� �״´�					
			}
		}
		else if (src[i] == '(')					// (�� ������ ���ÿ� ��´� 
			push(src[i]);
		else if (src[i] == ')')					// )�� ������ 
		{
			while (stack[top] != '(')			// ( �� ���������� ���ÿ� ��� �����ڸ� ���� ������ 
				dest[j++] = pop();
			pop();								// (�� ���� ������ �����Ѵ� 
		}			
		else 
		{
			printf("�Է� ����.");		// �߸� �Է����� ����  
			exit(1); 
		}
	}
	while (top > -1)					// �������� ���ÿ� ���� �����ڸ� ���� �����ְ� (�� ���� ������ �����Ѵ�  
	{
		if (stack[top] == '(')			// (�� ���� ������ �����Ѵ�
			pop();
		else dest[j++] = pop();
	}
		
	printf("���� ����� : %s\n",dest); 		//�߰����� ������ �̿��� ���� ���� ����� ��� 

	for (i = 0; i < strlen(dest); i++)
	{
		if (dest[i] >= '0' && dest[i] <= '9')	// �ǿ����ڸ� ������ 
		{
			k = dest[i] - 48;				// ���ڷ� �� ������� ���ڷ� ��ȯ 
			cal_push(k);					// int������ �� �ٸ� ���ÿ� ��´� 
		}
		else if (dest[i] == '+' || dest[i] == '-' || dest[i] == '*' || dest[i] == '/')
		{									// �����ڸ� ������ 
			b = cal_pop();					// ó�� ������ ���� ������ 
			a = cal_pop();					// �ι�° ������ ���� �ڷ� �ؼ� 
			result = func(dest[i],a,b);		// �Լ��� ����� ����� �Ѵ� 
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
