// Circular queue[][] 일단 좀더 생각해보자.  
#if 0
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME 50 //사람 이름 
#define MEMBER 8 //멤버 수 

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

void init_q(cir_Q *q) //queue 만들기  
{
	q->rear = q->front =0;
}

int full(cir_Q *q)
{
	return (q->rear +1)%MEMBER == q->front; 
	//front 값이 rear 값보다 하나 앞서는 경우 
}
int empty(cir_Q *q)
{
	return q->rear == (q->front); 
	//front 값이 rear 값과 같은 경우 
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


//main 프로그램 작성 
int main(void)
{
	cir_Q queue;
	init_q(&queue);
	
	char input1[50],input2[4];
	int number,j,num=1; 
	
	printf("------멤버 이름 입력하기------\n");

	while(1)
	{
		printf("%d번째 이름 입력: ",num);
		fgets(input1, 50, stdin);
		enqueue(&queue, input1);
		if(full(&queue))
		{
			break;
			printf("완료!");
		}
		num++;	
	}
	printf("\n");
	printf("----------벌칙자  뽑기----------\n"); 
	//입력한 번호 n명 빼고 남은 사람 중 첫번째가 벌칙자 
	
	printf("번호  입력: ");
	fgets(input2, 4, stdin);
	number = atoi(input2);
	printf("\n");
		
	for(j =0 ; j<number;j++)
	{
		dequeue(&queue);
	}	
	
	printf("----------벌칙자 당첨---------\n");
	printf("%5s", queue.data[j]); // 마지막 남은 사람 이름 뽑기  
	
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
	//학생 학번과 이름을 입력하기
	char input[100];
	
	printf("과제 제출한 학생의 학번과 이름 입력하세요: ");
	fgets(input,100,stdin);
	 
	
	//발표 순서 리스트 출력하기  
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
typedef struct DListNode {	// 이중연결 노드 타입
	element data;			//데이터 필드 
	struct DListNode* llink;//왼쪽 링크 필드 
	struct DListNode* rlink;//오른쪽 링크 필드 
} DListNode;

DListNode* current; //노드 링크 선언
DListNode* here; //노드 링크 선언    

// 이중 연결 리스트를 초기화
void init(DListNode* phead)
{
	phead->llink = phead;
	phead->rlink = phead;
}

// 이중 연결 리스트의 노드를 출력
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

// 새로운 데이터를 노드 before의 오른쪽에 삽입
void dinsert(DListNode *before, element data)
{
	DListNode *newnode = (DListNode *)malloc(sizeof(DListNode));
	strcpy(newnode->data, data);
	newnode->llink = before;
	newnode->rlink = before->rlink;
	before->rlink->llink = newnode;
	before->rlink = newnode;
}

// 노드 removed를 삭제
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
		printf("\n명령어를 입력하시오(<, >, -,q): ");
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
				
				printf("넣을 곡 입력하세요: ");
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
