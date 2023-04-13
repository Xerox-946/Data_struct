#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include "list_queue.h"

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

//计数排序
void count_sort(TYPE* arr,size_t len){
	int min=arr[0],max=arr[0];
	for(int i=0;i<len;i++){
		if(max<arr[i])max=arr[i];
		if(min>arr[i])min=arr[i];
	}
	int* hash=calloc(sizeof(TYPE),max-min+1);
	//标记哈希表
	for(int i=0;i<len;i++){
		hash[arr[i]-min]++;
	}

	for(int i=0,j=0;i<max-min+1;i++){
		while(hash[i]--){
			arr[j++]=i+min;
		}
	}
	free(hash);
}

//cnt桶数 range桶中数值的范围
void _bucket_sort(TYPE* arr,size_t len,int cnt,int range){
	//申请桶的内存 bucket桶的首地址 bucket_end桶中最后一个元素的地址
	TYPE* bucket[cnt],*bucket_end[cnt];
	for(int i=0;i<cnt;i++){
		//最坏的情况是所有数据在一个桶中
		bucket[i]=malloc(sizeof(TYPE)*len);
		//开始时，起始、末尾指针都指向开头
		bucket_end[i]=bucket[i];
	}
	
	//把所有数据按照桶的范围值放到对应的桶中
	for(int i=0;i<len;i++){
		for(int j=0;j<cnt;j++){
			if(range*j<=arr[i]&&arr[i]<range*(j+1)){
				*(bucket_end[j])=arr[i];
				bucket_end[j]++; //末尾指针往后移动一个元素
				break;
			}
		}
	}
	
	//调用其他的排序算法，对每个桶中的数据排序
	for(int i=0;i<cnt;i++){
		//计算桶中的元素个数
		int size=bucket_end[i]-bucket[i];
		if(size>1) count_sort(bucket[i],size);
		memcpy(arr,bucket[i],size*sizeof(TYPE));
		arr+=size;
		free(bucket[i]);
	}
}

//桶排序
void bucket_sort(TYPE* arr,size_t len){
	_bucket_sort(arr,len,4,25);
}

//基数排序
void base_sort(TYPE* arr,size_t len){
	//创建队列
	ListQueue* queue[10]={};
	for(int i=0;i<10;i++)	queue[i]=create_list_queue();

	//循环次数由最大值的位数决定
	int max=arr[0];
	for(int i=1;i<len;i++){
		if(arr[i]>max) max=arr[i];
	}

	for(int k=1;max/k;k*=10){
		for(int j=0;j<len;j++){
			//获取每个数的每个位的值
			push_list_queue(queue[arr[j]/k%10],arr[j]);
		}
		int index=0;
		for(int j=0;j<10;j++){
			while(!empty_list_queue(queue[j])){
				arr[index++]=head_list_queue(queue[j]);
				pop_list_queue(queue[j]);
			}
		}
	}

	for(int i=0;i<10;i++){
		destroy_list_queue(queue[i]);
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
	//count_sort(arr,LEN);//计数排序
	//bucket_sort(arr,LEN);//桶排序
	base_sort(arr,LEN);//基数排序
	show_arr(arr,LEN);
}
