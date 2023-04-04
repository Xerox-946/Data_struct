#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main(){
	srand(time(NULL));
	while(1){
		int n=0;
		printf("请输入矩阵的阶数:");
		scanf("%d",&n);
		int arr[n][n];
		int zip[3*n-2];
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				if(abs(i-j)<=1){
					arr[i][j]=rand()%9+1;
					zip[2*i+j]=arr[i][j];
				}else{
					arr[i][j]=0;
				}
				printf("%d ",arr[i][j]);
			}
			printf("\n");
		}
		printf("==========================\n");
		for(int i=0;i<3*n-2;i++){
			printf("%d ",zip[i]);
		}
		printf("\n");
	}
}
