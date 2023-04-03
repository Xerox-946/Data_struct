#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

//Linux 内核链表
typedef struct Node{
	struct Node* prev;
	struct Node* next;
}Node;

//创建链表
Node* create_list(void){
	Node* head=malloc(sizeof(Node));
	head->prev=head;
	head->next=head;
	return head;
}

void _add_list(Node* p,Node* n,Node* node){
	n->prev=node;
	node->next=n;
	p->next=node;
	node->prev=p;
}

//头添加
void add_head_list(Node* head,Node* node){
	_add_list(head,head->next,node);
}

//尾添加
void add_tail_list(Node* head,Node* node){
	_add_list(head->prev,head,node);
}

//遍历
#define list_for_each(head,pos)\
	for(pos=head->next;pos!=head;pos=pos->next)

//计算某个结构成员与结构首地址相差多少字节
#define offset(type,member) ((int)&(((type*)0)->member))
//计算出某个结构成员所处的结构变量的首地址
#define mem_to_obj(ptr,type,member)\
	((type*)((char*)ptr-offset(type,member)))

//第二种遍历结构
//obj结构指针 head链表头节点 member节点在结构中的成员名
#define list_for_each_entry(obj,head,member)\
	for(obj=mem_to_obj(head->next,typeof(*obj),member);\
	&obj->member!=head;\
	obj=mem_to_obj(obj->member.next,typeof(*obj),member))

/*************以下是调用者要写的代码************/

typedef struct Student{
	char name[20];
	char sex;
	char age;
	float score;
	Node node;
	int id;
}Student;

int main(){
	srand(time(NULL));
	Node* head=create_list();
	for(int i=0;i<10;i++){
		Student* stu=malloc(sizeof(Student));
		sprintf(stu->name,"hehe%d",i);
		stu->sex=i%2?'w':'m';
		stu->age=18+i%2;
		stu->score=rand()%100;
		stu->id=10001+i;
		add_head_list(head,&stu->node);
	}

	/*Node* node=NULL;
	list_for_each(head,node){
		Student* stu=mem_to_obj(node,Student,node);
		printf("%s %c %hhd %f %d\n",stu->name,stu->sex,stu->age,stu->score,stu->id);
	}*/
	Student* stu=NULL;
	list_for_each_entry(stu,head,node){
		printf("%s %c %hhd %f %d\n",stu->name,stu->sex,stu->age,stu->score,stu->id);
	}
}
