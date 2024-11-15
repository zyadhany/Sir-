#include "Sir.h"

string deleteSpaces(string expresion)
{
    string updatedExpresion = "";
    for (size_t i = 0; i < expresion.size(); i++)
    {
        if (expresion[i] != ' ')
            updatedExpresion.push_back(expresion[i]);
    }
    return updatedExpresion;
}

double applyOperation(double left, double right, char op)
{
    switch (op)
    {
    case '+':
        return left + right;
    case '-':
        return left - right;
    case '*':
        return left * right;
    case '/':
        if (right == 0)
        {
            throw invalid_argument("Division by zero");
        }
        return left / right;
    default:
        throw invalid_argument("Invalid operator");
    }
}

double executeOperation(string expresion)
{
    if(IsValidExpresion(expresion))
    {
        // exeute brances first
        string update = "", brance = "";
        double result = 0;
        for (size_t i = 0; i < expresion.size(); i++)
        {
            if(expresion[i] == '(')
            {
                brance = "";
                int barnaces = 1;
                i++;
                while (barnaces != 0)
                {
                    if(expresion[i] == '(')
                    {
                        barnaces++;
                    }
                    else if(expresion[i] == ')')
                    {
                        barnaces--;
                    }
                    brance.push_back(expresion[i]);
                    i++;
                }
                result = executeOperation(brance);
                update += to_string(result);
            }
            update.push_back(expresion[i]);
        }
        // execute multiplication and division
        for (size_t i = 0; i < expresion.size(); i++)
        {
            
        }
        // execute addition and subtraction
        for (size_t i = 0; i < expresion.size(); i++)
        {

        }
    }
    throw invalid_argument("Invalid expresion");
}
/**
 * @brief Make an operation from a string.
 * @expresion: The expresion to make the operation.
 * @return double The result of the operation.
*/
double MakeOperation(string expresion)
{
    expresion = deleteSpaces(expresion);
    return executeOperation(expresion);
}