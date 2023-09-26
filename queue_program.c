// 원형 Queue
// 2차원배열 사용
// 은행 창구 시뮬레이션(직원 전용) 
#if 1
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STRING_SIZE 10
#define MAX_STRING_LENGTH 40

typedef struct QueueType {
	// queue 데이터 (2차원배열)
	// MAX_STRING_SIZE: 개수, MAX_STRING_LENGTH: 길이
	char data[MAX_STRING_SIZE][MAX_STRING_LENGTH];
	int front, rear; // front, rear 
} QueueType;

// 초기화 하는 함수 
void init(QueueType* q) {
	// 비어있는 큐의 초기 상태설정 : rear = front = 0 
	q->front = q->rear = 0;
}

// 비어있는지 확인하는 함수 
int is_empty(QueueType* q) {
	// front와 rear가 같지 않으면 데이터가 있음 
	return (q->front == q->rear);
}

// 남아있는 요소 개수 확인하는 함수 
int remain(QueueType* q){
	return q->rear - q->front;
}

// 꽉차있는지 확인하는 함수 
int is_full(QueueType* q) {
	// rear+1에서 큐의 길이를 나눈 나머지값이 front와 같다면 큐가 가득차있는 상태
	return (q->front == ((q->rear + 1) % MAX_STRING_SIZE));
}

//큐가 가득 차있는지 확인 후 삽입 연산하는 함수 
void enqueue(QueueType* q, char *data) {
	// 큐가 가득차있는지 확인 
	if (is_full(q)) {
		printf("대기인원이 가득차있음\n\n");
	}
	else {
		// q rear: rear+1에서 큐의 길이를 나눈 나머지값 (MAX 값을 넘지않도록 1증가하는 식) 
		q->rear = (q->rear + 1) % MAX_STRING_SIZE;
		// 데이터 복사 
		strcpy(q->data[q->rear], data);
	}
}

// 큐가 비어있는지 확인 후 삭제 연산하는 함수 
char* dequeue(QueueType* q) {
	// 큐 비어있는지 확인 
	if (is_empty(q)) {
		printf("대기인원이 없습니다.\n\n");
		return NULL;
	}
	else {
		// front: rear+1에서 큐의 길이를 나눈 나머지값
		q->front = (q->front + 1) % MAX_STRING_SIZE;
		// 삭제할 문자열 저장후 리턴
		char* data = q->data[q->front];
		return data;
	}
}

//큐의 모든 요소 출력하는 함수 
void print_queue(QueueType* q) {
	// 비어있으면 
	if (is_empty(q)) {
		printf("대기인원이 없습니다.\n");
	}
	else {
		printf("\n========Queue========\n");
		if (!is_empty(q)) {
			int i = q->front;					// front 시작
			int seq = 1; 						// 순서 
			do {
				i = (i + 1) % MAX_STRING_SIZE;  // 1씩 증가하고 사이즈를 나눔(q->front와 같은 값이 나올때까지) 
				printf("%d. %s\n", seq++, q->data[i]);	// 순번과 각 요소 출력 
				if (i == q->rear)				// front와 rear 같은 위치이면 전체데이터를 출력함 
					break;
			} while (i != q->front);			
			printf("\n\n");
		}
	}
}

int main(void)
{
	char select[4]; 				// 선택 
	int i_select; 					// 선택번호
	char input[MAX_STRING_LENGTH];	// 입력데이터 
	
	QueueType queue; // 구조체 변수 선언 
	init(&queue); 	 // 큐 초기화 
	
	printf("==============은행 창구==============\n");
	while(1)
	{ 
		printf("1번 : 대기 인원 추가\n");
		printf("2번 : 서비스 완료\n");
		printf("3번 : 전체 대기표 출력\n");
		printf("4번 : 대기표 초기화\n");
		printf("5번 : 남은 대기인원수 확인\n");
		printf("999번 : 프로그램 종료\n");
		printf("===============================\n");
		
		printf("선택번호: ");
		fgets(select, 4, stdin);				// 번호 입력 
		i_select = atoi(select);				
		
		if(i_select == 1){ 						// 1. 입력 
			printf("대기인원을 입력해주세요!: ");
			fgets(input, 40, stdin); 			// 데이터 입력
			input[strlen(input) - 1] = '\0'; 	// 개행 문자제거 
			enqueue(&queue, input);				// 데이터 삽입 
			printf("\n\n");
			
		} else if(i_select == 2) { 				// 2. 삭제 
			char *dequeue_data = dequeue(&queue); 		//삭제 데이터 저장 
			if(dequeue_data != NULL){ 					// null이 아니면 삭제메세지 출력 
				printf("%s님 서비스 완료되었습니다!\n\n", dequeue_data);		
			}
			
		} else if(i_select == 3) { 				// 3. 데이터출력 
			print_queue(&queue);
			
		} else if(i_select == 4) { 				// 4. 초기화 
			init(&queue);						 
			printf("초기화가 완료되었습니다!\n\n");
			
		} else if(i_select == 5) { 				// 5. 남은 대기인원수 확인 
			printf("대기인원 수 : %d\n\n", remain(&queue));
			
		} else if(i_select == 999) { 			// 999. 종료 
			printf("프로그램을 종료합니다!\n\n");
			break;
			
		}  else { 								// 그외 다른문자입력 
			printf("잘못 입력되었습니다. 다시입력해주세요!\n\n");
			
		}	
	}
	
	return 0;
}
#endif
