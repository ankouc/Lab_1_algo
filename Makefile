src = matrixMult.c
prog = matrixMult

all : $(prog)

$(prog) : $(src)
	gcc -o $(prog) $(src) -I.
clean   : 
	rm -rf $(prog)
run     : $(prog)
	./$(prog)

.PHONY : all clean run
