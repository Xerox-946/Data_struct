#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define LEN 10
#define show_arr(arr,len){for(int i=0;i<len;printf("%d ",arr[i++]));printf("\n");}
#define SWAP(a,b){typeof(a) t=a;a=b;b=t;}

//顺序查找
int order_find(int* arr,int len,int key){
	for(int i=0;i<len;i++){
		if(arr[i]==key) return i;
	}
	return -1;
}

void quick_sort(int* arr,int l,int r){
	if(l>=r) return;
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

void merge_sort(int* arr,int l,int r){
	if(l>=r) return;
	int mid=l+r>>1;
	int i=l,j=mid+1,k=0;
	merge_sort(arr,l,mid);
	merge_sort(arr,mid+1,r);
	int temp[LEN];
	memset(temp,0,sizeof(int)*LEN);
	while(i<=mid&&j<=r){
		if(arr[i]<arr[j]) temp[k++]=arr[i++];
		else temp[k++]=arr[j++];
	}
	while(i<=mid)temp[k++]=arr[i++];
	while(j<=r)temp[k++]=arr[j++];
	for(int i=0,j=l;i<k;j++,i++){
		arr[j]=temp[i];
	}
}

//循环二分
int binary_for_find(int* arr,int len,int key){
	int l=0,r=len-1;
	while(l<=r){
		int m=l+r>>1;
		if(arr[m]==key) return m;
		if(arr[m]>key) r=m-1;
		else l=m+1;
	}
	return -1;
}

int _binary_find(int *arr,int l,int r,int k){
	if(l>r) return -1;
	int mid=l+r>>1;
	if(arr[mid]==k) return mid;
	if(arr[mid]>k) return _binary_find(arr,l,mid-1,k);
	else return _binary_find(arr,mid+1,r,k);
}

int binary_recusion_find(int* arr,int len,int key){
	return _binary_find(arr,0,len-1,key);
}

//哈希查找
bool hash_find(int *arr,int len,int key){
	/*
	//1.直接定址法
	//创建哈希表
	int hash[100000] = {};
	//标记
	for(int i=0;i<len;i++){
		hash[arr[i]]++;
	}

	//查找
	return hash[key];
	*/

	//2.数据分析法
	int min=arr[0],max=arr[0];
	for(int i=0;i<len;i++){
		if(arr[i]>max) max=arr[i];
		if(arr[i]<min) min=arr[i];
	}
	//创建哈希表
	int hash[max-min+1];
	memset(hash,0,(max-min+1)*sizeof(int));
	for(int i=0;i<len;i++){
		hash[arr[i]-min]++;
	}
	if(key<min||key>max) return false;
	return hash[key-min];
}

int main(){
	srand(time(NULL));
	int arr[LEN]={};
	for(int i=0;i<LEN;i++){
		arr[i]=rand()%100;
	}
	show_arr(arr,LEN);
	printf("order_find:%d\n",order_find(arr,LEN,77)+1);
	quick_sort(arr,0,LEN-1);
	//merge_sort(arr,0,LEN-1);
	show_arr(arr,LEN);
	printf("binary_for_find:%d\n",binary_for_find(arr,LEN,77)+1);
	printf("binary_recusion_find:%d\n",binary_recusion_find(arr,LEN,77)+1);
	printf("hash_find:%d\n",hash_find(arr,LEN,77));
	return 0;
}
