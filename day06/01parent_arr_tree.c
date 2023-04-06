#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "list_queue.h"

typedef struct TreeNode{
	char data;
	int parent;
}TreeNode;

typedef struct Tree{
	TreeNode* arr;
	int cal;
	int cnt;
}Tree;

Tree* create_tree(int cal){
	Tree* tree=malloc(sizeof(Tree));
	tree->arr=malloc(sizeof(TreeNode)*cal);
	tree->cal=cal;
	tree->cnt=0;
	return tree;
}

bool add_tree(Tree* tree,char data,char pdata){
	if(tree->cal<=tree->cnt){
		tree->cal*=2;
		tree->arr=realloc(tree->arr,sizeof(TreeNode)*tree->cal);
	}
	if(pdata=='\0'){
		tree->arr[0].data=data;
		tree->arr[0].parent=-1;
		tree->cnt++;
		return true;
	}

	for(int i=0;i<tree->cnt;i++){
		if(pdata==tree->arr[i].data){
			tree->arr[tree->cnt].data=data;
			tree->arr[tree->cnt++].parent=i;
			return true;
		}
	}
	return false;
}

void show_tree(Tree* tree){
	for(int i=0;i<tree->cnt;i++){
		printf("index:%d data:%c parent:%d\n",i,tree->arr[i].data,tree->arr[i].parent);
	}
}

int node_sub_count(Tree* tree,char data){
	int index=-1,cnt=0;;
	for(int i=0;i<tree->cnt;i++){
		if(tree->arr[i].data==data){
			index=i;
			break;
		}
	}
	if(index==-1)	return index;
	for(int i=0;i<tree->cnt;i++){
		if(index==tree->arr[i].parent) cnt++;
	}
	return cnt;
}

int _tree_high(Tree* tree,char data){
	int index=-1;
	for(int i=0;i<tree->cnt;i++){
		if(data==tree->arr[i].data){
			index=i;
			break;
		}
	}
	int max_sub_high=0;
	for(int i=0;i<tree->cnt;i++){
		if(index==tree->arr[i].parent){
			int high=_tree_high(tree,tree->arr[i].data);
			if(high>max_sub_high) max_sub_high=high;
		}
	}
	return max_sub_high+1;
}

int tree_high(Tree* tree){
	return _tree_high(tree,tree->arr[0].data);	
}

//层序遍历普通树
void layer_show_tree(Tree* tree){
	//创建队列
	ListQueue* queue=create_list_queue();

	//根节点入队
	push_list_queue(queue,tree->arr[0].data);

	while(!empty_list_queue(queue)){
		//获取队头并出队
		char data=head_list_queue(queue);
		pop_list_queue(queue);
		printf("%c ",data);

		//找data的孩子并入队
		int index=-1;
		for(int i=0;i<tree->cnt;i++){
			if(data==tree->arr[i].data){
				index=i;
				break;
			}
		}
		for(int i=0;i<tree->cnt;i++){
			if(index==tree->arr[i].parent){
				push_list_queue(queue,tree->arr[i].data);
			}
		}
	}
	//销毁队列
	destroy_list_queue(queue);
}

int main(){
	Tree* tree=create_tree(10);
	add_tree(tree,'A','\0');
	add_tree(tree,'B','A');
	add_tree(tree,'C','A');
	add_tree(tree,'D','A');
	add_tree(tree,'E','B');
	add_tree(tree,'F','B');
	add_tree(tree,'G','D');
	add_tree(tree,'H','D');
	add_tree(tree,'I','H');
	add_tree(tree,'J','I');
	show_tree(tree);
	printf("sub_cnt:%d\n",node_sub_count(tree,'A'));
	printf("high:%d\n",tree_high(tree));
	layer_show_tree(tree);
	return 0;
}
