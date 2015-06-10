#pragma once
#ifndef _ASSEMBLER_H
#define _ASSEMBLER_H
#include "Token.h"
#include "Lmachine.h"
#include "Global.h"
//汇编器
class Assembler
{
public:
	/*
	数据成员
	*/
	Lmachine * lmachine;//虚拟机实例指针
	int TokenIndex;//token记号索引
	fstream *Code;//要加载的汇编文件
	vector<Token> LmachineToken; //汇编代码字符流
	vector<Symbol> SymbolTable;//符号表动态数组
	/*
	成员函数
	*/
	Assembler();
	~Assembler();
	void Init(string codefilename);//初始化
	TokenType Lexer(Token token, string &Strtoken, Operand &operand);//汇编代码字符流分析
	void ReadLine();//将FILE类型Code名字读取到LmachineToken中
	void Run_Assembler();	//运行汇编器
	void BuildSymbolTable();//构建符号表
	int  SearchSymbol(string symbolname, int sign);//在符号表中查找符号
	Bytes SearchCmd(Token token);//查询汇编指令表，返回对应的机器指令，机器指令隐含为指令数组的下标
};
#endif