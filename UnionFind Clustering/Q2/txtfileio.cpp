#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "txtfileio.h"

using namespace std;

vector<string> txtfileio::readlines(string filename, vector<string>::size_type num_lines)
{
    ifstream input_file;
    string line;
    vector<string> lines;
    vector<string>::size_type current_line = 0, vec_max_size = lines.max_size();    

    input_file.open(filename.c_str());
    if(!input_file.is_open())
    {
        cerr << "<fnc>file::readlines - Error opening file: " << filename << endl;
        return lines;
    }
    
    if(num_lines < 0)
        num_lines = vec_max_size;
        
    // loop invariant: exactly current_line lines have been read from file
    while(current_line < num_lines && getline(input_file, line, '\n'))
    {
        lines.push_back(line);
        ++current_line;
    }
    
    if(current_line == vec_max_size)
        cerr << "<fnc>file::readlines - max possible number of lines read from file" << endl; 
    input_file.close();
    
    return lines;
}


void txtfileio::tokenize(const string &line, vector<string> &tokens, const string &delimiters,
    bool trimEmpty)
{
    string::size_type pos, lastPos = 0;
    
    if(line.size() == 0)
        return;

    while(true)
    {
        pos = line.find_first_of(delimiters, lastPos);
        if(pos == string::npos)
        {
            pos = line.size();
            if(pos != lastPos || !trimEmpty)
                tokens.push_back(line.substr(lastPos, pos - lastPos));
            break;
        }
        else
        {
            if(pos != lastPos || !trimEmpty)
                tokens.push_back(line.substr(lastPos, pos - lastPos));
            lastPos = pos + 1;
        }
   }
}