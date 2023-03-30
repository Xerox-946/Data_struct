#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TYPE int

typedef struct ArrayStack{
	TYPE* ptr;//存储元素的内存首地址
	size_t cal;//栈的容量
	size_t top;//栈顶位置
}ArrayStack;

//创建
ArrayStack* create_array_stack(size_t cal){
	ArrayStack* stack=malloc(sizeof(ArrayStack));
	stack->ptr=malloc(sizeof(TYPE)*cal);
	stack->cal=cal;
	stack->top=0;//入栈的位置	空增栈
	return stack;
}

typedef struct ArrayQueue{
	ArrayStack* stack1;
	ArrayStack* stack2;
}ArrayQueue;

ArrayQueue* create_array_queue(size_t cal){
	ArrayQueue* queue=malloc(sizeof(ArrayQueue));
	queue->stack1=create_array_stack(cal);
	queue->stack2=create_array_stack(cal);
}

//销毁
void destroy_array_stack(ArrayStack* stack){
	free(stack->ptr);
	free(stack);
}
void destroy_array_queue(ArrayQueue* queue){
	destroy_array_stack(queue->stack1);
	destroy_array_stack(queue->stack2);
	free(queue);
}

//栈空
bool empty_array_stack(ArrayStack* stack){
	return !stack->top;
}
//队空
bool empty_array_queue(ArrayQueue* queue){
	return empty_array_stack(queue->stack1)&&empty_array_stack(queue->stack2);
}

//栈满
bool full_array_stack(ArrayStack* stack){
	return stack->top>=stack->cal;
}
//队满
bool full_array_queue(ArrayQueue* queue){
	return queue->stack1->top+queue->stack2->top==queue->stack1->cal;
}

//入栈
bool push_array_stack(ArrayStack* stack,TYPE val){
	if(full_array_stack(stack)) return false;
	stack->ptr[stack->top++]=val;
	return true;
}
//入队
bool push_array_queue(ArrayQueue* queue,TYPE val){
	if(full_array_queue(queue)) return false;
	push_array_stack(queue->stack1,val);
	return true;
}

//出栈
bool pop_array_stack(ArrayStack* stack){
	if(empty_array_stack(stack)) return false;
	stack->top--;
	return true;
}
//栈顶
bool top_array_stack(ArrayStack* stack,TYPE* val){
	if(empty_array_stack(stack)) return false;
	*val=stack->ptr[stack->top-1];
	return true;
}
//出队
bool pop_array_queue(ArrayQueue* queue){
	if(empty_array_queue(queue)) return false;
	int val=0;
	if(empty_array_stack(queue->stack2)){
		while(top_array_stack(queue->stack1,&val)){
			push_array_stack(queue->stack2,val);
			pop_array_stack(queue->stack1);
		}
	}
	pop_array_stack(queue->stack2);
	return true;
}

//队头
TYPE head_array_queue(ArrayQueue* queue){
	int val=0;
	if(empty_array_stack(queue->stack2)){
		while(top_array_stack(queue->stack1,&val)){
			push_array_stack(queue->stack2,val);
			pop_array_stack(queue->stack1);
		}
	}
	top_array_stack(queue->stack2,&val);
	return val;
}
//队尾
TYPE tail_array_queue(ArrayQueue* queue){
	int val=0;
	if(empty_array_stack(queue->stack1)){
		while(top_array_stack(queue->stack2,&val)){
			push_array_stack(queue->stack1,val);
			pop_array_stack(queue->stack2);
		}
	}
	top_array_stack(queue->stack1,&val);
	return val;
}

//数量
size_t size_array_stack(ArrayStack* stack){
	return stack->top;
}
size_t size_array_queue(ArrayQueue* queue){
	return size_array_stack(queue->stack1)+size_array_stack(queue->stack2);
}

bool is_pop(TYPE* a,TYPE* b,int len){
	ArrayStack* stack=create_array_stack(len);
	int i=0,j=0;
	while(i<len){
		push_array_stack(stack,a[i]);
		i++;
		int top=0;
			while(top_array_stack(stack,&top)&&top==b[j]){
			pop_array_stack(stack);
			j++;
		}
	}
	bool flag=empty_array_stack(stack);
	destroy_array_stack(stack);
	return flag;
}

int main(){
	ArrayQueue* queue=create_array_queue(10);
	for(int i=0;i<10;i++){
		push_array_queue(queue,i+10);
		printf("%d head=%d tail=%d\n",size_array_queue(queue),head_array_queue(queue),tail_array_queue(queue));
	}
	printf("--------------------------\n");
	for(int i=0;i<10;i++){
		printf("%d head=%d tail=%d\n",size_array_queue(queue),head_array_queue(queue),tail_array_queue(queue));
		pop_array_queue(queue);
	}
	return 0;
}
