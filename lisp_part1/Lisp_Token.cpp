/* LISP Interpreter Part 1
Rupam Kundu
First Year Graduate Student
The Ohio State University
Email : kundu.24@osu.edu
------------------------------------------------------ */
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Lisp_Token
{
    vector<string> tokens;
    string input;
    bool isFirst;

    public:
        Lisp_Token()
{
    isFirst = false;
    tokens.clear();
}

/*____________________________________________________________________________________________________________________________________________________________________ */

/* break down into Tokens */
void Tokenize(string input)
{
        int atom_flag=0; 
        int brckt=0;
        string::size_type lookahead = 0;
	string::size_type lookbehind = 0;

    while (lookahead < input.size())
    {
        if (input[lookahead] == '(')
        {
            if(!isFirst)
                isFirst = true;

            tokens.push_back("(");
            lookahead ++;atom_flag=1; // atom_flag helps to detects error //

        }
        else if (input[lookahead] == '.')
        {
              if(atom_flag==0) // helps to detect error like: 5.6. Atom_flag initialized to 0. So if no opening bracket encountered, atom_flag=0. Now if . is encountered--> error//
                {
                  cout<<"[ERROR]: Invalid S expression!";
                  tokens.clear();
                  return; 
                 }
                if(!isFirst)
                isFirst = true;
            
            tokens.push_back(".");
            lookahead++;

        }
        else if (input[lookahead] == ')')
        {
            if(!isFirst)
            {
                isFirst = true;
                tokens.push_back(")");
                return;
            }
            tokens.push_back(")");
            lookahead ++;

        }
        else if (input[lookahead] == '\n' || input[lookahead] == '\t' || input[lookahead] == ' ') // skips in case of space, newline and tab //
           {
            lookahead++;
            }
        else
        {
            lookbehind = lookahead;
            while (input[lookahead] != '(' && input[lookahead] != '.' && input[lookahead] != ')' && input[lookahead] != '\n' &&
                   input[lookahead] != '\t' && input[lookahead] != ' ' && lookahead < input.size())
            {
                if(input[lookahead-1] == ' ' &&  atom_flag==0) // checks for error like : 78 0 //
                  {cout<<"[ERROR]: Invalid S expression!";  
                   tokens.clear();
                   return;}
                 lookahead++;
                }

            if(!isFirst)
                isFirst = true;

            string data = input.substr(lookbehind,lookahead-lookbehind);
            tokens.push_back(data);
        }
    }

}

/*____________________________________________________________________________________________________________________________________________________________________ */

/* Tokens_fetch() returns tokens and also does some checking */
vector<string> Tokens_fetch()
{
    int brcktCount = 0, i = 0;
    vector<string> newtokens;
    newtokens.clear();

    if(tokens.size() == 1 && tokens[0] == ")")
    {
        newtokens.push_back(")");
        tokens.erase(tokens.begin(),tokens.begin() + i+1 );
        return newtokens;
    }

    int flag=0;
    int store_index=tokens.size();
    int index_flag=1;
// Checks for unbalanced brakcets//
    while (i < tokens.size())
    {
           if (tokens[i] == "(")
         {
            if (flag == 1) //Condition: 2
             {flag=2;
              break;}
             else
            brcktCount++; 
         }
           else if(tokens[i] == ")")
          {
            brcktCount --;
          }
        if(brcktCount==0)//Condition: 1
        { flag =1;
            if(index_flag)
            {store_index=i; index_flag=0;} // store_index stores the position index of the point where the bracket count is 0//
        }
      
        i++;

     }

    if (brcktCount !=0)
       {  cout <<"[ERROR]:Invalid S Expression with Unbalanced Brackets!"<<endl; 
       newtokens.push_back(" ");
       return newtokens ;
           }
   else{
           // Checks for error like: ().1//
            if(store_index < tokens.size()-1)
            {  cout <<"Invalid S Expression!"<<endl;
                newtokens.push_back(" "); // ****** Returns " " which is checked in main.cpp//
                return newtokens ;
            }

             // Checks for error like: (1 2)(3 4). So Condition 1 changes the value of flag if the brackets are balanced, and if we encounter another opening bracket flag=2//
             if (flag==2)
              {  cout <<"Invalid S Expression!"<<endl; 
       newtokens.push_back(" "); // ****** Returns " " which is checked in main.cpp//
       return newtokens ;
           }
            int index = 0;
            while (index < tokens.size())
            {
                newtokens.push_back(tokens[index]);
                index ++;
            }

           tokens.erase(tokens.begin(),tokens.begin() + index ); //erase tokens after pushing those into newtokens//

            return newtokens;
       
    }
   

}

/*____________________________________________________________________________________________________________________________________________________________________ */

// Function: Check if empty;; Used in Main.cpp//
bool IsEmpty()
{
    if(tokens.size() > 0)
        return false;
    else
        return true;
}
};
