#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node{
	size_t row;//行
	size_t col;//列
	int val;//值
}Node;

typedef struct Triplet{
	Node* arr;
	int cnt;//元素数量
	size_t r_max;
	size_t c_max;
}Triplet;

//构建三元组结构
Triplet* create_triplet(size_t m,size_t n,int (*arr)[n],int cnt){
	//创建三元组结构
	Triplet* triad=malloc(sizeof(Triplet));
	triad->arr=malloc(sizeof(Node)*cnt);
	triad->cnt=cnt;
	triad->r_max=m;
	triad->c_max=n;
	
	//压缩矩阵
	int index=0;
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			if(arr[i][j]){
				triad->arr[index].val=arr[i][j];
				triad->arr[index].row=i;
				triad->arr[index].col=j;
				index++;
			}
		}
	}
	return triad;
}

int main(){
	srand(time(NULL));
	while(1){
		int m=0,n=0,cnt=0;
		printf("请输入行，列，随机个数:");
		scanf("%d %d %d",&m,&n,&cnt);
		int arr[m][n];
		for(int i=0;i<m;i++){
			for(int j=0;j<n;j++){
				arr[i][j]=0;
			}
		}
		for(int k=0;k<cnt;){
			int i=rand()%m;
			int j=rand()%n;
			if(!arr[i][j]){
				arr[i][j]=rand()%9+1;
				k++;
			}
		}
		for(int i=0;i<m;i++){
			for(int j=0;j<n;j++){
				printf("%d ",arr[i][j]);
			}
			printf("\n");
		}
		printf("==================\n");
		Triplet* triad=create_triplet(m,n,arr,cnt);
		for(int i=0;i<cnt;i++){
			printf("row:%d col:%d val:%d\n",triad->arr[i].row,triad->arr[i].col,triad->arr[i].val);
		}
		printf("\n");
	}
}
