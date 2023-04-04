#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
	srand(time(NULL));
	while(1){
		int n=0;
		printf("请输入矩阵的阶数:");
		scanf("%d",&n);
		int arr[n][n];
		int zip[n*(n+1)/2];
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				if(j>=i){
					arr[i][j]=rand()%9+1;
					zip[(j+1)*j/2+i]=arr[i][j];
				}else{
					arr[i][j]=0;
				}
				printf("%d ",arr[i][j]);
			}
			printf("\n");
		}
		printf("==========================\n");
		for(int i=0;i<n*(n+1)/2;i++){
			printf("%d ",zip[i]);
		}
		printf("\n");
	}
}
