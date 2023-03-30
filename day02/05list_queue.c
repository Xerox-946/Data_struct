#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define TYPE int

//设计单链表的节点
typedef struct Node{
	TYPE data;//节点的数据域
	struct Node* next;//节点的指针域
}Node;

//创建节点
Node* create_node(TYPE data){
	Node* node=malloc(sizeof(Node));
	node->data=data;
	node->next=NULL;
	return node;
}

typedef struct ListQueue{
	Node* head;
	Node* tail;
	size_t cnt;
}ListQueue;

//创建
ListQueue* create_list_queue(void){
	ListQueue* queue=malloc(sizeof(ListQueue));
	queue->head=NULL;
	queue->tail=NULL;
	queue->cnt=0;
	return queue;
}
//队空
bool empty_list_queue(ListQueue* queue){
	return !queue->cnt;
}
//出队
bool pop_list_queue(ListQueue* queue){
	if(empty_list_queue(queue))return false;
	if(queue->cnt==1){
		queue->tail=NULL;
	}
	Node* temp=queue->head;
	queue->head=temp->next;
	free(temp);
	queue->cnt--;
	return true;
}
//销毁
void destroy_list_queue(ListQueue* queue){
	while(pop_list_queue(queue));
	free(queue);
}
//入队
void push_list_queue(ListQueue* queue,TYPE val){
	Node* node=create_node(val);
	if(empty_list_queue(queue)){
		queue->head=node;
		queue->tail=node;
	}else{
		queue->tail->next=node;
		queue->tail=node;
	}
	queue->cnt++;
}
//队头
TYPE head_list_queue(ListQueue* queue){
	return queue->head->data;
}
//队尾
TYPE tail_list_queue(ListQueue* queue){
	return queue->tail->data;
}
//数量
size_t cnt_list_queue(ListQueue* queue){
	return queue->cnt;
}

int main(){
	srand(time(NULL));
	ListQueue* queue=create_list_queue();
	for(int i=0;i<10;i++){
		push_list_queue(queue,rand()%100);
		printf("tail:%2d size:%d\n",tail_list_queue(queue),cnt_list_queue(queue));
	}
	printf("-------------------------------------\n");
	while(queue->tail!=NULL){
		printf("head:%2d size:%d\n",head_list_queue(queue),cnt_list_queue(queue));
		pop_list_queue(queue);
	}
	destroy_list_queue(queue);
	queue=NULL;
	return 0;
}
