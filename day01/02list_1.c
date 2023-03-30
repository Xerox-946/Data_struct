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
void add_head_list(Node** head,TYPE data){
	Node* node=create_node(data);
	node->next=*head;
	*head=node;
}

//删除 按值删除
bool delete_value_list(Node** head,TYPE data){
	if((*head)->data==data){
		Node* temp=*head;
		*head=(*head)->next;
		free(temp);
		return true;
	}
	for(Node* n=*head;n->next!=NULL;n=n->next){
		if(n->next->data==data){
			Node* temp=n->next;
			n->next=n->next->next;
			free(temp);
			return true;
		}
	}
	return false;
}

bool delete_index_list(Node** head,size_t index){
	if(index==0){
		Node* temp=*head;
		*head=temp->next;
		free(temp);
		return true;
	}
	int i=1;
	for(Node* n=*head;n->next!=NULL;n=n->next,i++){
		if(i==index){
			Node* temp=n->next;
			n->next=temp->next;
			free(temp);
			return true;
		}
	}
	return false;
}

//访问
bool access_list(Node* head,size_t index,TYPE* val){
	int i=0;
	for(Node* n=head;n!=NULL;n=n->next,i++){
		if(i==index){
			*val=n->data;
			return true;
		}
	}
	return false;
}

//遍历
void show_list(Node* head){
	for(Node* n=head;n!=NULL;n=n->next){
		printf("%d ",n->data);
	}
	printf("\n");
}

//排序
void sort_list(Node* head){
	for(Node* n=head;n->next!=NULL;n=n->next){
		for(Node* m=n->next;m!=NULL;m=m->next){
			if(n->data>m->data){
				TYPE temp=n->data;
				n->data=m->data;
				m->data=temp;
			}
		}
	}
}

int main(){
	Node* head=NULL;
	for(int i=0;i<10;i++){
		add_head_list(&head,i*10);
	}
//	delete_index_list(&head,9);
	show_list(head);
	sort_list(head);
	show_list(head);
	return 0;
}
