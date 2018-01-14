# LISP Interpreter Part 2
#Rupam Kundu
#The Ohio State University
#Email : kundu.24@osu.edu
#------------------------------------------------------ 

# Makefile : Compiles all files in the folder and create the object files for the same

objects = main.o Lisp_Token.o Lisp_Parse.o SExp.o Lisp_Interpreter.o


# Actual source files:

sources = main.cpp Lisp_Token.cpp Lisp_Parse.cpp SExp.cpp Lisp_Interpreter.cpp

# Create a binary file named LispInterpreter with objects 

LispInterpreterP1: $(objects) 
	g++ -o Lisp_Part2 $(objects)

# Create object files from all source files


$(objects): $(sources)
	g++ -c $(sources)

# cleaning up the binary

clean:
	rm $(objects) Lisp_Part2
