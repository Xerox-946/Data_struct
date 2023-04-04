#include <stdio.h>
#include <stdlib.h>
#include "list.h"

//创建节点
static ListNode* create_list_node(void* ptr){
	ListNode* node=malloc(sizeof(ListNode));
	node->ptr=ptr;
	node->prev=node;
	node->next=node;
	return node;
}

//创建链表
List* create_list(void){
	List* list=malloc(sizeof(List));
	list->head=create_list_node(NULL);
	list->size=0;
	return list;
}

static void  _add_list(ListNode* p,ListNode* n,void* ptr){
	ListNode* node=create_list_node(ptr);
	p->next=node;
	node->next=n;
	n->prev=node;
	node->prev=p;
}

//头添加
void add_head_list(List* list,void* ptr){
	_add_list(list->head,list->head->next,ptr);
	list->size++;
}
//尾添加
void add_tail_list(List* list,void* ptr){
	_add_list(list->head->prev,list->head,ptr);
	list->size++;
}
//删除节点
static void _del_list(ListNode* node){
	node->next->prev=node->prev;
	node->prev->next=node->next;
	free(node->ptr);
	free(node);
}

//按位置访问节点
static ListNode* _index_list(List* list,size_t index){
	if(index>=list->size) return NULL;
	if(index<list->size/2){
		ListNode* node=list->head->next;
		while(index--)	node=node->next;
		return node;
	}else{
		ListNode* node=list->head->prev;
		while(++index<list->size) node=node->prev;
		return node;
	}
}

//插入
bool insert_list(List* list,size_t index,void* ptr){
	if(index==0 && list->size==0) add_head_list(list,ptr);
	ListNode* node=_index_list(list,index);
	if(!node) return false;
	_add_list(node->prev,node,ptr);
	list->size++;
	return true;
}

//按位置删除
bool del_index_list(List* list,size_t index){
	ListNode* node=_index_list(list,index);
	if(!node) return false;
	_del_list(node);
	list->size--;
	return true;
}

//遍历
void show_list(List* list,void (*show)(void *)){
	for(ListNode* n=list->head->next;n!=list->head;n=n->next){
		show(n->ptr);
	}
}

//按值删除
bool del_value_list(List* list,void* ptr,Compar compar){
	for(ListNode* n=list->head->next;n!=list->head;n=n->next){
		if(compar(ptr,n->ptr)==0){
			_del_list(n);
			list->size--;
			return true;
		}
	}
	return false;
}

//查询
void* query_list(List* list,void* ptr,Compar compar){
	for(ListNode* n=list->head->next;n!=list->head;n=n->next){
		if(compar(ptr,n->ptr)==0){
			return n->ptr;
		}
	}
	return NULL;
}
//访问
void* access_list(List* list,size_t index){
	ListNode* node= _index_list(list,index);
	if(!node) return NULL;
	return node->ptr;
}
//排序
void sort_list(List* list,Compar compar){
	for(ListNode* i=list->head->next;i!=list->head->prev;i=i->next){
		for(ListNode* j=i->next;j!=list->head;j=j->next){
			if(compar(i->ptr,j->ptr)<0){
				void* temp=i->ptr;
				i->ptr=j->ptr;
				j->ptr=temp;
			}
		}
	}
}
//清空
void clear_list(List* list){
	ListNode* n=list->head->next;
	while(n!=list->head){
		ListNode* temp=n;
		n=n->next;
		free(temp->ptr);
		free(temp);
	}
	/*
	while(list->size){
		del_index_list(list,0);
	}
	*/
	list->head->next=list->head;
	list->head->prev=list->head;
	list->size=0;
}
//销毁
void destroy_list(List* list){
	clear_list(list);
	free(list->head);
	free(list);
}
