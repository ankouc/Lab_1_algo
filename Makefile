src = matrixMult.c

all : conventionnel conventionnelT

conventionnel : $(src)
	gcc -o conventionnel $(src) -I. -Dconventionnel 

conventionnelT : $(src)
	gcc -o conventionnelT $(src) -I. -DconventionnelT 

clean   : 
	rm -rf conventionnel conventionnelT

regen   : Gen.csh
	rm -rf ex_*
	./Gen.csh

cleanall:
	make clean
	rm -rf ex_*

.PHONY : all clean run
.SILENT : regen all
