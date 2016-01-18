#include <stdio.h>




void  multiplyMatrix(int* matrixA,int* matrixB,int* result,int size){
	int i = 0;
	for(i ; i < size*size; i++){
		int j = 0;
		for(j ; j <  size; j++){
			result[i] += matrixA[j+(i/size)*size]*matrixB[j*size+i%size];
		} 
	}
}

int main(){
	int a[9] = {1,2,3,1,2,3,1,2,3};
	int b[9] = {1,2,3,1,2,3,1,2,3};
	int r[9] = {0,0,0,0,0,0,0,0,0};
	int identity[9] = {1,0,0,0,1,0,0,0,1};
	int size = 3;
	multiplyMatrix(a,identity,r,size);
	int i = 0;
	for (i = 0 ; i < size*size; i++){
		printf("%d\t",r[i]);
		if(i%size == size-1)
			printf("\n");
	}
	return 0;
}
