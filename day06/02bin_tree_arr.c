#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include "list_queue.h"

#define TREE_TYPE char

typedef struct BinTree{
	TREE_TYPE* arr;
	size_t cal;
}BinTree;

//构建'#'空位置
BinTree* create_tree(const TREE_TYPE* arr,size_t len){
	BinTree* tree=malloc(sizeof(BinTree));
	tree->arr=malloc(sizeof(TREE_TYPE)*len);
	memcpy(tree->arr,arr,sizeof(TREE_TYPE)*len);
	tree->cal=len;
	return tree;
}

//对编号为index的节点进行前序遍历
void _dlr_show(BinTree* tree,size_t index){
	if(index-1>=tree->cal||tree->arr[index-1]=='#') return;
	printf("%c ",tree->arr[index-1]);
	_dlr_show(tree,index*2);
	_dlr_show(tree,index*2+1);
}

//前序
void dlr_show(BinTree* tree){
	_dlr_show(tree,1);
	printf("\n");
}

//对编号为index的节点进行中序遍历
void _ldr_show(BinTree* tree,size_t index){
	if(index-1>=tree->cal||tree->arr[index-1]=='#') return;
	_ldr_show(tree,index*2);
	printf("%c ",tree->arr[index-1]);
	_ldr_show(tree,index*2+1);
}

//中序
void ldr_show(BinTree* tree){
	_ldr_show(tree,1);
	printf("\n");
}

//对编号为index的节点进行后序遍历
void _lrd_show(BinTree* tree,size_t index){
	if(index-1>=tree->cal||tree->arr[index-1]=='#') return;
	_lrd_show(tree,index*2);
	_lrd_show(tree,index*2+1);
	printf("%c ",tree->arr[index-1]);
}

//后序
void lrd_show(BinTree* tree){
	_lrd_show(tree,1);
	printf("\n");
}

//层序遍历
void layer_show(BinTree* tree){
	ListQueue* queue=create_list_queue();
	push_list_queue(queue,1);//入编号
	while(!empty_list_queue(queue)){
		int index=head_list_queue(queue);
		//入左子树
		int left=index*2;
		if(left-1<=tree->cal&&tree->arr[left-1]!='#')push_list_queue(queue,left);
		int right=index*2+1;
		if(right-1<=tree->cal&&tree->arr[right-1]!='#')push_list_queue(queue,right);
		printf("%c ",tree->arr[index-1]);
		pop_list_queue(queue);
	}
	destroy_list_queue(queue);
	printf("\n");
}

int _high_tree(BinTree* tree,size_t index){
	if(index-1>=tree->cal||tree->arr[index-1]=='#') return 0;
	int max=0;
	int h1=_high_tree(tree,index*2);
	int h2=_high_tree(tree,index*2+1);
	max=h1>h2?h1:h2;
	return max+1;
}

//树的高度
int high_tree(BinTree* tree){
	return _high_tree(tree,1);
}

int _density_tree(BinTree* tree,size_t index){
	if(index-1>=tree->cal||tree->arr[index-1]=='#') return 0;
	return _density_tree(tree,index*2)+_density_tree(tree,index*2+1)+1;
}

//树的密度
int density_tree(BinTree* tree){
	//return _density_tree(tree,1);
	int density=0;
	for(int i=0;i<tree->cal;i++){
		if('#'!=tree->arr[i]) density++;
	}
	return density;
}

//插入
bool insert_tree(BinTree* tree,TREE_TYPE data,TREE_TYPE pdata){
	size_t index=1;
	while(index-1<tree->cal){
		if(tree->arr[index-1]==pdata){
			//扩容
			if(index*2-1>=tree->cal){
				tree->arr=realloc(tree->arr,tree->cal*2*sizeof(TREE_TYPE));
				for(int i=tree->cal;i<tree->cal*2;i++){
					tree->arr[i]='#';
				}
				tree->cal*=2;
			}
			if(tree->arr[index*2-1]=='#'){ 
				tree->arr[index*2-1]=data;
				return true;
			}else if('#'==tree->arr[index*2]){
				tree->arr[index*2]=data;
				return true;
			}
			return false;
		}
		index++;
	}
	return false;
}

//删除节点
bool del_tree(BinTree* tree,TREE_TYPE data){
	size_t index=1;
	while(index-1<tree->cal){
		if(data==tree->arr[index-1]){
			if(index*2-1<tree->cal&&'#'!=tree->arr[index*2-1])return false;
			if(index*2<tree->cal&&'#'!=tree->arr[index*2])return false;
			tree->arr[index-1]='#';
			return true;
		}
		index++;
	}
	return false;
}

//求左
int left_tree(BinTree* tree,TREE_TYPE data){
	for(int i=1;i<tree->cal+1;i++){
		if(data==tree->arr[i-1]&&(i*2-1)<tree->cal&&tree->arr[i*2-1]!='#'){
			return 2*i;
		}
	}
	return -1;
}

//求右
int right_tree(BinTree* tree,TREE_TYPE data){
	for(int i=1;i<tree->cal+1;i++){
		if(data==tree->arr[i-1]&&i*2<tree->cal&&tree->arr[i*2]!='#'){
			return 2*i+1;
		}
	}
	return -1;
}

//求根
int boot_tree(BinTree* tree,TREE_TYPE data){
	if(data=='#') return -1;
	for(int i=1;i<tree->cal+1;i++){
		if(data==tree->arr[i-1]){
			return i/2;
		}
	}
	return -1;
}

//根据编号显示数据
void show_treebyindex(BinTree* tree,size_t index){
	if(index==-1||index-1>=tree->cal)
		printf("未找到该节点！\n");
	else
		printf("%c\n",tree->arr[index-1]);
}

int main(){
	char* str="ABCD#EFGH##I##J";
	BinTree* tree=create_tree(str,strlen(str));
	insert_tree(tree,'X','B');
	del_tree(tree,'X');
	dlr_show(tree);
	ldr_show(tree);
	lrd_show(tree);
	layer_show(tree);
	printf("high:%d\n",high_tree(tree));
	printf("density:%d\n",density_tree(tree));
	show_treebyindex(tree,left_tree(tree,'B'));
	show_treebyindex(tree,right_tree(tree,'B'));
	show_treebyindex(tree,boot_tree(tree,'B'));
}
