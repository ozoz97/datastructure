// ���� Queue
// 2�����迭 ���
// ���� â�� �ùķ��̼�(���� ����) 
#if 1
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STRING_SIZE 10
#define MAX_STRING_LENGTH 40

typedef struct QueueType {
	// queue ������ (2�����迭)
	// MAX_STRING_SIZE: ����, MAX_STRING_LENGTH: ����
	char data[MAX_STRING_SIZE][MAX_STRING_LENGTH];
	int front, rear; // front, rear 
} QueueType;

// �ʱ�ȭ �ϴ� �Լ� 
void init(QueueType* q) {
	// ����ִ� ť�� �ʱ� ���¼��� : rear = front = 0 
	q->front = q->rear = 0;
}

// ����ִ��� Ȯ���ϴ� �Լ� 
int is_empty(QueueType* q) {
	// front�� rear�� ���� ������ �����Ͱ� ���� 
	return (q->front == q->rear);
}

// �����ִ� ��� ���� Ȯ���ϴ� �Լ� 
int remain(QueueType* q){
	return q->rear - q->front;
}

// �����ִ��� Ȯ���ϴ� �Լ� 
int is_full(QueueType* q) {
	// rear+1���� ť�� ���̸� ���� ���������� front�� ���ٸ� ť�� �������ִ� ����
	return (q->front == ((q->rear + 1) % MAX_STRING_SIZE));
}

//ť�� ���� ���ִ��� Ȯ�� �� ���� �����ϴ� �Լ� 
void enqueue(QueueType* q, char *data) {
	// ť�� �������ִ��� Ȯ�� 
	if (is_full(q)) {
		printf("����ο��� ����������\n\n");
	}
	else {
		// q rear: rear+1���� ť�� ���̸� ���� �������� (MAX ���� �����ʵ��� 1�����ϴ� ��) 
		q->rear = (q->rear + 1) % MAX_STRING_SIZE;
		// ������ ���� 
		strcpy(q->data[q->rear], data);
	}
}

// ť�� ����ִ��� Ȯ�� �� ���� �����ϴ� �Լ� 
char* dequeue(QueueType* q) {
	// ť ����ִ��� Ȯ�� 
	if (is_empty(q)) {
		printf("����ο��� �����ϴ�.\n\n");
		return NULL;
	}
	else {
		// front: rear+1���� ť�� ���̸� ���� ��������
		q->front = (q->front + 1) % MAX_STRING_SIZE;
		// ������ ���ڿ� ������ ����
		char* data = q->data[q->front];
		return data;
	}
}

//ť�� ��� ��� ����ϴ� �Լ� 
void print_queue(QueueType* q) {
	// ��������� 
	if (is_empty(q)) {
		printf("����ο��� �����ϴ�.\n");
	}
	else {
		printf("\n========Queue========\n");
		if (!is_empty(q)) {
			int i = q->front;					// front ����
			int seq = 1; 						// ���� 
			do {
				i = (i + 1) % MAX_STRING_SIZE;  // 1�� �����ϰ� ����� ����(q->front�� ���� ���� ���ö�����) 
				printf("%d. %s\n", seq++, q->data[i]);	// ������ �� ��� ��� 
				if (i == q->rear)				// front�� rear ���� ��ġ�̸� ��ü�����͸� ����� 
					break;
			} while (i != q->front);			
			printf("\n\n");
		}
	}
}

int main(void)
{
	char select[4]; 				// ���� 
	int i_select; 					// ���ù�ȣ
	char input[MAX_STRING_LENGTH];	// �Էµ����� 
	
	QueueType queue; // ����ü ���� ���� 
	init(&queue); 	 // ť �ʱ�ȭ 
	
	printf("==============���� â��==============\n");
	while(1)
	{ 
		printf("1�� : ��� �ο� �߰�\n");
		printf("2�� : ���� �Ϸ�\n");
		printf("3�� : ��ü ���ǥ ���\n");
		printf("4�� : ���ǥ �ʱ�ȭ\n");
		printf("5�� : ���� ����ο��� Ȯ��\n");
		printf("999�� : ���α׷� ����\n");
		printf("===============================\n");
		
		printf("���ù�ȣ: ");
		fgets(select, 4, stdin);				// ��ȣ �Է� 
		i_select = atoi(select);				
		
		if(i_select == 1){ 						// 1. �Է� 
			printf("����ο��� �Է����ּ���!: ");
			fgets(input, 40, stdin); 			// ������ �Է�
			input[strlen(input) - 1] = '\0'; 	// ���� �������� 
			enqueue(&queue, input);				// ������ ���� 
			printf("\n\n");
			
		} else if(i_select == 2) { 				// 2. ���� 
			char *dequeue_data = dequeue(&queue); 		//���� ������ ���� 
			if(dequeue_data != NULL){ 					// null�� �ƴϸ� �����޼��� ��� 
				printf("%s�� ���� �Ϸ�Ǿ����ϴ�!\n\n", dequeue_data);		
			}
			
		} else if(i_select == 3) { 				// 3. ��������� 
			print_queue(&queue);
			
		} else if(i_select == 4) { 				// 4. �ʱ�ȭ 
			init(&queue);						 
			printf("�ʱ�ȭ�� �Ϸ�Ǿ����ϴ�!\n\n");
			
		} else if(i_select == 5) { 				// 5. ���� ����ο��� Ȯ�� 
			printf("����ο� �� : %d\n\n", remain(&queue));
			
		} else if(i_select == 999) { 			// 999. ���� 
			printf("���α׷��� �����մϴ�!\n\n");
			break;
			
		}  else { 								// �׿� �ٸ������Է� 
			printf("�߸� �ԷµǾ����ϴ�. �ٽ��Է����ּ���!\n\n");
			
		}	
	}
	
	return 0;
}
#endif
