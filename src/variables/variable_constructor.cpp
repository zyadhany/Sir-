#include "variable.h"
/**

 * Variable()

    Variable("(n + 20) * m");
    Variabele("n") + 



    Variable("n") + Va
 */
Variable::Variable(const string &expresion){

    *this = Variable("temp", "str", expresion);
}


/**
 * 
 */
bool IsValidBarnaces(string expresion)
{
    int barnaces = 0;
    for (int i = 0; i < expresion.size(); i++)
    {
        if (expresion[i] == '(')
        {
            barnaces++;
        }
        else if (expresion[i] == ')')
        {
            barnaces--;
        }
    }
    return barnaces == 0;
}