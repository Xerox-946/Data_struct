#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

typedef struct TreeNode{
	int data;
	struct TreeNode* left;
	struct TreeNode* right;
}TreeNode;

TreeNode* create_tree_node(int data){
	TreeNode* node=malloc(sizeof(TreeNode));
	node->data=data;
	node->left=NULL;
	node->right=NULL;
	return node;
}

void _insert_tree(TreeNode** root,TreeNode* node){
	if(NULL==*root){
		*root=node;
		return;
	}
	if((*root)->data>node->data)	_insert_tree(&((*root)->left),node);
	else _insert_tree(&((*root)->right),node);
}

//添加节点
void insert_tree(TreeNode** root,int data){
	_insert_tree(root,create_tree_node(data));
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

void lrd_show(TreeNode* root){
	if(root==NULL) return;
	lrd_show(root->left);
	lrd_show(root->right);
	printf("%d ",root->data);
}

//查找
bool query_tree(TreeNode* root,int data){
	if(root==NULL) return false;
	if(root->data==data) return true;
	if(root->data>data) return query_tree(root->left,data);
	return query_tree(root->right,data);
}

//高度
int high_tree(TreeNode* root){
	if(root==NULL) return 0;
	int high_left=high_tree(root->left);
	int high_right=high_tree(root->right);
	return high_right>high_left?high_right+1:high_left+1;
}

//密度
int density_tree(TreeNode* root){
	if(NULL==root) return 0;
	return density_tree(root->left)+density_tree(root->right)+1;
}

bool _access_ldr_tree(TreeNode* root,size_t index,int* val,int* k){
	if(root==NULL) return false;

	if(_access_ldr_tree(root->left,index,val,k))return true;
	if((*k)++==index){
		*val=root->data;
		return true;
	}
	return _access_ldr_tree(root->right,index,val,k);
}

//按中序访问
bool access_ldr_tree(TreeNode* root,size_t index,int* val){
	int k=0;
	//递归使用同一个k来计数，所以需要同一个变量k来共享
	return _access_ldr_tree(root,index,val,&k);
}

//按值删除
bool del_value_tree(TreeNode** root,int data){
	if(*root==NULL) return false;
	//找到data
	if(data==(*root)->data){
		//左子树替代data节点
		TreeNode* temp=*root;
		*root=temp->left;
		//data右子树重新往data的左子树插入
		_insert_tree(root,temp->right);
		free(temp);
		//返回
		return true;
	}
	if(data<(*root)->data) return del_value_tree(&((*root)->left),data);
	return del_value_tree(&((*root)->right),data);
}

//销毁
void destroy_tree(TreeNode* tree){
	
}

//判断是否平衡
bool is_AVL_tree(TreeNode* root){
	if(NULL==root) return true;
	return abs(high_tree(root->left)-high_tree(root->right))<=1&&is_AVL_tree(root->left)&&is_AVL_tree(root->right);
}

int main(){
	TreeNode* root=NULL;
	srand(time(NULL));
	for(int i=0;i<10;i++){
		int data=rand()%100;
		printf("%d ",data);
		insert_tree(&root,data);
	}
	int val=0;
	access_ldr_tree(root,0,&val);
	del_value_tree(&root,val);
	printf("\n");
	dlr_show(root);
	printf("\n");
	ldr_show(root);
	printf("\n");
	lrd_show(root);
	printf("\n");
	printf("query:%d high:%d density:%d\n",query_tree(root,32),
	high_tree(root),density_tree(root));
	return 0;
}
