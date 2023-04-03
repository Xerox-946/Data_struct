#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define TYPE int

typedef struct Node{
	TYPE data;
	struct Node* prev;
	struct Node* next;
}Node;

Node* create_Node(TYPE data){
	Node* node=malloc(sizeof(Node));
	node->data=data;
	node->prev=node;
	node->next=node;
	return node;
}

//双链表结构
typedef struct DoubleList{
	Node* head;
	size_t size;
}DoubleList;

DoubleList* create_doublelist(void){
	Node* node=create_Node(7);
	DoubleList* list=malloc(sizeof(DoubleList));
	list->head=node;
	list->size=0;
	return list;
}

//1.在两个节点之间添加一个节点
void _add_list(Node* p,Node* n,TYPE data){
	Node* node=malloc(sizeof(Node));
	node->data=data;
	p->next=node;
	node->next=n;
	n->prev=node;
	node->prev=p;
}

//2.删除当前节点
void _del_list(Node* node){
	node->prev->next=node->next;
	node->next->prev=node->prev;
	free(node);
}
//3.访问链表中指定位置的节点
Node* _index_node(DoubleList* list,size_t index){
	if(index>=list->size) return NULL;
	if(index<list->size/2){
		//从前往后找
		Node* n=list->head->next;
		while(index--) n=n->next;
		return n;
	}else{
		//从后往前找
		Node* n=list->head->prev;
		while(++index<list->size) n=n->prev;
		return n;
	}
}

//4.通过访问链表中指定数值的节点
Node* _value_node(DoubleList* list,TYPE data,int *num){
	*num=0;
	for(Node* n=list->head->next;n!=list->head;n=n->next){
		if(n->data==data) return n;
		(*num)++;
	}
	return NULL;
}

//头添加
void add_head_list(DoubleList* list,TYPE data){
	_add_list(list->head,list->head->next,data);
	list->size++;
}

//尾添加
void add_tail_list(DoubleList* list,TYPE data){
	_add_list(list->head->prev,list->head,data);
	list->size++;
}

//插入
bool insert_list(DoubleList* list,size_t index,TYPE data){
	if(!list->size){ 
		add_head_list(list,data);
		return true;
	}
	Node* node=_index_node(list,index);
	if(!node) return false;
	_add_list(node->prev,node,data);
	list->size++;
	return true;
}

//按位置删除
bool del_index_list(DoubleList* list,size_t index){
	Node* node=_index_node(list,index);
	if(!node) return false;
	_del_list(node);
	list->size--;
	return true;
}

//按值删除
bool del_value_list(DoubleList* list,TYPE val){
	int num=0;
	Node* node=_value_node(list,val,&num);
	if(!node) return false;
	_del_list(node);
	list->size--;
	return true;
}

//按位置修改
bool modify_index_list(DoubleList* list,size_t index,TYPE val){
	Node* node=_index_node(list,index);
	if(!node) return false;
	node->data=val;
	return true;
}

//按值修改
int modify_value_list(DoubleList* list,TYPE old,TYPE val){
	int num=0;
	Node* node=_value_node(list,old,&num);
	if(!node) return -1;
	node->data=val;
	return num;
}
//按值全部修改
int modify_values_list(DoubleList* list,TYPE old,TYPE val){
	int num=0;
	for(Node* node=list->head->next;node!=list->head;node=node->next){
		if(node->data==old){
			num++;
			node->data=val;
		}
	}
	return num;
}

//访问
bool access_list(DoubleList* list,size_t index,TYPE* val){
	Node* node=_index_node(list,index);
	if(!node) return false;
	*val=node->data;
	return true;
}

//查询
int query_list(DoubleList* list,TYPE val){
	int num=0;
	Node* node=_value_node(list,val,&num);
	if(!node) return -1;
	return num;
}

//遍历
void show_list(DoubleList* list){
	for(Node* n=list->head->next;n!=list->head;n=n->next){
		printf("%d ",n->data);
	}
	printf("\n");
}

//清空
/*void clear_list(DoubleList* list){
	while(list->size){
		del_index_list(list,0);
	}
}
*/

void clear_list(DoubleList* list){
	Node* n=list->head->next;
	while(n!=list->head){
		Node* temp=n;
		n=n->next;
		free(temp);
	}
	list->head->next=list->head;
	list->head->prev=list->head;
	list->size=0;
}

//销毁
void destroy_list(DoubleList* list){
	clear_list(list);
	free(list->head);
	free(list);
}

int main(){
	DoubleList* list=create_doublelist();
	for(int i=0;i<10;i++){
		insert_list(list,0,i+10);
	}
	show_list(list);
	printf("num=%d\n",query_list(list,12));
	clear_list(list);
	destroy_list(list);
	list=NULL;
	return 0;
}
