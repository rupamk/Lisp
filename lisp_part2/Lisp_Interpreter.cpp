/* LISP Interpreter Part 2
Rupam Kundu
First Year Graduate Student
The Ohio State University
Email : kundu.24@osu.edu
------------------------------------------------------ */
#include <iostream>
#include <string>
#include <algorithm>
#include <cassert>
#include "Lisp_Parse.cpp"

#ifndef Lisp_Interpreter_CPP// to avoid multiple definitions of classes
#define Lisp_Interpreter_CPP// to avoid multiple definitions of classes


using namespace std;

class Lisp_Interpreter
{
      Lisp_Parse parse;
        /* LISP DEFINED PRIMITIVES */
	SExp* t; // t defines true because "true" cannot be used
	SExp* nil; SExp* car; SExp* cdr; SExp* cons; SExp* atom; SExp* null; SExp* quote; SExp* cond; SExp* defun; SExp* d_list;
	SExp* eq; SExp* less; SExp* greater; SExp* isinteger; SExp* plus; SExp* minus; SExp* times; SExp* quotient; SExp* remainder;

    public:
        Lisp_Interpreter()
{
 // Creates S-Expression for LISP DEFINED PRIMITIVES //    
    t = parse.CreateSExpr("T"); nil = parse.CreateSExpr("NIL"); car = parse.CreateSExpr("CAR"); cdr = parse.CreateSExpr("CDR");
    cons = parse.CreateSExpr("CONS"); atom = parse.CreateSExpr("ATOM"); null = parse.CreateSExpr("NULL"); eq = parse.CreateSExpr("EQ");
    quote = parse.CreateSExpr("QUOTE"); cond = parse.CreateSExpr("COND"); defun = parse.CreateSExpr("DEFUN"); 
     d_list = nil; // dlist= definition list, used for storing defined functions.
    less = parse.CreateSExpr("LESS"); greater = parse.CreateSExpr("GREATER"); isinteger = parse.CreateSExpr("INT"); plus = parse.CreateSExpr("PLUS"); minus = parse.CreateSExpr("MINUS"); times = parse.CreateSExpr("TIMES"); quotient = parse.CreateSExpr("QUOTIENT");
    remainder = parse.CreateSExpr("REMAINDER");

}
/*______________________________________________________________________________________________________________________________________*/
                                                   
//checks whether the arguments are present in Association list or not
bool CheckAList(SExp* alist, SExp* expression) // alist= association list
{
    if (alist->IsNull())
        return false;
    else if (alist->CAR()->CAR()->IsEqual(expression))
        return true;
    else
        return CheckAList(alist->CDR(), expression);
}
/*______________________________________________________________________________________________________________________________________*/
bool Constantcheck(SExp* exp) // checks whether a integer or a built in function name
{
    if(exp->IsNull())
        return false;
    else if(exp->CAR()->IsNumeric())
        return true;
    else if(exp->CAR()->IsBuiltin())
        return true;
    else
        return Constantcheck(exp->CDR());
}
/*______________________________________________________________________________________________________________________________________*/
SExp* Getvalue(SExp* expression, SExp* checkList)
{
    if(checkList->IsNull())
        return nil;
    else if (checkList->CAR()->CAR()->IsEqual(expression))
        return checkList->CAR()->CDR();
    else
        return Getvalue(expression, checkList->CDR());

}
/*______________________________________________________________________________________________________________________________________*/
                                                  
SExp* Eval(SExp* expression)
{
    return Eval(expression,nil);
}

SExp* Eval(SExp *expression, SExp* alist) // alist= association list
{
    if (expression ->IsAtom())
    {
        if(expression->IsNumeric())
            return expression;
       else if (expression->IsEqual(t))
            return t;
       else if (expression->IsEqual(nil))
            return nil;
        else if (CheckAList(alist, expression))
            return Getvalue(expression, alist);
       // else if (expression->IsLiteral())
         //   return expression;
         else
        {
            cout << "[ERROR]::Unbound variable";
            return NULL;
        }
    }
    else if(expression->CAR()->IsLiteral())
    {
        if(expression->CAR()->IsEqual(quote))
        {
			if(expression->CDR()->IsNull())
            {
				cout << "[ERROR]::Arguments needed for QUOTE";
				return NULL;
			}
			else if(expression->CDR()->CDR()->IsNull())
				return expression->CDR()->CAR();

			else {
				cout << "[ERROR]::QUOTE accepts one argument";
				return NULL;
			}
		}
        else if (expression->CAR()->IsEqual(cond))
        {
            return Evcon(expression->CDR(), alist);
        }

        else if (expression->CAR()->IsEqual(defun))
        {
            if(expression->CDR()->IsNull())
            {
				cout << "[ERROR]::Give Function name!";
				return NULL;
			}
			else if(!expression->CDR()->CAR()->IsAtom())
            {
				cout << "[ERROR]::Function name should be an atom";
				return NULL;
			}
			else if(expression->CDR()->CAR()->IsNumeric())
            {
				cout << "[ERROR]::Function name can't be an integer";
				return NULL;
			}
			else if(expression->CDR()->CDR()->IsNull())
            {
				cout << "[ERROR]::Atleast one parameter needed for the function to evaluate on";
				return NULL;
			}
			else if(!expression->CDR()->CDR()->CAR()->IsList())
            {
				cout << "[ERROR]::Function parameters must be a list";
				return NULL;
			}
			else if(expression->CDR()->CDR()->CDR()->IsNull())
            {
				cout << "[ERROR]::There is no Function body ";
				return NULL;
			}

			else if(expression->CDR()->CDR()->CAR()->IsList())
                  {
				SExp* paraList = expression->CDR()->CDR()->CAR();
				if(Constantcheck(paraList))
				{
                    cout << "[ERROR]::No use of constants as variables in parameter list.";
                    return NULL;
				}

			}

            SExp* funcName = expression->CDR()->CAR();
            SExp* parameters = expression->CDR()->CDR()->CAR();
			SExp* funcbody = expression->CDR()->CDR()->CDR()->CAR();

            if(funcName->IsBuiltin())
            {
				cout << "[ERROR]::\"";
				funcName->Output();
				cout << "\" can't be reused as function name, it is a Lisp-built-in function";
				return NULL;
			}

			SExp* function = funcName->Cons(parameters->Cons(funcbody));
			d_list = function->Cons(d_list);
			return funcName;
        }
        else
        {
            SExp* evaluatedlist = Evlis(expression->CDR(), alist);
			if(evaluatedlist == NULL)
				return NULL;

            return Apply(expression->CAR(), evaluatedlist, alist);
		}
    }

    else
    {
		cout << "[ERROR]::function call not valid \"";
		expression->CAR()->Output();
		cout << "\"" << endl;
		cout << "Improper Function name";
		return NULL;
	}
}


/*______________________________________________________________________________________________________________________________________*/
SExp* Evlis(SExp* list, SExp* alist)
{
    if(list->IsNull())
        return nil;

    if (!list->IsList())
        return NULL;

    SExp* carexp = Eval(list->CAR(), alist);
    if (carexp == NULL)
        return NULL;

    SExp* cdrexp = Evlis(list->CDR(), alist);

    if (cdrexp == NULL)
        return NULL;

    return carexp->Cons(cdrexp);

}
/*______________________________________________________________________________________________________________________________________*/
SExp* Evcon(SExp * expression, SExp * alist)
{
    if (expression->IsNull())
    {
        cout << "[ERROR]::No condition evaluates to true";
        return NULL;
    }

    if(expression->CAR()->IsAtom())
    {
        cout << "[ERROR]::Condition should not be an atom";
        return NULL;
    }

    SExp* condition = Eval(expression->CAR()->CAR(),alist);
    if (condition == NULL)
    {
        cout << "[ERROR]::Condition evaluation failed";
        return NULL;
    }

    if (!condition->IsLiteral() || (condition->IsLiteral() && !condition->IsEqual(nil)))
    {
        if(!condition->IsLiteral() && condition->IsNumeric())
        {
            cout << "[ERROR]::Improper expression for condition ";
            return NULL;
        }
        if (expression->CAR()->IsList())
        {

            if (!expression->CAR()->CDR()->IsNull())
            {
                return Eval(expression->CAR()->CDR()->CAR(),alist);
            }
            else
            {
                cout << "[ERROR]::Improper argument format for COND" << endl;
                return NULL;
            }
        }
        else
        {
            cout << "[ERROR]::Improper argument format for COND" << endl;
            return NULL;
        }

    }

    return Evcon(expression->CDR(), alist);

}
/*______________________________________________________________________________________________________________________________________*/
SExp* ArgPairAssociation(SExp * parameters, SExp * args, SExp * alist) // integrates arguments and parameters and put that in association list.
{
	if(parameters->IsNull())
    {
		if(args->IsNull())
			return alist;
		else
        {
			cout << "[ERROR]::Number of arguments exceeded";
			return NULL;
		}
	}
	if(!parameters->IsAtom() && !args->IsAtom())
    {
		SExp* value = parameters->CAR()->Cons(args->CAR());
		alist = value->Cons(alist);
	}
	else
    {
		cout << "[ERROR]::Not enough arguments ";
		return NULL;
	}

	return ArgPairAssociation(parameters->CDR(), args->CDR(), alist);
}
/*______________________________________________________________________________________________________________________________________*/
SExp* Apply(SExp * functionName, SExp * args, SExp * alist)
{
        if(functionName->IsLiteral() && args->IsList())
        {
            if(functionName->IsEqual(car))
            {
                if(!args->IsNull())
                {
                    if(!args->CAR()->IsAtom())
                    {
                        if(args->CDR()->IsNull())
                            return args->CAR()->CAR();
                        else
                        {
                            cout << "[ERROR]::CAR accepts one argument";
                            return NULL;
                        }
                    }
                    else
                    {
                        cout << "[ERROR]::CAR not defined for atoms";
                        return NULL;
                    }
                }
                else
                {
                    cout << "[ERROR]::No arguments for CAR";
                    return NULL;
                }
            }
            else if(functionName->IsEqual(cdr))
            {
                if(!args->IsNull())
                {
                    if(!args->CAR()->IsAtom())
                    {
                        if(args->CDR()->IsNull())
                            return args->CAR()->CDR();
                        else
                        {
                            cout << "[ERROR]::CDR accepts one argument";
                            return NULL;
                        }
                    }
                    else {
                        cout << "[ERROR]::CDR not defined for atoms";
                        return NULL;
                    }
                }
                else {
                    cout << "[ERROR]::No arguments for CDR";
                    return NULL;
                }
            }
            else if(functionName->IsEqual(cons))
            {
                if(!args->IsNull())
                {
                    if(!args->CDR()->IsNull())
                    {
                        if(args->CDR()->CDR()->IsNull())
                            return args->CAR()->Cons(args->CDR()->CAR());
                        else
                        {
                            cout << "[ERROR]::CONS accepts two arguments";
                            return NULL;
                        }
                    }
                    else
                    {
                        cout << "[ERROR]::CONS accepts two arguments";
                        return NULL;
                    }
                }
                else
                {
                    cout << "[ERROR]::No argument for CONS";
                    return NULL;
                }
            }
            else if(functionName->IsEqual(atom))
            {
                if(!args->IsNull())
                {
                    if(args->CDR()->IsNull()) {
                        if(args->CAR()->IsAtom())
                            return t;
                        else
                            return nil;
                    }
                    else
                    {
                        cout << "[ERROR]::ATOM accepts one argument";
                        return NULL;
                    }
                }
                else
                {
                    cout << "[ERROR]::No argument for ATOM";
                    return NULL;
                }
            }
            else if(functionName->IsEqual(null))
            {
                if(!args->IsNull())
                {
                    if(args->CDR()->IsNull())
                    {
                        if(args->CAR()->IsNull())
                            return t;
                        else
                            return nil;
                    }
                    else
                    {
                        cout << "[ERROR]::NULL accepts one argument";
                        return NULL;
                    }
                }
                else {
                    cout << "[ERROR]::No argument for NIL";
                    return NULL;
                }
            }
            else if(functionName->IsEqual(eq))
            {
                if(!args->IsNull())
                {
                    if(!args->CDR()->IsNull())
                    {
                        if(args->CDR()->CDR()->IsNull())
                        {
                            int result = args->CAR()->IsEqual(args->CDR()->CAR());
                            if(result == 1)
                                return t;
                            else if(result == 0)
                                return nil;
                            else
                                return NULL;
                        }
                        else
                        {
                            cout << "[ERROR]::EQ accepts two arguments";
                            return NULL;
                        }
                    }
                    else {
                        cout << "[ERROR]::EQ accepts two arguments";
                        return NULL;
                    }
                }
                else {
                    cout << "[ERROR]::No argument for EQ";
                    return NULL;
                }
            }
            else if(functionName->IsEqual(less))
            {
                if(!args->IsNull())
                {
                    if(!args->CDR()->IsNull())
                    {
                        if(args->CDR()->CDR()->IsNull())
                        {
                            int result = args->CAR()->IsLess(args->CDR()->CAR());

                            if(result == 1)
                                return t;
                            else if(result == 0)
                                return nil;
                            else
                                return NULL;
                        }
                        else
                        {
                            cout << "[ERROR]::LESS accepts two arguments";
                            return NULL;
                        }
                    }
                    else
                    {
                        cout << "[ERROR]::LESS accepts two arguments";
                        return NULL;
                    }
                }
                else
                {
                    cout << "[ERROR]::No argument for LESS";
                    return NULL;
                }
            }
            else if(functionName->IsEqual(greater))
            {
                if(!args->IsNull())
                {
                    if(!args->CDR()->IsNull())
                    {
                        if(args->CDR()->CDR()->IsNull())
                        {
                            int result = args->CAR()->IsGreater(args->CDR()->CAR());

                            if(result == 1)
                                return t;
                            else if(result == 0)
                                return nil;
                            else
                                return NULL;
                        }
                        else
                        {
                            cout << "[ERROR]::GREATER accepts two arguments";
                            return NULL;
                        }
                    }
                    else
                    {
                        cout << "[ERROR]::GREATER accepts two arguments";
                        return NULL;
                    }
                }
                else
                {
                    cout << "[ERROR]::No argument for GREATER";
                    return NULL;
                }
            }
            else if(functionName->IsEqual(isinteger))
            {
                if(!args->IsNull())
                {
                    if(args->CDR()->IsNull())
                    {
                        if(args->CAR()->IsNumeric())
                            return t;
                        else
                            return nil;
                    }
                    else
                    {
                        cout << "[ERROR]::INT accepts one argument";
                        return NULL;
                    }
                }
                else
                {
                    cout << "[ERROR]::No argument for INT";
                    return NULL;
                }
            }
            else if(functionName->IsEqual(plus))
            {
                if(!args->IsNull())
                {
                    if(!args->CDR()->IsNull())
                    {
                        if(args->CDR()->CDR()->IsNull())
                        {
                            return args->CAR()->Plus(args->CDR()->CAR());
                        }
                        else
                        {
                            cout << "[ERROR]::PLUS accepts two arguments";
                            return NULL;
                        }
                    }
                    else
                    {
                        cout << "[ERROR]::PLUS accepts two arguments";
                        return NULL;
                    }
                }
                else
                {
                    cout << "[ERROR]::No argument for PLUS";
                    return NULL;
                }
            }
            else if(functionName->IsEqual(minus))
            {
                if(!args->IsNull())
                {
                    if(!args->CDR()->IsNull())
                    {
                        if(args->CDR()->CDR()->IsNull())
                        {
                            return args->CAR()->Minus(args->CDR()->CAR());
                        }
                        else
                        {
                            cout << "ERROR MINUS accepts two arguments";
                            return NULL;
                        }
                    }
                    else
                    {
                        cout << "ERROR MINUS accepts two arguments";
                        return NULL;
                    }
                }
                else
                {
                    cout << "ERROR No argument for MINUS";
                    return NULL;
                }
            }
            else if(functionName->IsEqual(times))
            {
                if(!args->IsNull())
                {
                    if(!args->CDR()->IsNull())
                    {
                        if(args->CDR()->CDR()->IsNull())
                        {
                            return args->CAR()->Times(args->CDR()->CAR());
                        }
                        else
                        {
                            cout << "[ERROR]::TIMES accepts two arguments";
                            return NULL;
                        }
                    }
                    else
                    {
                        cout << "[ERROR]::TIMES accepts two arguments";
                        return NULL;
                    }
                }
                else
                {
                    cout << "[ERROR]::No argument for TIMES";
                    return NULL;
                }
            }
            else if(functionName->IsEqual(quotient))
            {
                if(!args->IsNull())
                {
                    if(!args->CDR()->IsNull())
                    {
                        if(args->CDR()->CDR()->IsNull())
                        {
                            return args->CAR()->Quotient(args->CDR()->CAR());
                        }
                        else
                        {
                            cout << "[ERROR]::QUOTIENT accepts two arguments";
                            return NULL;
                        }
                    }
                    else
                    {
                        cout << "[ERROR]::QUOTIENT accepts two arguments";
                        return NULL;
                    }
                }
                else
                {
                    cout << "[ERROR]::No argument for QUOTIENT";
                    return NULL;
                }
            }
            else if(functionName->IsEqual(remainder))
            {
                if(!args->IsNull())
                {
                    if(!args->CDR()->IsNull())
                    {
                        if(args->CDR()->CDR()->IsNull())
                        {
                            return args->CAR()->Remainder(args->CDR()->CAR());
                        }
                        else
                        {
                            cout << "[ERROR]::REMAINDER accepts two arguments";
                            return NULL;
                        }
                    }
                    else
                    {
                        cout << "[ERROR]::REMAINDER accepts two arguments";
                        return NULL;
                    }
                }
                else
                {
                    cout << "[ERROR]::No argument for REMAINDER";
                    return NULL;
                }
            }
            else
            {
                SExp* value = Getvalue(functionName, d_list);

                if(value->IsNull())
                {
                    cout << "[ERROR]::function not defined \"";
                    functionName->Output();
                    cout << "\"";
                    return NULL;
                }
                SExp* funcbody = value->CDR();
                SExp* parameters = value->CAR();

                alist = ArgPairAssociation(parameters, args, alist);

                if(alist == NULL)
                    return NULL;

                return Eval(funcbody,alist);
            }
        }
        else
        {
            cout << "[ERROR]::Invalid function call";
            return NULL;
        }

}


};
#endif
