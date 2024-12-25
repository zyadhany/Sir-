#include "Sir.h"

vector<string> readfile(const string &filename)
{
    vector<string> lines;
    ifstream file(filename);
    if (!file.is_open())
    {
        throw runtime_error("File not found");
    }
    string line;
    while (getline(file, line))
    {
        line = parseline(line);
        if (line.empty())
            continue;
        lines.push_back(line);
    }
    file.close();
    return lines;
}