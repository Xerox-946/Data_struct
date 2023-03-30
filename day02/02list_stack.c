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

//入栈
void push_list_stack(ListStack* stack,TYPE val){
	Node* node=create_node(val);
	node->next=stack->top;
	stack->top=node;
	stack->cnt++;
}

//栈顶
TYPE top_list_stack(ListStack* stack){
	return stack->top->data;
}
//栈空
bool empty_list_stack(ListStack* stack){
	return stack->top==NULL;
}
//数量
size_t cnt_list_stack(ListStack* stack){
	return stack->cnt;
}

//出栈
void pop_list_stack(ListStack* stack){
	Node* temp=stack->top;
	stack->top=temp->next;
	free(temp);
	stack->cnt--;
}
//销毁
void destory_list_stack(ListStack* stack){
	while(!empty_list_stack(stack)) pop_list_stack(stack);
	free(stack);
}
int main(){
	ListStack* stack=create_list_stack();
	srand(time(NULL));
	for(int i=0;i<10;i++){
		push_list_stack(stack,rand()%100);
		if(!empty_list_stack(stack)){
			printf("top:%d\n",top_list_stack(stack));
		}
	}
	printf("-------------------\n");
	for(int i=0;i<10;i++){
		if(!empty_list_stack(stack)){
			printf("top:%d\n",top_list_stack(stack));
		}
		pop_list_stack(stack);
	}
	return 0;
}
