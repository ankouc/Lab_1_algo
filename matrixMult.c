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

void  multiplyMatrix(Matrices *m){
	double starting_time = clock();
	int i = 0;
	for(i ; i < m->size*m->size; i++){
		int j = 0;
		for(j ; j <  m->size; j++){
			m->result[i] += m->a[j+(i/m->size)*m->size]*m->b[j*m->size+i%m->size];
		} 
	}
	printf("%.12f\n",(clock()-starting_time)/CLOCKS_PER_SEC);
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
	printf("%.12f\n",(double)(clock()-starting_time)/CLOCKS_PER_SEC);
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
  multiplyMatrix(&m);
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
	return 0;
}
