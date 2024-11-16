// #include "Sir.h"

// string deleteSpaces(string expresion)
// {
//     string updatedExpresion = "";
//     for (size_t i = 0; i < expresion.size(); i++)
//     {
//         if (expresion[i] != ' ')
//             updatedExpresion.push_back(expresion[i]);
//     }
//     return updatedExpresion;
// }

// double applyOperation(string left, string right, char op) {
//     double leftd = 0, rightd = 0;
//     try {
//         leftd = stod(left);
//     } catch (const invalid_argument &e) {
//         try {
//             leftd = GetVariable(left);
//         } catch (const invalid_argument &e) {
//             throw invalid_argument("Invalid operation: Invalid left operand");
//         }
//     }
//     try {
//         rightd = stod(right);
//     } catch (const invalid_argument &e) {
//         try {
//             rightd = GetVariable(right);
//         } catch (const invalid_argument &e) {
//             throw invalid_argument("Invalid operation: Invalid right operand");
//         }
//     }

//     switch (op) {
//         case '+':
//             return leftd + rightd;
//         case '-':
//             return leftd - rightd;
//         case '*':
//             return leftd * rightd;
//         case '/':
//             if (rightd == 0) {
//                 throw invalid_argument("Division by zero");
//             }
//             return leftd / rightd;
//         case '^':
//             return pow(leftd, rightd);
//         case '%':
//             return (int)leftd % (int)rightd;
//         case '&':
//             return (int)leftd & (int)rightd;
//         case '|':
//             return (int)leftd | (int)rightd;
//         case '<':
//             return (int)leftd << (int)rightd;
//         case '>':
//             return (int)leftd >> (int)rightd;
//         default:
//             throw invalid_argument("Invalid operator");
//     }
// }

// double executeOperation(string expresion)
// {
//     // Handle parentheses first

//     size_t openPos = expresion.rfind('(');
//     while (openPos != string::npos) {
//     size_t closePos = expresion.find(')', openPos);
//     string innerExp = expresion.substr(openPos + 1, closePos - openPos - 1);
//     double result = executeOperation(innerExp);  
//     expresion.replace(openPos, closePos - openPos + 1, to_string(result));
//     openPos = expresion.rfind('(', openPos - 1);
//     }


//     // process operators based on precedence
//     // handle multiplication, division, and modulus
//     for (size_t i = 0; i < expresion.size(); ++i) {
//         if (expresion[i] == '*' || expresion[i] == '/' || expresion[i] == '%') {
//             size_t leftStart = expresion.find_last_of("+-*/%", i - 1);
//             string left = expresion.substr(leftStart + 1, i - leftStart - 1);
//             size_t rightEnd = expresion.find_first_of("+-*/%", i + 1);
//             string right = expresion.substr(i + 1, rightEnd - i - 1);
//             double result = applyOperation(left, right, expresion[i]);
//             expresion.replace(leftStart + 1, rightEnd - leftStart - 1, to_string(result));
//             i = leftStart + to_string(result).size();  // Update position after modification
//         }
//     }

//     // Then handle addition and subtraction
//     for (size_t i = 0; i < expresion.size(); ++i) {
//         if (expresion[i] == '+' || expresion[i] == '-') {
//             size_t leftStart = expresion.find_last_of("+-", i - 1);
//             string left = expresion.substr(leftStart + 1, i - leftStart - 1);
//             size_t rightEnd = expresion.find_first_of("+-", i + 1);
//             string right = expresion.substr(i + 1, rightEnd - i - 1);
//             double result = applyOperation(left, right, expresion[i]);
//             expresion.replace(leftStart + 1, rightEnd - leftStart - 1, to_string(result));
//             i = leftStart + to_string(result).size();
//         }
//     }

//     // Return the final evaluated expression as a number
//     return stod(expresion);
// }
// /**
//  * @brief Make an operation from a string.
//  * @expresion: The expresion to make the operation.
//  * @return double The result of the operation.
// */
// double MakeOperation(string expresion)
// {
//     expresion = deleteSpaces(expresion);
//     return executeOperation(expresion);
// }