// StringList.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "CStringList.h"
#include <vector>

int main()
{
    CStringList list;
    list.PushBack("str1");
    list.PushBack("str3");

    auto iter = list.begin();
    iter++;
    list.Insert(iter, "str2");
    for (auto it = list.begin(); it != list.end(); it++)
    {
        std::cout << *it;
    }
    //std::vector<std::string> list;
    //list.push_back("str1");
    //list.push_back("str2");
    //auto iter = list.end();
    //iter--;
    //std::cout << *iter;
    return 0;
}