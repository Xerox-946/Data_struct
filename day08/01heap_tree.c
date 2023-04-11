#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define TYPE int
#define SWAP(a,b) {typeof(a) t=(a);(a)=(b);(b)=t;}

//大顶堆
typedef struct Heap{
	TYPE* arr;
	size_t cal;
	size_t cnt;
}Heap;

//创建
Heap* createw_heap(int cal){
	Heap* heap=malloc(sizeof(Heap));
	heap->arr=malloc(sizeof(TYPE)*cal);
	heap->cal=cal;
	heap->cnt=0;
	return heap;
}

//空堆
bool empty_heap(Heap* heap){
	return 0==heap->cnt;
}

//满堆
bool full_heap(Heap* heap){
	return heap->cnt>=heap->cal;
}

bool add_heap(Heap* heap,TYPE data){
	if(full_heap(heap)) return false;
	heap->arr[heap->cnt++]=data;
	
	//新加入的位置进行调整成大顶堆
	int index = heap->cnt;//编号
	while(index>1){
		if(heap->arr[index/2-1]<heap->arr[index-1]){
			SWAP(heap->arr[index/2-1],heap->arr[index-1]);
			index/=2;
			continue;
		}
		return true;
	}
	return true;
}

void show_heap(Heap* heap){
	for(int i=0;i<heap->cnt;i++){
		printf("%d ",heap->arr[i]);
	}
	printf("\n");
}

//删除堆顶
bool del_top_heap(Heap* heap){
	if(empty_heap(heap)) return false;
	//堆顶与末尾交换
	SWAP(heap->arr[heap->cnt-1],heap->arr[0]);
	heap->cnt--;
	int index=1;
	//从上到下重新调整成堆结构
	while(index<=heap->cnt){
		if(index*2<heap->cnt){
			if(heap->arr[index*2-1]<heap->arr[index*2]){
				if(heap->arr[index*2]>heap->arr[index-1]){
					SWAP(heap->arr[index*2],heap->arr[index-1]);
					index=index*2+1;
				}else{
					return true;
				}
			}else{
				if(heap->arr[index*2-1]>heap->arr[index-1]){
					SWAP(heap->arr[index*2-1],heap->arr[index-1]);
					index*=2;
				}else{
					return true;
				}
			}
		}else if(index*2-1<heap->cnt){
			if(heap->arr[index*2-1]>heap->arr[index-1]){
				SWAP(heap->arr[index*2-1],heap->arr[index-1]);
				index*=2;
			}
			return true;
		}else{
			return true;
		}
	}
}

//堆排序
void sort_heap(int* arr,int len){
	//把数组调整成大顶堆结构
	Heap* heap=createw_heap(len);
	for(int i=0;i<len;i++){
		add_heap(heap,arr[i]);
	}
	//交换堆顶与末尾，有效个数-1,重新调整堆结构，直到有效个数为0位置
	for(int i=0;i<len;i++){
		del_top_heap(heap);
	}
	for(int i=0;i<len;i++){
		printf("%d ",heap->arr[i]);
	}
	printf("\n");
}

int main(){
	srand(time(NULL));
	int arr[10]={};
	for(int i=0;i<10;i++){
		arr[i]=rand()%100;
	}
	sort_heap(arr,10);
	/*Heap* heap=createw_heap(10);
	for(int i=0;i<10;i++){
		add_heap(heap,rand()%100);
	}
	show_heap(heap);
	del_top_heap(heap);
	show_heap(heap);
	*/
	return 0;
}
