#include "ds_model.h"
#include <iostream>

using namespace std;
using namespace ds_common;

dsaObj::dsaObj(string obj) : objType(obj)
{
}

void dsaObj::display()
{
    cout << objType << endl;
    cout << "{" << endl;

    vector<string> rows = str_out();
    for (auto &element : rows)
    {
        cout << "    " << element << endl;
    }

    cout << "}" << endl;
}

std::string ds_common::dsaObj::toString()
{
    string result = objType + " { ";

    vector<string> rows = str_out();
    for (auto &element : rows)
    {
        result = result + element + ", ";
    }

    return result.substr(0, result.length() - 2) + " }";
}
