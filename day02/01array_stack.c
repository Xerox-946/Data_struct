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

//销毁
void destroy_array_stack(ArrayStack* stack){
	free(stack->ptr);
	free(stack);
}

//栈空
bool empty_array_stack(ArrayStack* stack){
	return !stack->top;
}

//栈满
bool full_array_stack(ArrayStack* stack){
	return stack->top>=stack->cal;
}

//入栈
bool push_array_stack(ArrayStack* stack,TYPE val){
	if(full_array_stack(stack)) return false;
	stack->ptr[stack->top++]=val;
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

//数量
size_t size_array_stack(ArrayStack* stack){
	return stack->top;
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
	ArrayStack* stack=create_array_stack(10);
	for(int i=0;i<10;i++){
		push_array_stack(stack,i+10);
		TYPE top=-10;
		top_array_stack(stack,&top) && printf("top:%d\n",top);
	}
	printf("---------------------------------\n");
	/*while(!empty_array_stack(stack)){
		TYPE top=-10;
		top_array_stack(stack,&top) && printf("pop:%d\n",top);
		pop_array_stack(stack);
	}*/
	TYPE* p=malloc(sizeof(TYPE)*10);
	for(int i=0;i<10;i++){
		*(p+i)=i+10;
	}
	printf("%s\n",is_pop(stack->ptr,p,10)?"yes":"no");
}
