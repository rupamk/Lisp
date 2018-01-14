# LISP Interpreter Part 1
#Rupam Kundu
#First Year Graduate Student
#The Ohio State University
#Email : kundu.24@osu.edu
#------------------------------------------------------ 

# Makefile : Compiles all files in the folder and create the object files for the same

objects = main.o Lisp_Token.o Lisp_Parse.o SExp.o


# Actual source files:

sources = main.cpp Lisp_Token.cpp Lisp_Parse.cpp SExp.cpp

# Create a binary file named LispInterpreter with objects 

LispInterpreterP1: $(objects) 
	g++ -o Lisp_Part1 $(objects)

# Create object files from all source files


$(objects): $(sources)
	g++ -c $(sources)

# cleaning up the binary

clean:
	rm $(objects) Lisp_Part1
