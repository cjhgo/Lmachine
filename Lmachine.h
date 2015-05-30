#pragma once
#ifndef _LMACHINE_H
#define _LMACHINE_H
#include "Global.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;
#define Operand_SIZE 1024 //只读指令存储器大小 
#define Data_SIZE 1024 //数据区大小
#define RegisterNum 8   //寄存器数目
#define PC_Register 7   //程序计数器的下标

boost::regex Regex("(\s)|([0-9]+)|([A-Z_a-z]*[A-Z_a-z0-9]+)|(;)"); //正则表达式
boost::smatch what;
//格式 Op data1,data2,data3
enum Operand
{
	//RR
	OpHALT,	//CPU暂停指令 格式：HALT
	OpIN,	//将一个数写入Register[data1] 
	OpOUT,	//将Register[data1]的数输出
	OpADD,
	OpSUB,
	OpMUL,
	OpDIV,
	OpRRMODE,//RR类型指令限制
	//RM 
	OpLOAD,	//将内存中Data[Register[num2]+num3] 存到Register[num1]
	OpSTORE,//将Register[num1]存到Data[Register[num2]+num3]
	OpRMMODE,//RM类型指令限制
	//RA
	OpLDA,	//load regs[s]+t into regs[r]
	OpLDC,	// load t into regs[r]
	OpJL,	//<
	OpJLE,	//<=
	OpJNLE,	//>
	OpJNL,	//>=
	OpJE,	//==
	OpJNE,	//!=
	OpRAMODE,//RA类型指令限制

};
enum OpCode //三种不同类型的opcode
{
	OperandRR,
	OperandRM,
	OperandRA,
};
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
string OpCodeTable[] =
{
	//RR
	"HLT",
	"IN",
	"OUT",
	"ADD",
	"SUB",
	"MUL",
	"DIV",
	"????"
	//RM
	"LD",
	"ST",
	"????",
	//RA
	"LDA",
	"LDC",
	"JL",
	"JLE",
	"JNLE",
	"JNL",
	"JE",
	"JNE",
	"????",
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
	string GetNumber();
};
//汇编器
class Assembler
{
public:
	/*
		数据成员
	*/
	vector<Token> LmachineToken; //汇编代码字符流
	vector<Symbol> SymbolTable;//符号表动态数组
	/*
		成员函数
	*/
	Assembler();
	Assembler(vector<Token> *token,Lmachine *lmachine);
	~Assembler();
	void Run_Assembler();	//运行汇编器
	void BuildSymbolTable();//构建符号表
	bool SearchSymbol(string symbolname);//在符号表中查找符号
	TokenType Lexer(Token token);//确定Token的属性
};
//虚拟机
class Lmachine
{
public:
	/*
	数据成员
	*/
	Command OperandMem[Operand_SIZE];//只读指令存储区
	Bytes Data[Data_SIZE];//数据存储区
	int Register[RegisterNum];//寄存器
	vector<Token> LmachineToken; //汇编代码字符流
	fstream *Code;//要加载的汇编文件
	int IADDR_Pointer;//指向只读指令存储区的指针
	int DADDR_Pointer;//指向数据存储区的指针
	/*
	成员函数
	*/
	void Init();//初始化
	void Load();//加载汇编代码到只读指令存储区
	void Run();//运行虚拟机
	void ReadLine();//将FILE类型Code名字读取到LmachineToken中
	string Error(string error);//输出错误信息
	Operand Token2Op(Token token);//将Token转换为枚举类型的Operand
	int Token2Int(Token token);
	int OpClass(int c);//根据c的值在Operand枚举查找指令的类型
	Result OpRun(Command * command);//命令执行
	Result In_Instruction(Command * command);
	Result Out_Instruction(Command * command);
	Result Add_Instruction(Command * command);
	Result Sub_Instruction(Command * command);
	Result Mul_Instruction(Command * command);
	Result Div_Instruction(Command * command);
	Result Load_Instruction(Command * command);
	Result Store_Instruction(Command * command);
	Result Lda_Instruction(Command * command);
	Result Ldc_Instruction(Command * command);
	Result Jl_Instruction(Command * command);
	Result Jle_Instruction(Command * command);
	Result Jnle_Instruction(Command * command);
	Result Jnl_Instruction(Command * command);
	Result Je_Instruction(Command * command);
	Result Jne_Instruction(Command * command);
};

#endif
