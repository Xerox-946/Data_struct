#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define TREE_TYPE char
#define EMPTY '#'
#define END '\0'
//节点
typedef struct TreeNode{
	TREE_TYPE data;
	struct TreeNode* left;
	struct TreeNode* right;
}TreeNode;

//创建节点
TreeNode* create_tree_node(TREE_TYPE data){
	TreeNode* node=malloc(sizeof(TreeNode));
	node->data=data;
	node->left=NULL;
	node->right=NULL;
	return node;
}

//前序遍历
void dlr_show(TreeNode* root){
	if(root==NULL) return;
	printf("%c",root->data);
	dlr_show(root->left);
	dlr_show(root->right);
}
//中序遍历
void ldr_show(TreeNode* root){
	if(root==NULL) return;
	ldr_show(root->left);
	printf("%c",root->data);
	ldr_show(root->right);
}
//后序遍历
void lrd_show(TreeNode* root){
	if(root==NULL) return;
	lrd_show(root->left);
	lrd_show(root->right);
	printf("%c",root->data);
}

//构建一棵树
/*
TreeNode* create_tree(void){
	TREE_TYPE data=0;
	scanf("%c",&data);
	if(data==EMPTY) return NULL;
	TreeNode* node=create_tree_node(data);
	node->left=create_tree();
	node->right=create_tree();
	return node;
}
*/

TreeNode* _create_tree(char** str){
	if(EMPTY==**str || **str==END) return NULL;
	TreeNode* node=create_tree_node(**str);
	(*str)++;
	node->left=_create_tree(str);
	(*str)++;
	node->right=_create_tree(str);
	return node;
}

//构建 前序
TreeNode* create_tree(char* str){
	_create_tree(&str);
}

//树的高度
int high_tree(TreeNode* root){
	if(root==NULL) return 0;
	int high_left=high_tree(root->left);
	int high_right=high_tree(root->right);
	return high_right>high_left?high_right+1:high_left+1;
}

//树的密度
int density_tree(TreeNode* root){
	if(root==NULL) return 0;
	return density_tree(root->left)+density_tree(root->right)+1;
}

//求左
TreeNode* left_tree(TreeNode* root,TREE_TYPE data){
	if(root==NULL) return NULL;
	if(root->data==data) return root->left;
	TreeNode* left=left_tree(root->left,data);
	TreeNode* right=left_tree(root->right,data);

	return left?left:right;
}

//插入
bool insert_tree(TreeNode* root,TREE_TYPE pdata,TREE_TYPE data){
	if(NULL==root) return false;
	if(root->data==pdata){
		if(NULL==root->left)
			return root->left=create_tree_node(data);
		if(NULL==root->right)
			return root->right=create_tree_node(data);
		return false;
	}
	bool lflag=insert_tree(root->left,pdata,data);
	bool rflag=insert_tree(root->right,pdata,data);
	return lflag||rflag;
}

//删除
bool del_tree(TreeNode** root,TREE_TYPE data){
	if(*root==NULL) return false;
	if((*root)->data==data){
		if((*root)->left || (*root)->right) return false;
		free(*root);
		*root=NULL;
		return true;
	}
	return del_tree(&((*root)->left),data)||del_tree(&((*root)->right),data);
}

//销毁
void destroy_tree(TreeNode* root){
	if(NULL==root) return;
	destroy_tree(root->left);
	destroy_tree(root->right);
	free(root);
}

int main(){
	TreeNode* root=create_tree("ABDG##H###CEI###F#J##");
	insert_tree(root,'G','X');
	del_tree(&root,'X');
	dlr_show(root);
	printf("\n");
	ldr_show(root);
	printf("\n");
	lrd_show(root);
	printf("\n");
	printf("high:%d\n",high_tree(root));
	printf("density:%d\n",density_tree(root));
	printf("left:%c\n",left_tree(root,'C')->data);
	destroy_tree(root);
	root=NULL;
}
