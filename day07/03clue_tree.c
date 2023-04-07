#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

//线索二叉树
typedef struct TreeNode{
	int data;
	struct TreeNode* left;
	struct TreeNode* right;
	bool rclue;//为真时，右子树是线索
}TreeNode;

TreeNode* create_tree_node(int data){
	TreeNode* node=malloc(sizeof(TreeNode));
	node->data=data;
	node->left=NULL;
	node->right=NULL;
	node->rclue=false;
	return node;
}

void _insert_tree(TreeNode** root,TreeNode* node){
	if(NULL==*root){
		*root=node;
		return;
	}
	if(node->data<(*root)->data){
		_insert_tree(&((*root)->left),node);
	}else{
		_insert_tree(&((*root)->right),node);
	}
}

void insert_tree(TreeNode** root,int data){
	_insert_tree(root,create_tree_node(data));
}

void ldr_show(TreeNode* root){
	if(NULL==root) return;
	ldr_show(root->left);
	printf("%d ",root->data);
	ldr_show(root->right);
}

//prev是root的上一个节点
TreeNode* prev=NULL;

//根据中序遍历，建立线索
void create_clue(TreeNode* root){
	if(NULL==root) return;

	//左
	create_clue(root->left);

	//根
	if(NULL!=prev && NULL==prev->right){
		prev->right=root;
		prev->rclue=true;
	}
	prev=root;

	create_clue(root->right);
}

//按照线索遍历
void clue_show(TreeNode* node){
	while(node){
		while(node->left) node=node->left;
		
		printf("%d ",node->data);
		while(node->rclue){
			node=node->right;
			printf("%d ",node->data);
		}
		node=node->right;
	}
}

int main(){
	srand(time(NULL));
	TreeNode* root=NULL;
	for(int i=0;i<10;i++){
		insert_tree(&root,rand()%100);
	}
	ldr_show(root);
	printf("\n");
	create_clue(root);
	clue_show(root);
}
