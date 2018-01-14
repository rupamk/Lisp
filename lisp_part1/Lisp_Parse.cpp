/* LISP Interpreter Part 1
Rupam Kundu
First Year Graduate Student
The Ohio State University
Email : kundu.24@osu.edu
------------------------------------------------------ */
#include <iostream>
#include <string>
#include <vector>
#include <ctype.h>
#include "SExp.cpp"

using namespace std;

class Lisp_Parse
{
        // Converts lower to upper case //
        void String_LowerToUpper(string &input)
          {
    for(unsigned int i = 0; i < input.length(); i++)
    {
        input[i] = toupper(input[i]);
    }
          }
    public:
        Lisp_Parse()
{
}

/*____________________________________________________________________________________________________________________________________________________________________ */

// Create SExpr with vector of tokens as input //
SExp* CreateSExpr(vector<string> tokens)
{
    if(tokens.back() != ")")
        cout << "[ERROR]:: ) is required!";

    tokens.pop_back();
    string First_entry = "";

    if (!tokens.empty())
    {
        First_entry = tokens[0];
    }

    if (tokens.size() == 1 && First_entry != "(" && First_entry != ")" && First_entry != ".") // for identifiers/numbers
        return CreateSExpr(First_entry);
    else if(tokens.size() > 1 && First_entry == "(") // looks for inputs starting with (
        return CreateTree(tokens);
    else
    {
        cout << "[ERROR]:: Invalid S Expression!";
        return NULL;
    }

}

/*____________________________________________________________________________________________________________________________________________________________________ */

// Create SExpr with tokens as input //
SExp* CreateSExpr(string token)
{

    int val = 0;
    int sign = 1;
    int verify = 1;
	unsigned i = 0;
	
     /* Identifier */
	if(isalpha(token[i])) // to check whether a letter: Identifier= letter->letter/digit //
         {
		for(; i < token.size(); i++) 
                   {
			if(!((isalpha(token[i])) || (token[i] >= '0' && token[i] <= '9')))       //letter/digit
				verify = 0;
		    }
		if(!verify)
                {
			cout << "[ERROR]::Invalid input--> '" << token << "'!"; 
			return NULL;
		}

        String_LowerToUpper(token); //coverts letters to upper case

	return (new SExp(token));
	 }
    /* Integers */  // can be +number|-number
	else if(token[i] == '+')
         {
		i++;
	 }
	else if(token[i] == '-')
        {
		sign = -1;
		i++;
	}

	if(i < token.size() && token[i] >= '0' && token[i] <= '9') 
        {
		        for(; i < token.size(); i++)
                        {
			if(token[i] >= '0' && token[i] <= '9')
				val = 10 * val + (token[i] - '0'); // so 549 is parsed as: [( 5 * 10 + 4 ) * 10 + 9]
			else {
				cout << "[ERROR]::Invalid Input!";
				return NULL;
	                     }
	                }
		return (new SExp(val * sign)); // returned as sign(+1/-1)*549
	}

	cout << "[ERROR]::Invalid input '" << token << "'" << endl ;
	return NULL;
}

/*____________________________________________________________________________________________________________________________________________________________________ */

/* Creating the binary parse tree using the valid tokens obtained from the Lisp_Token.cpp */
SExp* CreateTree(vector<string> tokens)
{
    vector<string>::size_type length = tokens.size();
    vector<string> elements_left;
    vector<string> elements_right;
    SExp* Left_Exp = NULL;
    SExp* Right_Exp = NULL;
    int position = 0;

    if (tokens[0] == "(") 
    {
        position ++;
        int brackt_count = 0;

        if (tokens[position] == "(")
        {
            elements_left.push_back(tokens[position]);
            brackt_count++;
            position ++;
            while (brackt_count > 0 && position < length)
            {
                if(tokens[position] == "(")
                    brackt_count++;
                else if(tokens[position] == ")")
                    brackt_count--;

               elements_left.push_back(tokens[position]);
                position++;
            }
            Left_Exp = CreateTree(elements_left);
        }
        else if(tokens[position] == ")")
            return CreateSExpr("NIL"); // for inputs like: ()
        else if(tokens[position] == ".")
            cout << "[ERROR]"; // for inputs like (. 
        else
        {
            Left_Exp = CreateSExpr(tokens[position]);
            position   ++;
        }

        bool createlist = 1;

        if(tokens[position] == ".")
        {
            createlist = 0; // presence of "." will dismiss the concept of list but an S-expression //
            position  ++;
        }

        while (position < length)
        {
            elements_right.push_back(tokens[position]);
           position ++;
        }

        if(elements_right.size() == 0)
        {
            cout << "[ERROR]";
            return NULL;
        }

        if(createlist)
            Right_Exp = CreateList(elements_right);
        else
            Right_Exp = CreateSExpr(elements_right);


        if(Left_Exp == NULL || Right_Exp == NULL)
            return NULL;

        return new SExp(Left_Exp, Right_Exp);

    }
    else if(tokens[0] != ")" && tokens[0] != ".")
        return CreateSExpr(tokens[position]);
    else
    {
        cout << "[ERROR]::Invalid S Expression!";
        return NULL;
    }
}


/*____________________________________________________________________________________________________________________________________________________________________ */

/* For creating a list */
SExp* CreateList(vector<string> tokens)
{
    int position = 0;
    vector<string>::size_type length = tokens.size();
    vector<string> elements_left;
    vector<string> elements_right;
    SExp* Left_Exp;
    SExp* Right_Exp;

    if (tokens.size() == 1)
    {
        if(tokens[0] == ")")
            return CreateSExpr("NIL");
        else
        {
            cout << "[ERROR]::Invalid Input!";
            return NULL;
        }
    }
    else
    {
        if(tokens[0] == "(")
        {
            int brackt_count = 1;
            elements_left.push_back(tokens[position]);
            position  ++;

            while (brackt_count > 0 && position < length)
            {
                if(tokens[position] == "(")
                    brackt_count++;
                else if(tokens[position] == ")")
                    brackt_count--;

                elements_left.push_back(tokens[position]);
                position++;

            }

            Left_Exp = CreateTree(elements_left);

        }
        else if (tokens[0] != ")" && tokens[0] != ".")
        {
            Left_Exp = CreateSExpr(tokens[0]);
            position++;
        }
        else
        {
            cout << "[ERROR]::Invalid input!";
            return NULL;
        }

        while (position < length)
        {
            elements_right.push_back(tokens[position]);
            position ++;
        }

        if(elements_right.size() == 0)
        {
            cout << "[ERROR]";
            return NULL;
        }
        Right_Exp = CreateList(elements_right);

        if(Left_Exp == NULL || Right_Exp == NULL)
            return NULL;

        return new SExp(Left_Exp, Right_Exp);
    }

}


};
