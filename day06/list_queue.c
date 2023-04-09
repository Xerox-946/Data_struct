#include "list_queue.h"
#define TYPE char

//创建节点
Node* create_node(TYPE data){
	Node* node=malloc(sizeof(Node));
	node->data=data;
	node->next=NULL;
	return node;
}

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
