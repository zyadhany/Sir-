#include "Sir.h"

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

bool IsOperator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '%' || c == '&' || c == '|' ||c == '<' || c == '>';
}

bool IsValidOperation(string expresion)
{
    for (size_t i = 0; i < expresion.size(); i++)
    {
        if(IsOperator(expresion[i]))
        {
            if(i == 0 || i == expresion.size() - 1)
            {
                throw invalid_argument("operator can't be at the start or the end of the expresion");
            }
            if(IsOperator(expresion[i - 1]) || IsOperator(expresion[i + 1]) || expresion[i - 1] == '(' || expresion[i + 1] == ')')
            {
                throw invalid_argument("two operators can't be next to each other");
            }
        }
    }
    if(IsValidBarnaces(expresion))
    {
        return true;
    }
    throw invalid_argument("Invalid brances");
    
}