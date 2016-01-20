#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


typedef struct matrices{
	int *a;
	int *b;
	int *result;
	int size;
} Matrices;

void matrixSum(int* a, int* b,int size, int* result){
  int i = 0 ; 
  for( i = 0 ; i < size ; i++)
    result[i] = a[i]+b[i]; 
}
void matrixSub(int* a, int*b, int size, int* result){
  int i = 0 ;
  for(i = 0 ; i < size ; i++)
    result[i] = a[i]-b[i];
}

void strassen(Matrices *m){
  int seuil = 0;
  int *a11,*a12,*a21,*a22;
  int *b11,*b12,*b21,*b22;

  a11 = malloc((m->size*m->size*sizeof(int))/4);
  a12 = malloc((m->size*m->size*sizeof(int))/4);
  a21 = malloc((m->size*m->size*sizeof(int))/4);
  a22 = malloc((m->size*m->size*sizeof(int))/4);

  b11 = malloc((m->size*m->size*sizeof(int))/4);
  b12 = malloc((m->size*m->size*sizeof(int))/4);
  b21 = malloc((m->size*m->size*sizeof(int))/4);
  b22 = malloc((m->size*m->size*sizeof(int))/4);

  int index1=0;
  int index2=0;
  int index3=0;
  int index4=0;
  int i; 
  for(i = 0 ; i < m->size*m->size ; i++){
    if(i%m->size < m->size/2 ){
      if((i/m->size) < m->size/2){
        a11[index1]=m->a[i];
        b11[index1++]=m->b[i];
      }else{
        a21[index2]=m->a[i];
        b21[index2++]=m->b[i];
      }
    }else{
      if((i/m->size) < m->size/2){
        a12[index3]=m->a[i];
        b12[index3++]=m->b[i];
      }else{
        a22[index4]=m->a[i];
        b22[index4++]=m->b[i];
      }
    }
  }

  Matrices temp;
  temp.size = m->size/2;

  int* p1;
  p1 = malloc(m->size*sizeof(int));
  temp.result = p1;
  matrixSum(a11,a22,temp.size,temp.a);
  matrixSum(b11,b22,temp.size,temp.b);
  strassen(&temp);
    
  int* p2;
  p2 = malloc(m->size*sizeof(int));
  temp.result = p2;
  matrixSum(a21,a22,temp.size,temp.a);
  temp.b = b11;
  strassen(&temp);

  int* p3;
  p3 = malloc(m->size*sizeof(int));
  temp.result = p3;
  matrixSub(b12,b22,temp.size,temp.b);
  temp.a = a11;
  strassen(&temp);
  
  
}

void  multiplyMatrix(Matrices *m){
	double starting_time = clock();
  double ending_time = 0;
	int i = 0;
	for(i ; i < m->size*m->size; i++){
		int j = 0;
		for(j ; j <  m->size; j++){
			m->result[i] += m->a[j+(i/m->size)*m->size]*m->b[j*m->size+i%m->size];
		} 
	}
  ending_time = clock();
	printf("%.12f\n",(double)(ending_time-starting_time)/CLOCKS_PER_SEC);
}

void  multiplyMatrixT(Matrices *m){
	double starting_time = clock();
  double ending_time = 0;
	int i = 0;
	for(i ; i < m->size*m->size; i++){
		int j = 0;
		for(j ; j <  m->size; j++){
			m->result[i] += m->a[j+(i/m->size)*m->size]*m->b[j+(i%m->size)*m->size];
		} 
	}
  ending_time = clock();
	printf("%.12f\n",(double)(ending_time-starting_time)/CLOCKS_PER_SEC);
}

int readFiles(char* file1,char* file2, Matrices *m){
	FILE *f1,*f2;
	f1 = fopen(file1,"r");
	f2 = fopen(file2,"r");

	fscanf(f1,"%d",&(m->size));
	m->size = (1<<m->size);

	m->a = malloc(m->size*m->size*sizeof(int));
	m->b = malloc(m->size*m->size*sizeof(int));
	m->result = malloc(m->size*m->size*sizeof(int));

  int i = 0;
	for(i; i < m->size*m->size ; i++){
		fscanf(f1,"%d",&(m->a[i]));
	}
	
	fscanf(f2,"%d",&(m->b[0]));
 
	// Normal 
#ifndef conventionnelT
		for(i = 0 ; i < m->size*m->size ; i++){
			fscanf(f2,"%d",&(m->b[i]));
		}
#else
  // Transpose
	  for(i = 0 ; i < m->size*m->size ; i++){
		  fscanf(f2,"%d",&(m->b[i/m->size+m->size*(i%m->size)]));
    }
#endif
	
	fclose(f1);
	fclose(f2);
	return 0;
}

int main(int argc,char** argv){
  if(argc < 4 || argc > 5)
    return 1;

  int verbose = 0;
  Matrices m;

  int i = 0;
  for( i = 0 ; i < argc ; i++){
    if(strcmp(argv[i],"-p") == 0)
      verbose = 1;
    if(strcmp(argv[i],"-f") == 0){
      if( argc - i < 3){
        printf("You have to specify two files\n");
        return 1;
      }
      else{
	      readFiles(argv[i+1],argv[i+2],&m);
        i+=2;
      }
    }
  }

#ifdef conventionnel
  //multiplyMatrix(&m);
  strassen(&m);
#endif
#ifdef conventionnelT
	multiplyMatrixT(&m);
#endif
  if(verbose){
  for( i = 0 ; i < m.size*m.size; i++){
	 	printf("%d\t",m.result[i]);
	 	if(i%m.size == m.size - 1)
	  	printf("\n");
 	  }
  }
  free(m.a);
  free(m.b);
  free(m.result);
	return 0;
}
