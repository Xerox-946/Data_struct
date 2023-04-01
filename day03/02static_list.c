#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int data;
	int i;
}Node;

Node list[100];

int main(){
	Node* head=list[0];
	head->i=5;
	list[5].i=2;
	list[2].i=8;
}
