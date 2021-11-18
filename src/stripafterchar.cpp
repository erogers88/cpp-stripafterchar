//============================================================================
// Name        : stripafterchar.cpp
// Author      : Erik Rogers
// Version     :
// Copyright   : MIT License
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <cstdio>
#include <iostream>
#include <string>
#include <filesystem>

using namespace std;

bool check_number_args(int argc)
{
    if(argc < 2)
    {
        return false;
    }
    return true;
}

string remove_before_char(string i_string, char delimiter)
{
    size_t last_delimiter = i_string.find_last_of(delimiter);
    string o_string = i_string.substr(last_delimiter+1);
    return o_string;
}

string remove_after_char(string i_string, char delimiter)
{
    size_t last_delimiter = i_string.find_last_of(delimiter);
    string o_string = i_string.substr(0, last_delimiter);
    return o_string;
}

int main(int argc, char **argv)
{
    if(!check_number_args(argc))
    {
        cerr << "ERROR: directory path required as argument" << endl;
        return -1;
    }

    for (const auto& dir_file : filesystem::recursive_directory_iterator(argv[1]))
    {
        filesystem::path old_name_path = dir_file.path();
        string old_name_string = old_name_path.string();
        string file_extension = remove_before_char(old_name_string, '.');
        string new_name_string = remove_after_char(old_name_string, '-') + '.' + file_extension;
        const char* old_name_c_str = old_name_string.c_str();
        const char* new_name_c_str = new_name_string.c_str();

        int rename_r = std::rename(old_name_c_str, new_name_c_str);
        if(rename_r != 0)
          {
            cout << "Error renaming file:" << old_name_string << endl;
          }
    }

    return 0;
}
