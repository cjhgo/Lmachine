#pragma once
#ifndef _TOKEN_H
#define _TOKEN_H
#include <iostream>
#include <string>
using namespace std;

//´úÂë×Ö·ûÁ÷
class Token
{
public:
	Token();
	Token(int number);
	Token(string ID);
	string ID;
	int Number;
	bool IsID();
	bool IsNumber();
	string GetID();
	int GetNumber();
};
#endif