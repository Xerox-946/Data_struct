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

typedef struct ListStack{
	Node* top;
	size_t cnt;
}ListStack;

//创建
ListStack* create_list_stack(void){
	ListStack* stack=malloc(sizeof(ListStack));
	stack->top=NULL;
	stack->cnt=0;
	return stack;
}

typedef struct ListQueue{
	ListStack* stack1;
	ListStack* stack2;
}ListQueue;

//创建队列
ListQueue* create_list_queue(void){
	ListQueue* queue=malloc(sizeof(ListQueue));
	queue->stack1=create_list_stack();
	queue->stack2=create_list_stack();
	return queue;
}
//入栈
void push_list_stack(ListStack* stack,TYPE val){
	Node* node=create_node(val);
	node->next=stack->top;
	stack->top=node;
	stack->cnt++;
}
//入队
void push_list_queue(ListQueue* queue,TYPE val){
	push_list_stack(queue->stack1,val);
}

//栈顶
TYPE top_list_stack(ListStack* stack){
	return stack->top->data;
}

//栈空
bool empty_list_stack(ListStack* stack){
	return stack->top==NULL;
}
//队空
bool empty_list_queue(ListQueue* queue){
	return empty_list_stack(queue->stack1)&&empty_list_stack(queue->stack2);
}

//出栈
void pop_list_stack(ListStack* stack){
	Node* temp=stack->top;
	stack->top=temp->next;
	free(temp);
	stack->cnt--;
}
//出队
void pop_list_queue(ListQueue* queue){
	if(empty_list_stack(queue->stack2)){
		while(empty_list_stack(queue->stack1)){
			push_list_stack(queue->stack2,top_list_stack(queue->stack1));
			pop_list_stack(queue->stack1);
		}
	}
	pop_list_stack(queue->stack2);
}

//队头
TYPE head_list_queue(ListQueue* queue){
	if(empty_list_stack(queue->stack2)){
		while(!empty_list_stack(queue->stack1)){
			push_list_stack(queue->stack2,top_list_stack(queue->stack1));
			pop_list_stack(queue->stack1);
		}
	}
	return top_list_stack(queue->stack2);
}
//队尾
TYPE tail_list_queue(ListQueue* queue){
	if(empty_list_stack(queue->stack1)){
		while(!empty_list_stack(queue->stack2)){
			push_list_stack(queue->stack1,top_list_stack(queue->stack2));
			pop_list_stack(queue->stack2);
		}
	}
	return top_list_stack(queue->stack1);
}

//数量
size_t cnt_list_stack(ListStack* stack){
	return stack->cnt;
}
size_t cnt_list_queue(ListQueue* queue){
	return cnt_list_stack(queue->stack1)+cnt_list_stack(queue->stack2);
}

//销毁
void destory_list_stack(ListStack* stack){
	while(!empty_list_stack(stack)) pop_list_stack(stack);
	free(stack);
}

void destory_list_queue(ListQueue* queue){
	destory_list_stack(queue->stack1);
	destory_list_stack(queue->stack2);
	free(queue);
}
int main(){
	ListQueue* queue=create_list_queue();
	for(int i=0;i<10;i++){
		push_list_queue(queue,i+10);
		printf("%d head=%d tail=%d\n",cnt_list_queue(queue),head_list_queue(queue),tail_list_queue(queue));
	}
	printf("--------------------------\n");
	for(int i=0;i<10;i++){
		printf("%d head=%d tail=%d\n",cnt_list_queue(queue),head_list_queue(queue),tail_list_queue(queue));
		pop_list_queue(queue);
	}
	return 0;
}
