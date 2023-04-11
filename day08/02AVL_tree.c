#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct TreeNode{
	int data;
	struct TreeNode* left;
	struct TreeNode* right;
}TreeNode;

//创建节点
TreeNode* create_node(int data){
	TreeNode* node=malloc(sizeof(TreeNode));
	node->data=data;
	node->left=NULL;
	node->right=NULL;
	return node;
}

int high_tree(TreeNode* root){
	if(root==NULL) return 0;
	int right=high_tree(root->right);
	int left=high_tree(root->left);
	return right>left?right+1:left+1;
}

//平衡差值
int diff_high(TreeNode* root){
	return high_tree(root->left)-high_tree(root->right);
}

//左旋转函数
TreeNode* left_rotate(TreeNode* x){
	TreeNode* y=x->right;
	TreeNode* t2=y->left;
	y->left=x;
	x->right=t2;
	return y;
}

//右旋转函数
TreeNode* right_rotate(TreeNode* x){
	TreeNode* y=x->left;
	TreeNode* t2=y->right;
	y->right=x;
	x->left=t2;
	return y;
}

//自动调整平衡
TreeNode* auto_balance(TreeNode* x){
	if(x==NULL) return NULL;
	int lh=high_tree(x->left);
	int rh=high_tree(x->right);

	if(lh-rh>1){
		if(diff_high(x->left) >=1){
			//情况一
			x=right_rotate(x);
		}else{
			//情况三
			x->left=left_rotate(x->left);
			x=right_rotate(x);
		}
	}else if(rh-lh>1){
		if(diff_high(x->right) >=1){
			//情况四
			x->right=right_rotate(x->right);
			x=left_rotate(x);
		}else{
			//情况二
			x=left_rotate(x);
		}
	}
	return x;
}

//添加数据 有序且平衡 可能会变化 优点不用传二级指针
TreeNode* insert_tree(TreeNode* root,int data){
	if(NULL==root)
		return create_node(data);
	if(root->data>data)
		root->left=insert_tree(root->left,data);
	else
		root->right=insert_tree(root->right,data);
	
	root=auto_balance(root);
	return root;
}

void dlr_show(TreeNode* root){
	if(root==NULL) return;
	printf("%d ",root->data);
	dlr_show(root->left);
	dlr_show(root->right);
}

void ldr_show(TreeNode* root){
	if(root==NULL) return;
	ldr_show(root->left);
	printf("%d ",root->data);
	ldr_show(root->right);
}

int main(){
	TreeNode* root=NULL;
	for(int i=0;i<10;i++){
		root=insert_tree(root,i+1);
		dlr_show(root);
		printf("\n");
		ldr_show(root);
		printf("\n====================\n");
	}
	return 0;
}
