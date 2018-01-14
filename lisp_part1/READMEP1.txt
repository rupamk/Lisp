
Rupam Kundu
The Ohio State University
Email : kundu.24@osu.edu
------------------------------------------------------

Files included in the project folder :
	1. main.cpp
	2. Lisp_Parse.cpp 
	3. Lisp_Token.cpp 
	4. SExp.cpp 
	5. Makefile
	6. designP1.txt 
	7. READMEP1.txt
	
How to Compile :
	1. Run :	"make" / "make -f Makefile"
		
	2. On successful compilation:	"./Lisp_Part1"
		
	3. For cleaning up binary: "make clean"

Input Format:
         1. The input should be given line by line separated by "$" in the lines between them.
         2. If any input is incomplete the program will generate the appropriate error.
	
Output Format:
	1. outputs the dot notation of the inputs until it gets a "$$" as input.
	2. waits for a complete input expressions after "$".
	
-----------------------------------------------------------------------------------------------------------------	
A sample output:

LISP Interpreter Project :: PART 1

Enter: a valid s-expression.

[Output: a dotted notation of the Input expression]

<Note: Type $ in a separate line after each input to get the output and type $$ to exit the  interpreter>



>> ((()))))
$
[ERROR]:Invalid S Expression with Unbalanced Brackets

Type a new input>> (1 2)(4 5)
$
Invalid S Expression

Type a new input>> -1
$
-1


Type a new input>> (4 $)
[ERROR]:unexpected $ found 
$

Type a new input>> (4.5.6.7)
$
[ERROR]:: Not a valid S-exp.

>> 
Type a new input>> (1 2 3 4 5 6)
$$
(1.(2.(3.(4.(5.(6.NIL))))))


Closing Interpreter...Bye

--------------------------------------------------------------------------------------------------------------------

