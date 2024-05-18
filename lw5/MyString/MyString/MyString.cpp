// MyString.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "CMyString.h"

int main()
{
    //std::string s = "12345678901234567890";
    //s.erase();
    //std::cout << s.capacity() << " " << s.length();

    //CMyString s = "123";
    //CMyString d = s + "abc";
    //std::cout << d << " " << d + s << std::endl;

    //CMyString s1 = "123";
    //CMyString s2 = "456";
    //s1 += s2;
    //std::cout << s1 << std::endl;

    //s1 += "123";
    //std::cout << s1 << std::endl;

    //CMyString str1("123");
    //CMyString str2("A");
    //str1 += str2;
    //std::cout << str1.GetStringData() << std::endl;

    //CMyString abc("123");
    //std::cout << abc << std::endl;
    //std::cin >> abc;
    //std::cout << abc << std::endl;

    //const char* chs = "hello world";
    //CMyString str = CMyString(chs);
    //CMyString substr = str.SubString(6, 5);
    //std::cout << substr << std::endl;

    CMyString he("he");
    CMyString llo("ello world");
    he += llo;
    std::cout << he.GetCapacity();

    auto r = he.SubString(6, -6);
    std::cout << r;

    return 0;
}