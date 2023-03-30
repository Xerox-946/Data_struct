#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define TYPE int

void quick_sort(int l,int r,TYPE ptr[]);
void merge_sort(int l,int r,TYPE ptr[]);
//	设计顺序表结构
typedef struct Array{
	TYPE* ptr;//存储元素的内存首地址
	size_t cal;//表的容量
	size_t cnt;//元素的数量
}Array;

//创建
Array* create_array(size_t size){
	//先分配顺序表结构的内存
	Array* arr=malloc(sizeof(Array));
	//分配存储元素的内存
	arr->ptr=malloc(sizeof(TYPE)*size);
	//记录容量
	arr->cal=size;
	//初始化数量
	arr->cnt=0;
	return arr;
}

//销毁
void destroy_array(Array* arr){
	free(arr->ptr);
	free(arr);
}

//清空
void clean_array(Array* arr){
	arr->cnt=0;
}

//插入
bool insert_array(Array* arr,size_t index,TYPE val){
	if(arr->cnt>=arr->cal) return false;
	if(arr->cnt<index)return false;
	for(int i=arr->cnt;i>index;i--){
		arr->ptr[i]=arr->ptr[i-1];
	}
	arr->ptr[index]=val;
	arr->cnt++;
	return true;
}
bool insert_array1(Array* arr,size_t index,TYPE val){
	if(arr->cnt>=arr->cal) return false;
	if(arr->cnt<index)return false;
	memmove(arr->ptr+index+1,arr->ptr+index,(arr->cnt-index)*sizeof(TYPE));
	arr->ptr[index]=val;
	arr->cnt++;
	return true;
}

//删除
bool delete_array(Array* arr,size_t index){
	if(index>=arr->cnt) return false;
	memmove(arr->ptr+index,arr->ptr+index+1,(arr->cnt-index-1)*sizeof(TYPE));
	arr->cnt--;
	return true;
}

//访问
bool access_array(Array* arr,size_t index,TYPE* val){
	if(index>=arr->cnt) return false;
	*val=arr->ptr[index];
	return true;
}

//修改
bool modify_array(Array* arr,size_t index,TYPE val){
	if(index>=arr->cnt) return false;
	arr->ptr[index]=val;
	return true;
}

//查询
int query_array(Array* arr,TYPE val){
	for(int i=0;i<arr->cnt;i++){
		if(val==arr->ptr[i]){
			return i;
		}
	}
	return -1;
}

//排序
void sort_array(Array* arr){
	//quick_sort(0,arr->cnt-1,arr->ptr);
	merge_sort(0,arr->cnt-1,arr->ptr);
}

//遍历
void show_array(Array* arr){
	for(int i=0;i<arr->cnt;i++){
		printf("%d ",arr->ptr[i]);
	}
	printf("\n");
}
//快排
void quick_sort(int l,int r,TYPE ptr[]){
	if(l>=r) return;
	int i=l-1;
	int j=r+1;
	int mid=ptr[l+r>>1];
	while(i<j){
		do i++;while(ptr[i]<mid);
		do j--;while(ptr[j]>mid);
		if(i<j){
			TYPE temp=ptr[i];
			ptr[i]=ptr[j];
			ptr[j]=temp;
		}
	}
	quick_sort(l,j,ptr);
	quick_sort(j+1,r,ptr);
	return;
}
//归并排序
void merge_sort(int l,int r,TYPE ptr[]){
	if(l>=r) return;
	int mid=l+r>>1;
	merge_sort(l,mid,ptr);
	merge_sort(mid+1,r,ptr);
	int k=0;
	int i=l,j=mid+1;
	TYPE temp[100010]={};
	while(i<=mid&&j<=r){
		if(ptr[i]<ptr[j]) temp[k++]=ptr[i++];
		else temp[k++]=ptr[j++];
	}
	while(i<=mid) temp[k++]=ptr[i++];
	while(j<=r) temp[k++]=ptr[j++];
	for(int i=0,j=l;i<k;i++,j++){
		ptr[j]=temp[i];
	}
	return;
}

int main(){
	Array* arr=create_array(10);
	for(int i=0;i<5;i++){
		insert_array1(arr,0,i);
	}
	modify_array(arr,2,100);
	show_array(arr);
	sort_array(arr);
	show_array(arr);
	return 0;
}
