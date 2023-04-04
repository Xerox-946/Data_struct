#ifndef LIST_H
#define LIST_H

#include <stdbool.h>

//通用链表

typedef int (*Compar)(const void*,const void*);

//链表节点
typedef struct ListNode{
	void* ptr;
	struct ListNode* prev;
	struct ListNode* next;
}ListNode;

//链表结构
typedef struct List{
	ListNode* head;
	size_t size;
}List;

//创建链表
List* create_list(void);
//头添加
void add_head_list(List* list,void* ptr);
//尾添加
void add_tail_list(List* list,void* ptr);
//插入
bool insert_list(List* list,size_t index,void* ptr);
//按位置删除
bool del_index_list(List* list,size_t index);
//按值删除
bool del_value_list(List* list,void* ptr,Compar compar);
//查询
void* query_list(List* list,void* ptr,Compar compar);
//访问
void* access_list(List* list,size_t index);
//排序
void sort_list(List* list,Compar compar);
//清空
void clear_list(List* list);
//销毁
void destroy_list(List* list);
//遍历
void show_list(List* list,void (*show)(void *));


#endif//LIST_H
