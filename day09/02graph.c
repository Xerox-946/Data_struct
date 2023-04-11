#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include "list_queue.h"

//邻接矩阵

typedef struct Graph{
	char* v;//顶点数组
	char* e;//边的数组
	size_t cnt;//顶点数量
}Graph;

//创建矩阵
Graph* create_graph(const char* str){
	//申请图结构的内存
	Graph* graph=malloc(sizeof(Graph));
	graph->cnt=strlen(str);//计算顶点数量
	//申请顶点存储顶点的内存
	graph->v=malloc(graph->cnt);
	strcpy(graph->v,str);
	//申请边的数组
	graph->e=calloc(graph->cnt,graph->cnt);
	return graph;
}

//添加边
bool add_edge(Graph* graph,char v1,char v2){
	int x=-1,y=-1;
	for(int i=0;i<graph->cnt;i++){
		if(graph->v[i]==v1) x=i;
		if(graph->v[i]==v2) y=i;
	}
	if(-1==x||-1==y) return false;

	graph->e[x*graph->cnt+y]=1;
	//graph->e[y*graph->cnt+x]=1;
	return true;
}

void show_graph(Graph* graph){
	printf("  ");
	for(int i=0;i<graph->cnt;i++) printf("%c ",graph->v[i]);
	printf("\n");

	for(int i=0;i<graph->cnt;i++){
		printf("%c ",graph->v[i]);
		for(int j=0;j<graph->cnt;j++){
			printf("%hhd ",graph->e[i*graph->cnt+j]);
		}
		printf("\n");
	}
}

//计算顶点的入度
int in_degree(Graph* graph,char v){
	for(int i=0;i<graph->cnt;i++){
		if(graph->v[i]==v){
			int cnt=0;
			for(int j=0;j<graph->cnt;j++){
				if(graph->e[j*graph->cnt+i]) cnt++;
			}
			return cnt;
		}
	}
	return -1;
}

//计算顶点的出度
int out_degree(Graph* graph,char v){
	for(int i=0;i<graph->cnt;i++){
		if(graph->v[i]==v){
			int cnt=0;
			for(int j=0;j<graph->cnt;j++){
				if(graph->e[i*graph->cnt+j]) cnt++;
			}
			return cnt;
		}
	}
	return -1;
}

//对顶点v[i] DFS
void _DFS_show(Graph* graph,char* vflag,int i){
	if(vflag[i]) return;
	printf("%c ",graph->v[i]);
	vflag[i]=1;
	for(int j=0;j<graph->cnt;j++){
		if(graph->e[i*graph->cnt+j]) _DFS_show(graph,vflag,j);
	}
}

void DFS_show(Graph* graph){
	char vflag[graph->cnt];
	memset(vflag,0,graph->cnt);
	for(int i=0;i<graph->cnt;i++){
		_DFS_show(graph,vflag,i);
	}
}

void BFS_show(Graph* graph){
	char vflag[graph->cnt];
	memset(vflag,0,graph->cnt);
	ListQueue* queue=create_list_queue();
	for(int i=0;i<graph->cnt;i++){
		if(!vflag[i]){
			push_list_queue(queue,i);
			vflag[i]=1;
		}
		while(!empty_list_queue(queue)){
			int top=head_list_queue(queue);
			printf("%c ",graph->v[top]);
			pop_list_queue(queue);

			for(int y=0;y<graph->cnt;y++){
				if(graph->e[top*graph->cnt+y]&&!vflag[y]){
					push_list_queue(queue,y);
					vflag[y]=1;
				}
			}
		}
	}
	destroy_list_queue(queue);
}

int main(){
	Graph* graph = create_graph("ABCDEFGH");
	add_edge(graph,'A','B');
	add_edge(graph,'A','C');
	add_edge(graph,'A','D');
	add_edge(graph,'B','C');
	add_edge(graph,'C','F');
	add_edge(graph,'D','F');
	add_edge(graph,'H','D');
	add_edge(graph,'C','G');
	add_edge(graph,'G','E');
	add_edge(graph,'E','F');
	add_edge(graph,'F','G');
	show_graph(graph);
	printf("in:%d out:%d\n",in_degree(graph,'D'),out_degree(graph,'D'));
	DFS_show(graph);
	printf("\n");
	BFS_show(graph);
	printf("\n");
}
