#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"

typedef struct Student{
	char name[20];
	char sex;
	int id;
}Student;

void show_stu(void* ptr){
	Student* stu=ptr;
	printf("姓名:%s 性别:%c 学号:%d\n",stu->name,stu->sex,stu->id);
}

int compar_id(const void* p1,const void* p2){
	const Student* stu1=p1;
	const Student* stu2=p2;
	return stu1->id-stu2->id;
}

int compar_name(const void* p1,const void* p2){
	const Student* stu1=p1;
	const Student* stu2=p2;
	return strcmp(stu1->name,stu2->name);
}

int main(){
	List* list=create_list();

	for(int i=0;i<10;i++){
		Student* stu=malloc(sizeof(Student));
		sprintf(stu->name,"hehe%d",i+1);
		stu->sex=i%2?'w':'m';
		stu->id=2023000+i;
		add_tail_list(list,stu);
	}
	show_list(list,show_stu);
	printf("===============================\n");
	/*Student stu1={};
	stu1.id=2023002;
	sprintf(stu1.name,"hehe%d",1);
	del_value_list(list,&stu1,compar_name);
	show_list(list,show_stu);
	*/
	sort_list(list,compar_id);
	show_list(list,show_stu);
	destroy_list(list);
	return 0;
}
