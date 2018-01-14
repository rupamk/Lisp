LISP Interpreter Part 2

Rupam Kundu

The Ohio State University

Email : kundu.24@osu.edu

------------------------------------------------------



Files included in the project folder :

	1. main.cpp

	2. Lisp_Parse.cpp 

	3. Lisp_Token.cpp 

	4. SExp.cpp 
  
        5. Lisp_Interpreter.cpp

	6. Makefile

	7. designP2.txt 

	8. READMEP2.txt

	

How to Compile :

	1. Run :	"make" / "make -f Makefile"

		

	2. On successful compilation:	"./Lisp_Part2"

		

	3. For cleaning up binary: "make clean"



Input Format:

         1. The input should be given line by line separated by "$" in the lines between them.

         2. If any input is incomplete the program will generate the appropriate error.

	

Output Format:

	1. outputs the evaluated inputs and dot notation of the inputs until it gets a "$$" as input.

	2. waits for a complete input expressions after "$".

	

-----------------------------------------------------------------------------------------------------------------	

A sample output:

CSE 6341; LISP Interpreter Project, Part 2; Spring 2015

Enter: a valid s-expression.

[Output: a dotted notation of the Input expression]

<Note: Type $ in a separate line after each input to get the output and type $$ to exit the  interpreter>



Type an input>>  (CAR (QUOTE (A . B)))
$
A

 dot notation:(CAR.((QUOTE.((A.B).NIL)).NIL))

Type a new input>>  (CONS 4 (QUOTE (A . B)))
$
(4.(A.B))

 dot notation:(CONS.(4.((QUOTE.((A.B).NIL)).NIL)))

Type a new input>> (DEFUN SILLY (A B) (PLUS A B))
$
SILLY

 dot notation:(DEFUN.(SILLY.((A.(B.NIL)).((PLUS.(A.(B.NIL))).NIL))))

Type a new input>> (SILLY 5 6)
$
11

 dot notation:(SILLY.(5.(6.NIL)))

Type a new input>> (DEFUN MINUS2 (A B) (MINUS A B))
$
MINUS2

 dot notation:(DEFUN.(MINUS2.((A.(B.NIL)).((MINUS.(A.(B.NIL))).NIL))))

Type a new input>> (DEFUN NOTSOSILLY (A B) 
            (COND
               ((EQ A 0) (PLUS B 1))
               ((EQ B 0) (NOTSOSILLY (MINUS2 A 1) 1))
               (T (NOTSOSILLY (MINUS2 A 1) (NOTSOSILLY A (MINUS2 B 1))))
             ))
$
NOTSOSILLY

 dot notation:(DEFUN.(NOTSOSILLY.((A.(B.NIL)).((COND.(((EQ.(A.(0.NIL))).((PLUS.(B.(1.NIL))).NIL)).(((EQ.(B.(0.NIL))).((NOTSOSILLY.((MINUS2.(A.(1.NIL))).(1.NIL))).NIL)).((T.((NOTSOSILLY.((MINUS2.(A.(1.NIL))).((NOTSOSILLY.(A.((MINUS2.(B.(1.NIL))).NIL))).NIL))).NIL)).NIL)))).NIL))))

Type a new input>>  (NOTSOSILLY 0 0)
$
1

 dot notation:(NOTSOSILLY.(0.(0.NIL)))

Type a new input>>(NOTSOSILLY 1 1)
$
3

 dot notation:(NOTSOSILLY.(1.(1.NIL)))

Type a new input>> $$

Closing Interpreter...Bye





