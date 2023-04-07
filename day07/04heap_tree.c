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

int main(){
	srand(time(NULL));
	Heap* heap=createw_heap(10);
	for(int i=0;i<10;i++){
		add_heap(heap,rand()%100);
	}
	show_heap(heap);
}
