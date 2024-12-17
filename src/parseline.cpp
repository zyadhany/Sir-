#include "Sir.h"


bool check_double_quotes(string str) {
    bool check = false;
    for (int i = 0; i < str.size(); i++) {
        if(str[i] == '\\' && str[i + 1] == '\"' && check) i++;
        else if(str[i] == '\"') check = !check;
    }
    return !check;
}

string parseLine(string line)
{
    if (!check_double_quotes(line))
        throw runtime_error("Invalid string");

    string parsedLine = "";
    bool firstChar = false, firstSpace = false;
    for (int i = 0; i < line.size(); i++)
    {
        if(line[i] == '\"')
        {
            parsedLine += line[i];
            i++;
            while(line[i] != '\"')
            {
                if(line[i] == '\\' && line[i + 1] == '\"')
                    i++;
                parsedLine += line[i];
                i++;
            }
            parsedLine += line[i];
            continue;
        }
        if (line[i] != ' ')
        {
            firstChar = true;
            if(line[i] == '#')
                return parsedLine;
        }
        if (firstChar)
        {
            if (line[i] == ' ')
            {
                if (!firstSpace)
                {
                    parsedLine += line[i];
                    firstSpace = true;
                }
            }
            else
            {
                parsedLine += line[i];
                firstSpace = false;
            }
        }
    }
    return parsedLine;
}