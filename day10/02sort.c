#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#define LEN 15
#define TYPE int
#define SWAP(a,b){typeof(a) t=a;a=b;b=t;}
#define show_arr(arr,len){for(int i=0;i<len;printf("%d ",arr[i++]));printf("\n");}

typedef void (*SortFP)(TYPE* arr,size_t len);

//冒泡排序
void bubble_sort(TYPE* arr,size_t len){
	for(int i=len-1;i>0;i--){
		int cnt=0;
		for(int j=0;j<i;j++){
			if(arr[j]>arr[j+1]){
				SWAP(arr[j],arr[j+1]);
				cnt++;
			}
		}
		if(!cnt) return;
	}
}

//归并排序
void merge_sort(TYPE *arr,int l,int r){
	if(l>=r) return;
	int mid=l+r>>1;
	merge_sort(arr,l,mid);
	merge_sort(arr,mid+1,r);
	int i=l,j=mid+1,k=0;
	TYPE temp[LEN];
	memset(temp,0,sizeof(TYPE)*LEN);
	while(i<=mid&&j<=r){
		if(arr[i]<arr[j]) temp[k++]=arr[i++];
		else temp[k++]=arr[j++];
	}
	while(i<=mid) temp[k++]=arr[i++];
	while(j<=r) temp[k++]=arr[j++];
	for(int i=0,j=l;i<k;i++,j++){
		arr[j]=temp[i];
	}
}

//快速排序
void quick_sort(TYPE* arr,int l,int r){
	if(l>=r)return;
	int i=l-1;
	int j=r+1;
	int mid=arr[l+r>>1];
	while(i<j){
		do i++;while(arr[i]<mid);
		do j--;while(arr[j]>mid);
		if(i<j){
			SWAP(arr[i],arr[j]);
		}
	}
	quick_sort(arr,l,j);
	quick_sort(arr,j+1,r);
}

//选择排序
void select_sort(TYPE* arr,size_t len){
	for(int i=0;i<len-1;i++){
		int min=i;
		for(int j=i;j<len;j++){
			if(arr[j]<arr[min]){
				min=j;
			}
		}
		if(min!=i) SWAP(arr[min],arr[i]);
	}
}

//插入排序
void insert_sort(TYPE* arr,size_t len){
	//i是无序部分的第一个位置
	int j=0;
	for(int i=0;i<len;i++){
		int val=arr[i];
		for(j=i;j>0&&arr[j-1]>val;j--){
			arr[j]=arr[j-1];
		}
		if(j!=i) arr[j]=val;
	}
}

//希尔排序
void shell_sort(TYPE* arr,size_t len){
	for(int k=len/2;k>0;k/=2){
		for(int i=k,j=0;i<len;i++){
			int val=arr[i];
			for(j=i;j-k>=0 && arr[j-k]>val;j-=k){
				arr[j]=arr[j-k];
			}
			if(j!=i) arr[j]=val;
		}
	}
}

int main(){
	TYPE arr[LEN]={};
	srand(time(NULL));
	for(int i=0;i<LEN;i++){
		arr[i]=rand()%100;
	}
	show_arr(arr,LEN);
	//quick_sort(arr,0,LEN-1);//快速排序
	//bubble_sort(arr,LEN);//冒泡排序
	//merge_sort(arr,0,LEN-1);//归并排序
	//select_sort(arr,LEN);//选择排序
	//insert_sort(arr,LEN);//插入排序
	//shell_sort(arr,LEN);//希尔排序
	show_arr(arr,LEN);
}
