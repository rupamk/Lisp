/* LISP Interpreter Part 1
Rupam Kundu
First Year Graduate Student
The Ohio State University
Email : kundu.24@osu.edu
------------------------------------------------------ */
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <cassert>

/* Types of Expression */
#define SYMBOLIC_ATOM     1
#define INTEGER_ATOM      2
#define NON_ATOM          3


using namespace std;

class SExp
{
   int Type; /*1: SYMBOLIC_ATOM ; 2: INTEGER_ATOM ; 3: NON_ATOM */
   string name_val; // Type=1
   int val; //Type=2
   SExp* Left_Exp; // Type=3
   SExp* Right_Exp; // Type=3
    
    public:
   
// Type=1
 SExp(string name)
{
    name_val = name;
    Type = SYMBOLIC_ATOM;
}
//Type=2
 SExp(int integer)
{
    val = integer;
    Type = INTEGER_ATOM;
}
// Type=3
 SExp(SExp* left, SExp* right)
{
    Left_Exp = left;
    Right_Exp = right;
    Type = NON_ATOM;
}

/* output dotted notation of the input */
void  Output_Dot_notation()
{
    if (Type == SYMBOLIC_ATOM)
        cout << name_val;
    else if (Type == INTEGER_ATOM)
        cout << val;
    else
    {
        cout << "(";
        this->Left_Exp->Output_Dot_notation();
        cout << ".";
        this->Right_Exp->Output_Dot_notation();
        cout << ")";
    }
}

};
