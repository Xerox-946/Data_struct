#ifndef LIST_QUEUE_H
#define LIST_QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define TYPE char

//设计单链表的节点
typedef struct Node{
	TYPE data;//节点的数据域
	struct Node* next;//节点的指针域
}Node;

//创建节点
Node* create_node(TYPE data);

typedef struct ListQueue{
	Node* head;
	Node* tail;
	size_t cnt;
}ListQueue;

//创建
ListQueue* create_list_queue(void);
//队空
bool empty_list_queue(ListQueue* queue);
//出队
bool pop_list_queue(ListQueue* queue);
//销毁
void destroy_list_queue(ListQueue* queue);
//入队
void push_list_queue(ListQueue* queue,TYPE val);
//队头
TYPE head_list_queue(ListQueue* queue);
//队尾
TYPE tail_list_queue(ListQueue* queue);
//数量
size_t cnt_list_queue(ListQueue* queue);

#endif//LIST_QUEUE_H
