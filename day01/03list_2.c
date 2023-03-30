#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

//头添加
void add_head_list(Node* head,TYPE data){
	Node* node=create_node(data);
	node->next=head->next;
	head->next=node;
}

//尾添加
void add_tail_list(Node* head,TYPE data){
	Node* node=create_node(data);
	Node* n=head;
	for(;n->next!=NULL;n=n->next);
	n->next=node;
}

//删除 按值删除
bool delete_value_list(Node* head,TYPE data){
	Node* n=head;
	while(n->next!=NULL){
		if(n->next->data==data){
			Node* temp=n->next;
			n->next=temp->next;
			free(temp);
			return true;
		}
		n=n->next;
	}
	return false;
}
//删除 按位置删除
bool delete_index_list(Node* head,size_t index){
	int i=0;
	for(Node* n=head;n->next!=NULL;n=n->next,i++){
		if(index==i){
			Node* temp=n->next;
			n->next=temp->next;
			free(temp);
			return true;
		}
	}
	return false;
}

//插入
bool insert_list(Node* head,size_t index,TYPE val){
	int i=0;
	for(Node* n=head;n!=NULL;n=n->next,i++){
		if(i==index){
			Node* node=create_node(val);
			node->next=n->next;
			n->next=node;
			return true;
		}
	}
	return false;
}
//修改
bool modify_index_list(Node* head,size_t index,TYPE val){
	int i=0;
	for(Node* n=head->next;n!=NULL;n=n->next,i++){
		if(i==index){
			n->data=val;
			return true;
		}
	}
	return false;
}
bool modify_value_list(Node* head,TYPE old,TYPE val){
	for(Node* n=head->next;n!=NULL;n=n->next){
		if(old==n->data){
			n->data=val;
			return true;
		}
	}
	return false;
}
//访问
bool access_list(Node* head,size_t index,TYPE* val){
	int i=0;
	for(Node* n=head->next;n!=NULL;n=n->next,i++){
		if(i==index){
			*val=n->data;
			return true;
		}
	}
	return false;
}
//查询
int query_list(Node* head,TYPE val){
	int i=0;
	for(Node* n=head->next;n!=NULL;n=n->next,i++){
		if(n->data==val){
			return i;
		}
	}
	return -1;
}
//遍历
void show_list(Node* head){
	for(Node* n=head->next;n!=NULL;n=n->next){
		printf("%d ",n->data);
	}
	printf("\n");
}

//排序
void sort_list(Node* head){
	for(Node* n=head->next;n->next!=NULL;n=n->next){
		for(Node* m=n->next;m!=NULL;m=m->next){
			if(n->data<m->data){
				TYPE temp=n->data;
				n->data=m->data;
				m->data=temp;
			}
		}
	}
}

int main(){
	Node* head=create_node(0);
	for(int i=0;i<10;i++){
		add_tail_list(head,i*10);
	}
	//delete_value_list(head,20);
	//insert_list(head,4,999);
	//modify_value_list(head,40,100);
	//modify_index_list(head,8,10000);
	//int val=0;
	//access_list(head,4,&val);
	//printf("%d\n",val);
	//printf("%d\n",query_list(head,80));
	show_list(head);
	sort_list(head);
	show_list(head);
	return 0;
}
