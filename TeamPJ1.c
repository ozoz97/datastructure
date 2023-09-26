// Circular queue[][] �ϴ� ���� �����غ���.  
#if 0
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME 50 //��� �̸� 
#define MEMBER 8 //��� �� 

typedef struct 
{
	int front;
	int rear;
    char data[MEMBER][NAME];
}cir_Q;


void error(char *message);
void init_q(cir_Q *q);
int full(cir_Q *q);
int empty(cir_Q *q);
void enqueue(cir_Q *q, char *in);
void dequeue(cir_Q *q);

char input[50];

void error(char *message)
{
	fprintf(stderr, "%s\n",message);
	exit(1);
}

void init_q(cir_Q *q) //queue �����  
{
	q->rear = q->front =0;
}

int full(cir_Q *q)
{
	return (q->rear +1)%MEMBER == q->front; 
	//front ���� rear ������ �ϳ� �ռ��� ��� 
}
int empty(cir_Q *q)
{
	return q->rear == (q->front); 
	//front ���� rear ���� ���� ��� 
}

void enqueue(cir_Q *q, char *in)
{
	if(full(q))
	{
		error("OVERFLOW!!");
		return;
	} 
	q->rear = (q->rear+1)%MEMBER;
    strcpy(q->data[q->rear], in);
}
void dequeue(cir_Q *q)
{
	if(empty(q))
	{
		error("UNDERFLOW!!");
		return;
	}
	q->front+=1;
	q->front %= MEMBER; 
	return q->data[q->front];
}


//main ���α׷� �ۼ� 
int main(void)
{
	cir_Q queue;
	init_q(&queue);
	
	char input1[50],input2[4];
	int number,j,num=1; 
	
	printf("------��� �̸� �Է��ϱ�------\n");

	while(1)
	{
		printf("%d��° �̸� �Է�: ",num);
		fgets(input1, 50, stdin);
		enqueue(&queue, input1);
		if(full(&queue))
		{
			break;
			printf("�Ϸ�!");
		}
		num++;	
	}
	printf("\n");
	printf("----------��Ģ��  �̱�----------\n"); 
	//�Է��� ��ȣ n�� ���� ���� ��� �� ù��°�� ��Ģ�� 
	
	printf("��ȣ  �Է�: ");
	fgets(input2, 4, stdin);
	number = atoi(input2);
	printf("\n");
		
	for(j =0 ; j<number;j++)
	{
		dequeue(&queue);
	}	
	
	printf("----------��Ģ�� ��÷---------\n");
	printf("%5s", queue.data[j]); // ������ ���� ��� �̸� �̱�  
	
	return 0;
}
#endif
// Stack
#if 0
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 30

typedef struct student
{
	int student_num;
	char student_name[MAX];	
}student;

typedef struct
{
	student *data;
	int capacity;
	int top;
}stack;

void init_stack(stack *s)
{
	s->top=-1;
	s->capacity==1;
	s->data=(student *)malloc(sizeof(student)*s->capacity);
}
int is_empty(stack *s)
{
	return s->top==-1; 
}
int is_full(stack *s)
{
	return s->top==(s->capacity-1);
}
void push(stack *s,student obj)
{
	if(is_full(s))
	{
		s->capacity *=2;
		s->data=(student *)realloc(s->data,sizeof(student)*s->capacity);
	}
	s->data[++s->top]=obj;
}
student pop(stack *s)
{
	if(is_empty(s))
	{
		fprintf(stderr,"UNDERFLOW...\n");
		exit(1);
	}else
		return s->data[s->top--];
}
student peek(stack *s)
{
	if(is_empty(s))
	{
		fprintf(stderr,"UNDERFLOW...\n");
		exit(1);
	}else
		return s->data[s->top];
}

int main(void)
{
	stack s;
	init_stack(&s);
	//�л� �й��� �̸��� �Է��ϱ�
	char input[100];
	
	printf("���� ������ �л��� �й��� �̸� �Է��ϼ���: ");
	fgets(input,100,stdin);
	 
	
	//��ǥ ���� ����Ʈ ����ϱ�  
//	student jws=
//	{
//		1915817,"JINWOOSUN"
//	};
	student object;
	
	push(&s,jws);
    object=pop(&s);

    printf("student number:%d\n",object.student_num);
    printf("student name:%s\n",object.student_name);
    
	return 0;
}
#endif



// Linked list
#if 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef char element[100];
typedef struct DListNode {	// ���߿��� ��� Ÿ��
	element data;			//������ �ʵ� 
	struct DListNode* llink;//���� ��ũ �ʵ� 
	struct DListNode* rlink;//������ ��ũ �ʵ� 
} DListNode;

DListNode* current; //��� ��ũ ����
DListNode* here; //��� ��ũ ����    

// ���� ���� ����Ʈ�� �ʱ�ȭ
void init(DListNode* phead)
{
	phead->llink = phead;
	phead->rlink = phead;
}

// ���� ���� ����Ʈ�� ��带 ���
void print_dlist(DListNode* phead)
{
	DListNode* p;
	for (p = phead->rlink; p != phead; p = p->rlink) {
        if (p == current)
		    printf("<<| #%s# |>> ", p->data);
        else
            printf("<<| %s |>> ", p->data);
	}
	printf("\n");
}

// ���ο� �����͸� ��� before�� �����ʿ� ����
void dinsert(DListNode *before, element data)
{
	DListNode *newnode = (DListNode *)malloc(sizeof(DListNode));
	strcpy(newnode->data, data);
	newnode->llink = before;
	newnode->rlink = before->rlink;
	before->rlink->llink = newnode;
	before->rlink = newnode;
}

// ��� removed�� ����
void ddelete(DListNode* head, DListNode* removed)
{
	if (removed == head) return;
	removed->llink->rlink = removed->rlink;
	removed->rlink->llink = removed->llink;
	free(removed);
}



int main(void)
{
	char input[100];
	char ch;
	DListNode* head = (DListNode *)malloc(sizeof(DListNode));
	init(head);

	dinsert(head, "HARD");
	dinsert(head, "Blue");
	dinsert(head, "Good & Great");
	dinsert(head, "Advice");
	dinsert(head, "Chase");
	
	current = head->rlink;
	//print_dlist(head);
	 
	do {
		print_dlist(head);
		printf("\n��ɾ �Է��Ͻÿ�(<, >, -,q): ");
		ch = getchar();
		switch(ch)
		{
			case '<':
				current = current->llink;
				if(current == head)
					current = current->llink;
				break;
			case '>':
				current = current->rlink;
				if(current == head)
					current = current->rlink;
				break;
			case '-':
				ddelete(head,current);
				break;
			case '+':
				
				printf("���� �� �Է��ϼ���: ");
				scanf("%s",&input);
				here = head->llink;
				dinsert(here,input);
				
				break;
		}
		
		getchar();
	} while (ch != 'q');
	return 0;
}
#endif
