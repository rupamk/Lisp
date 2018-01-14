/* LISP Interpreter Part 2
Rupam Kundu
First Year Graduate Student
The Ohio State University
Email : kundu.24@osu.edu
------------------------------------------------------ */

#include <iostream>
#include "Lisp_Token.cpp"
#include "Lisp_Parse.cpp"
#include "Lisp_Interpreter.cpp"
#include "SExp.cpp"
#include <string>
#include <cstring>
#include <algorithm>
#include <cassert>

using namespace std;

void  process(string inputStr, Lisp_Parse parse, Lisp_Token tokenize,  Lisp_Interpreter *lisp_interpreter);

/* Main function: Accepts Input, Process them and print them */
int main(int argc, const char * argv[])
{
   string inputStr;
   string inputStr1;
Lisp_Interpreter lisp_interpreter;
Lisp_Parse parse;
Lisp_Token tokenize;
   cout << string(50, '\n');
    cout << "CSE 6341; LISP Interpreter Project, Part 2; Spring 2015"<<endl<<endl;
    cout << "Enter: a valid s-expression." << endl<<endl;
    cout << "[Output: Evaluated Input and a dotted notation of the Input expression]" << endl<<endl;
    cout << "<Note: Type $ in a separate line after each input to get the output and type $$ to exit the  interpreter>" << endl<<endl ;
    cout << endl << endl ;
    cout << "Type an input>> ";
    
    while (cin)
    {
                  getline(cin, inputStr); 
                   
                  if(!inputStr.size())
                   continue;

           char * cstr = new char [inputStr.length()+1];
           std::strcpy (cstr, inputStr.c_str()); // convert input string to character for comparison//

                if(strcmp(cstr, "$") && strcmp(cstr, "$$"))
                         {
                           // Checks for unexpected $//
                           std::size_t found = inputStr.find('$');
                          if (found!=std::string::npos)
                          {std::cout << "[ERROR]:unexpected $ found "<< endl;
                           continue;}
                          else
                            inputStr1.append(inputStr);
                                               }
                 else
                   {  
                     if(inputStr == "$")  // if input= $ -> gives the output after processing//
                        {
                             process(inputStr1,  parse, tokenize, &lisp_interpreter); //process//
                              inputStr1.clear(); //clear string after processing//
                              inputStr.clear();//clear string after processing//
                              cout <<endl;     
cout << "Type a new input>> "; 
                            }
                    
                 if(inputStr == "$$")  // if input= $$ -> gives the output after processing and exit the interpreter//
                    { 
                       process(inputStr1, parse, tokenize, &lisp_interpreter);//process//
                       inputStr1.clear();//clear string after processing//
                       inputStr.clear(); //clear string after processing//
                    cout <<endl;   
                    cout << "Closing Interpreter...";
                    cout << "Bye";
                    cout <<endl<<endl; 
                  return 0; //exits//
                    }
                        
                    }          
      }

return 0;
}


/* Processing of Inputs*/
void  process(string inputStr, Lisp_Parse parse, Lisp_Token tokenize,  Lisp_Interpreter *lisp_interpreter)
{

tokenize.Tokenize(inputStr); //break down into Tokens and return them using token.push_back(), also does some checking//


        while (!tokenize.IsEmpty()) //  Tokens_fetch erases tokens after pushing them as newtokens.push_back()//
        {
            vector<string> tokens = tokenize. Tokens_fetch(); // returns tokens and also does some checking//

         /* Check "******" in Lisp_Token: So a check is done here to break if such a case happens  */
            char * cstr = new char [tokens[0].length()+1];
           std::strcpy (cstr, tokens[0].c_str());

           if(tokens.size()== 1&& !strcmp(cstr," "))
            {               
                 break;
             }
            else 
           { 
            SExp *exp = parse.CreateTree(tokens);   // Parse //        
            if(exp == NULL)
            {
                cout << endl << endl;
                cout << ">> ";
            continue;
            }
               SExp *output = lisp_interpreter->Eval(exp); //Interpreter evaluates the input
      if(output == NULL)
            {
                cout << endl ;
       cout<< "ERROR interpreting input!! \n";
            }
            else
            {
                output->Output();// Prints the result from interpreter
            } 
            cout << "\n dot notation:";
            exp->Output_Dot_notation(); // Prints the dotted notation of the input
               cout << endl;   
        }

}
}




