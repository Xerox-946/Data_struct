#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TYPE int

typedef struct ArrayQueue{
	TYPE* ptr;
	size_t cal;
	size_t head;
	size_t tail;
}ArrayQueue;

//创建
ArrayQueue* create_array_queue(size_t cal){
	ArrayQueue* queue=malloc(sizeof(ArrayQueue));
	queue->ptr=malloc(sizeof(TYPE)*(cal+1));
	queue->head=0;
	queue->tail=0;
	queue->cal=cal+1;
	return queue;
}
//销毁
void destroy_array_queue(ArrayQueue* queue){
	free(queue->ptr);
	free(queue);
}
//队空
bool empty_array_queue(ArrayQueue* queue){
	return queue->head==queue->tail;
}
//队满
bool full_array_queue(ArrayQueue* queue){
	return (queue->tail+1)%queue->cal==queue->head;
}
//入队
bool push_array_queue(ArrayQueue* queue,TYPE val){
	if(full_array_queue(queue)) return false;
	queue->ptr[queue->tail]=val;
	queue->tail=(queue->tail+1)%queue->cal;
	return true;
}
//出队
bool pop_array_queue(ArrayQueue* queue){
	if(empty_array_queue(queue)) return false;
	queue->head=(queue->head+1)%queue->cal;
	return true;
}
//队头
TYPE head_array_queue(ArrayQueue* queue){
	return queue->ptr[queue->head];
}
//队尾
TYPE tail_array_queue(ArrayQueue* queue){
	return queue->ptr[(queue->tail-1+queue->cal)%queue->cal];
}
//数量
size_t size_array_queue(ArrayQueue* queue){
	return queue->tail>queue->head?queue->tail-queue->head:queue->tail+queue->cal-queue->head;
}
int main(){
	ArrayQueue* queue=create_array_queue(10);
	for(int i=0;i<10;i++){
		push_array_queue(queue,i+10);
		printf("%d head=%d tail=%d\n",size_array_queue(queue),head_array_queue(queue),tail_array_queue(queue));
	}
	pop_array_queue(queue);
	printf("%d head=%d tail=%d\n",size_array_queue(queue),head_array_queue(queue),tail_array_queue(queue));
	return 0;
}
