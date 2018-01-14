/* LISP Interpreter Part 2
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

#ifndef SEXP_CPP // to avoid multiple definitions of classes
#define SEXP_CPP // to avoid multiple definitions of classes

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
/*______________________________________________________________________________________________________________________________________*/
                                                      /* Expression Checkpoint */
/*______________________________________________________________________________________________________________________________________*/

// returns the CAR( expression )
SExp* CAR()
{
    if (this->Type == NON_ATOM)
        return this->Left_Exp;
    else
    {
        cout << "[ERROR] ::This is an Atomic expression, CAR is undefined.";
        return NULL;
    }

}
// returns the CDR( expression )
SExp* CDR()
{
    if (this->Type == NON_ATOM)
        return this->Right_Exp;
    else
    {
        cout << "[ERROR] ::This is an Atomic expression, CDR is undefined.";
        return NULL;
    }

}

// checks if expression is null
bool IsNull()
{
    if (this->Type == SYMBOLIC_ATOM && this->name_val == "NIL")
        return true;
    else
        return false;
}
// checks if expression is an atom
bool IsAtom()
{
    if (this-> Type == SYMBOLIC_ATOM || this->Type == INTEGER_ATOM)
        return true;
    else
        return false;
}
// checks if expression is an integer
bool IsNumeric()
{
    if (this->Type == INTEGER_ATOM)
        return true;
    else
        return false;
}
// checks if expression is a string
bool IsLiteral()
{
    if (this->Type == SYMBOLIC_ATOM)
        return true;
    else
        return false;
}
// this is to match the (DEFUN) "Function Name" and Built in Functions. The user is not allowed to define a function name which is already in use by the program otherwise ambiguity will arise.
bool IsBuiltin() {

    if( this->name_val == "CAR" || this->name_val == "CDR" || this->name_val == "CONS" ||
       this->name_val == "QUOTE" || this->name_val == "DEFUN" || this->name_val == "ATOM" ||
       this->name_val == "NULL" || this->name_val == "PLUS" || this->name_val == "MINUS" ||
       this->name_val == "COND" || this->name_val == "TIMES" || this->name_val == "REMAINDER" ||
       this->name_val == "QUOTIENT" || this->name_val == "EQ" || this->name_val == "LESS" ||
       this->name_val == "GREATER" || this->name_val == "name_val" ||
       this->name_val == "T" || this->name_val == "NIL" )
		return true;
	else
		return false;
}

SExp* Cons(SExp *expression)
{
    return new SExp(this,expression);
}


// checks if expression is a list
bool IsList()
{
    if(this->IsNull())
        return true;
    else if (this->IsAtom())
        return false;
    else
        return this->Right_Exp->IsList();
}
/*______________________________________________________________________________________________________________________________________*/
                                                      /* BUILT IN FUNCTION */
/*______________________________________________________________________________________________________________________________________*/
SExp* Plus(SExp* expression)
{
    if (this-> Type == 2 && expression->Type== 2)
    {
        return new SExp(this->val + expression->val);
    }
    else
    {
        cout << "[ERROR]:: Two Integer values required for PLUS operation";
        return NULL;
    }
}

SExp* Minus(SExp* expression)
{
    if (this-> Type == 2 && expression->Type== 2)
    {
        return new SExp(this->val - expression->val);
    }
    else
    {
        cout << "[ERROR]:: Two Integer values required for MINUS operation";
        return NULL;
    }
}

SExp* Times(SExp* expression)
{
    if (this-> Type == 2 && expression->Type== 2)
    {
        return new SExp(this->val * expression->val);
    }
    else
    {
        cout << "[ERROR]:: Two Integer values required for TIMES operation";
        return NULL;
    }
}

SExp* Quotient(SExp* expression)
{
    if (this-> Type == 2 && expression->Type== 2)
    {
        return new SExp(this->val / expression->val);
    }
    else
    {
        cout << "[ERROR]:: Two Integer values required for QUOTIENT operation";
        return NULL;
    }
}

SExp* Remainder(SExp* expression)
{
    if (this-> Type == 2 && expression->Type== 2)
    {
        return new SExp(this->val % expression->val);
    }
    else
    {
        cout << "[ERROR]:: Two Integer values required for REMAINDER operation";
        return NULL;
    }
}
int IsGreater(SExp* expression)
{
    if (this-> Type == 2 && expression->Type== 2)
    {
        if (this->val > expression->val)
            return 1;
        else
            return 0;
    }
    else
    {
        cout << "[ERROR]:: Two Integer values required for ISGREATER operation";
        return -1;
    }
}

int IsLess(SExp* expression)
{
    if (this-> Type == 2 && expression->Type== 2)
    {
        if (this->val < expression->val)
            return 1;
        else
            return 0;
    }
    else
    {
        cout << "[ERROR]:: Two Integer values required for ISLESS operation";
        return -1;
    }
}

int IsEqual(SExp* expression)
{
    if (this-> Type == 2 && expression->Type== 2)
    {
        if (this->val == expression->val)
            return 1;
        else
            return 0;
    }
    else if (this-> Type == 1 && expression->Type == 1)
    {
        if (this->name_val == expression->name_val)
            return 1;
        else
            return 0;
    }
    else
    {
        cout << "[ERROR]:: Two Atoms of same type required for ISEQUAL operation";
        return -1;
    }
}

/*______________________________________________________________________________________________________________________________________*/
                                                      /* OUTPUT HANDLE */
/*______________________________________________________________________________________________________________________________________*/
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

/* general output : decides between output list or output S-expression */
void Output()
{
    if (this->IsList() && !this->IsNull())
        return OutputList();
    else
        return OutputSExp();
}
/* output a s-expression */
void OutputSExp()
{
    if (Type == SYMBOLIC_ATOM)
        cout << name_val;
    else if (Type == INTEGER_ATOM)
        cout << val;
    else
    {
        cout << "(";
        this->Left_Exp->Output();
        cout << ".";
        this->Right_Exp->Output();
        cout << ")";
    }
}
/* output a list */
void OutputList()
{
    cout << "(";
    SExp* temp = this;
    while( temp->Type == NON_ATOM)
    {
        if(temp->CAR()->IsAtom())
        {
            cout << " ";
            temp->CAR()->OutputSExp();
            cout << " ";
        }
        else
            temp->CAR()->Output();

        temp = temp->CDR();
    }

    cout << ")";
}

};

#endif
