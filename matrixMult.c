#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct matrices{
	int *a;
	int *b;
	int *result;
	int size;
} Matrices;

void  multiplyMatrix(Matrices *m){
	double starting_time = clock();
	int i = 0;
	for(i ; i < m->size*m->size; i++){
		int j = 0;
		for(j ; j <  m->size; j++){
			m->result[i] += m->a[j+(i/m->size)*m->size]*m->b[j*m->size+i%m->size];
		} 
	}
	printf("the multiplication of two matrices of size %d took %lf s\n",m->size,(double)(clock()-starting_time)*(double)1000/CLOCKS_PER_SEC);
}

void  multiplyMatrixT(Matrices *m){
	double starting_time = clock();
	int i = 0;
	for(i ; i < m->size*m->size; i++){
		int j = 0;
		for(j ; j <  m->size; j++){
			m->result[i] += m->a[j+(i/m->size)*m->size]*m->b[j+(i%m->size)*m->size];
		} 
	}
	printf("the multiplication of two matrices of size %d took %lf s\n",m->size,(double)(clock()-starting_time)*(double)1000/CLOCKS_PER_SEC);
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
  if(argc < 3 ){
		printf("this program takes at least 3 parameters\n"); 
		printf("      -f <file1> <file2> [-p]\n");
		return 1;
	}
  printf("%s %d\n",argv[3],argc);
  Matrices m;
	readFiles(argv[1],argv[2],&m);
#ifdef conventionnel
  multiplyMatrix(&m);
#endif
#ifdef conventionnelT
	multiplyMatrixT(&m);
#endif
  if(argc >= 4){
    if(strcmp(argv[3],"-p") == 0){
      int i;	
  	  for( i = 0 ; i < m.size*m.size; i++){
		  	printf("%d\t",m.result[i]);
		  	if(i%m.size == m.size - 1)
			  	printf("\n");
 	    }
    }
  }
	return 0;
}
