#pragma once
#ifndef _LMACHINE_H
#define _LMACHINE_H
#include "Global.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;


enum Result
{
	OK,		//正确执行
	HALT,	//停止执行
	OperandMEM_ERROR,	//IMEM错误
	DataMEM_ERROR,	//DMEM错误
	ZERO_ERROR,//零除错误
	NONECOMMAND_ERROR,//指令错误
};
struct Command
{
	Operand op;
	int data1;	//r
	int data2;	//s
	int data3;	//t
};

string ResultTable[] =
{
	"OK",
	"HLT"
	"INSTRUCTION MEMORY FAULT",
	"DATA MEMORY FAULT",
	"DIVISION BY 0"
};
//同名引用结点
struct SymbolReferenceNode
{
	Bytes ReferenceAddr;	   //同名引用的符号的内存地址
	SymbolReferenceNode * Next;//下一个同名引用的结点
};
//符号定义
struct Symbol
{
	string SymbolName;	//符号地址名
	Bytes SymbolAddr;	//符号内存地址
	SymbolReferenceNode * First;//该符号首次出现
};


//虚拟机
class Lmachine
{
public:
	/*
		数据成员
	*/
	Bytes Memory[MemSize];//虚拟机内存空间

	/*
		成员函数
	*/
	void Init();//初始化
	inline string GetMemonic(int i) //返回机器指令i的助记符
	{
		return  OpMemonic[i];
	}


};

#endif
