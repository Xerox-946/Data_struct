#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define TYPE int

// 封装带头节点的单链表
typedef struct Node{
	TYPE data;
	struct Node* next;
}Node;

Node* create_node(TYPE data){
	Node* node=malloc(sizeof(Node));
	node->data=data;
	node->next=NULL;
	return node;
}

typedef struct List{
	Node* head;	//头指针
	Node* tail;	//尾指针
	size_t size;//节点数量
}List;

//创建链表
List* create_list(){
	List* list=malloc(sizeof(List));
	list->head=create_node(7);
	list->tail=NULL;
	list->size=0;
	return list;
}

//头添加
void add_head_list(List* list,TYPE data){
	Node* node=create_node(data);
	if(!list->size){
		list->tail=node;
	}
	node->next=list->head->next;
	list->head->next=node;
	list->size++;
}
//尾添加
void add_tail_list(List* list,TYPE data){
	Node* node=create_node(data);
	if(!list->size){
		list->head->next=node;
		list->tail=node;
	}else{
		list->tail->next=node;
		list->tail=node;
	}
	list->size++;
}
//头删除
bool del_head_list(List* list){
	if(!list->size) return false;
	Node* temp=list->head->next;
	list->head->next=temp->next;
	free(temp);
	list->size--;
	if(!list->size){
		list->tail=NULL;
	}
	return true;
}
//尾删除
bool del_tail_list(List* list){
	if(!list->size) return false;
	Node* node=list->head;
	while(node->next!=list->tail) node=node->next;
	Node* temp=list->tail;
	node->next=NULL;
	list->tail=node;
	free(temp);
	list->size--;
	if(!list->size){
		list->tail=NULL;
	}
	return true;
}
//插入
bool insert_list(List* list,size_t index,TYPE data){
	if(index>list->size) return false;
	Node* add_node=create_node(data);
	Node* node=list->head;
	int i=0;
	while(i<index){
		node=node->next;
		i++;
	}
	add_node->next=node->next;
	node->next=add_node;
	list->size++;
	if(list->size==1){
		list->tail=add_node;
	}
	return true;
}
//按值删除
bool del_value_list(List* list,TYPE data){
	if(0==list->size) return false;
	if(data==list->head->next->data) del_head_list(list);
	if(data==list->tail->data) del_tail_list(list);
	for(Node* n=list->head->next;n->next;n=n->next){
		if(n->next->data==data){
			Node* temp=n->next;
			n->next=temp->next;
			free(temp);
			list->size--;
			return true;
		}
	}
	return false;
}
//按位置删除
bool del_index_list(List* list,size_t index){
	if(index>=list->size) return false;
	if(0==index) return del_head_list(list);
	if(list->size-1==index) return del_tail_list(list);

	Node* prev = list->head->next;
	for(int i=1;i<index;i++){
		prev=prev->next;
	}
	Node* node=prev->next;
	prev->next=node->next;
	free(node);
	list->size++;
	return true;
}
//按值修改
bool modify_value_list(List* list,TYPE old,TYPE new){
	int i=list->size;
	Node* node=list->head->next;
	while(i--){
		if(old==node->data){
			node->data=new;
			return true;
		}
		node=node->next;
	}
	return false;
}
//按位置修改
bool modify_index_list(List* list,size_t index,TYPE new){
	if(index>list->size) return false;
	Node* node=list->head->next;
	int i=0;
	while(!node){
		if(i==index){
			node->data=new;
			return true;
		}
		i++;
		node=node->next;
	}
	return false;
}
//查询
size_t query_list(List* list,TYPE val){
	Node* node=list->head->next;
	for(int i=0;i<list->size;i++){
		if(node->data==val){
			return i;
		}
		node=node->next;
	}
	return -1;
}
//访问
bool access_list(List* list,size_t index,TYPE* val){
	Node* node=list->head->next;
	for(int i=0;i<list->size;i++){
		if(index==i){
			*val=node->data;
			return true;
		}
		node=node->next;
	}
	return false;
}
//排序
void sort_list(List* list){
	for(Node* i=list->head->next;i->next;i=i->next){
		for(Node* j=i->next;j;j=j->next){
			if(i->data>j->data){
				TYPE temp=i->data;
				i->data=j->data;
				j->data=temp;
			}
		}
	}
}
//遍历
void show_list(List* list){
	for(Node* node=list->head->next;node;node=node->next){
		printf("%d ",node->data);
	}
	printf("\n");
}
//清空
void clear_list(List* list){
	while(list->size) del_head_list(list);
}
//销毁
void destroy_list(List* list){
	clear_list(list);
	free(list->head);
	free(list);
}

int main(){
	List* list=create_list();
	srand(time(NULL));
	for(int i=0;i<10;i++){
		insert_list(list,0,rand()%100);
	}	
	show_list(list);
	sort_list(list);
	show_list(list);
	clear_list(list);
	show_list(list);
	destroy_list(list);
	return 0;
}
