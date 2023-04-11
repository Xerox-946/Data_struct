#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "list_queue.h"

//边
typedef struct Edge{
	int index;				//该边到index下标的顶点
	struct Edge* next;//
}Edge;

//创建一条到index顶点的边
Edge* create_edge(int index){
	Edge* edge=malloc(sizeof(Edge));
	edge->index=index;
	edge->next=NULL;
	return edge;
}

//顶点
typedef struct Vertex{
	char vertex;//顶点数据
	Edge* first;//从该顶点出发的第一条边
}Vertex;

//图
typedef struct Graph{
	Vertex* v;//顶点表
	int cnt;//顶点数量
}Graph;

Graph* create_graph(const char* str){
	Graph* graph=malloc(sizeof(Graph));
	graph->cnt=strlen(str);
	graph->v=malloc(sizeof(Vertex)*graph->cnt);
	//初始化顶点
	for(int i=0;i<graph->cnt;i++){
		graph->v[i].vertex=str[i];
		graph->v[i].first=NULL;
	}
	return graph;
}

//添加边
bool add_edge(Graph* graph,char v1,char v2){
	for(int i=0;i<graph->cnt;i++){
		if(graph->v[i].vertex==v1){
			for(int j=0;j<graph->cnt;j++){
				if(graph->v[j].vertex==v2){
					//添加v1到v2的边
					Edge* edge=create_edge(j);
					edge->next=graph->v[i].first;
					graph->v[i].first=edge;
					return true;
				}
			}
		}
	}
	return false;
}

void show_graph(Graph* graph){
	for(int i=0;i<graph->cnt;i++){
		printf("index:%d v:%c e:",i,graph->v[i].vertex);
		for(Edge* e=graph->v[i].first;e;e=e->next){
			printf("%c ",graph->v[e->index].vertex);
		}
		printf("\n");
	}
}

int out_degree(Graph* graph,char vertex){
	for(int i=0;i<graph->cnt;i++){
		if(graph->v[i].vertex==vertex){
			Edge* edge=graph->v[i].first;
			int out_cnt=0;
			while(edge){
				out_cnt++;
				edge=edge->next;
			}
			return out_cnt;
		}
	}
	return -1;
}

int in_degree(Graph* graph,char vertex){
	int index=-1;
	int in_cnt=0;
	for(int i=0;i<graph->cnt;i++){
		if(vertex==graph->v[i].vertex) index=i;
	}
	if(index==-1) return -1;
	for(int i=0;i<graph->cnt;i++){
		Edge* edge=graph->v[i].first;
		while(edge){
			if(edge->index==index){
				in_cnt++;
				break;
			}
			edge=edge->next;
		}
	}
	return in_cnt;
}

void _DFS_show(Graph* graph,char* vflag,int i){
	if(vflag[i]) return;
	printf("%c ",graph->v[i].vertex);
	vflag[i]=1;
	for(Edge* e=graph->v[i].first;e;e=e->next){
		_DFS_show(graph,vflag,e->index);
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
			printf("%c ",graph->v[top].vertex);
			pop_list_queue(queue);

			for(Edge* e=graph->v[top].first;e;e=e->next){
				if(!vflag[e->index]){
					push_list_queue(queue,e->index);
					vflag[e->index]=1;
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
