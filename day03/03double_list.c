#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#define TYPE int

//演示双向链表的特点
typedef struct Node{
	struct Node* prev;
	TYPE data;
	struct Node* next;
}Node;

//创建节点
Node* create_node(TYPE data){
	Node* node=malloc(sizeof(Node));
	node->data=data;
	node->prev=node;
	node->next=node;
	return node;
}

void _add_list(Node* n1,Node* n2,TYPE data){
	Node* node=create_node(data);
	node->prev=n1;
	node->next=n2;
	n1->next=node;
	n2->prev=node;
}

//头添加
void add_head_list(Node* head,TYPE data){
	_add_list(head,head->next,data);
}

//尾添加
void add_tail_list(Node* head,TYPE data){
	_add_list(head->prev,head,data);
}

//插入
bool insert_list(Node* head,size_t index,TYPE data){
	Node* node=head->next;
	int i=0;
	if(node->next==head){
		add_head_list(head,data);
	}
	while(head!=node){
		if(i==index){
			_add_list(node->prev,node,data);
			return true;
		}
		i++;
		node=node->next;
	}
	return false;
}

void _del_list(Node* node){
	node->prev->next=node->next;
	node->next->prev=node->prev;
	free(node);
}

bool del_index_list(Node* head,size_t index){
	Node* n=head->next;
	for(int i=0;i<index;i++){
		n=n->next;
		if(head==n) return false;
	}
	_del_list(n);
	return true;
}

bool del_value_list(Node* head,TYPE data){
	for(Node* n=head->next;head!=n;n=n->next){
		if(n->data==data){
			_del_list(n);
			return true;
		}
	}
	return false;
}

//遍历
void show_list(Node* head){
	for(Node* n=head->next;n!=head;n=n->next){
		printf("%d ",n->data);
	}
	printf("\n");
}

int main(){
	srand(time(NULL));
	Node* head=create_node(7);//带头节点
	for(int i=0;i<10;i++){
		insert_list(head,0,rand()%100);
	}
	show_list(head);
}
