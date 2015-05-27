#pragma once
#ifndef _LMACHINE_H
#define _LMACHINE_H
#include <iostream>
#include <string>
#include <queue>
#include <fstream>
using namespace std;
#define Operand_SIZE 1024 //只读指令存储器大小 
#define Data_SIZE 1024 //数据区大小
#define RegisterNum 8   //寄存器数目
#define PC_Regist 7   //程序计数器的下标

boost::regex Regex("(\s)|([0-9]+)|([A-Z_a-z]*[A-Z_a-z0-9]+)|(;)"); //正则表达式
boost::smatch what;
//格式 Op data1,data2,data3
enum Operand
{
	//RR
	OpHLT,//CPU暂停指令 格式：HLT
	OpIN,//将一个数写入Register[data1];
	OpOUT,//将Register[data1]的数输出
	OpADD,
	OpSUB,
	OpMUL,
	OpDIV,
	OpRRMODE,//寄存器寻址方式限制
	//RM 
	OpLOAD,//读取
	OpSTORE,//存储
	OpRMMODE,//内存中寻址
	//RA
	OpLDA,
	OpLDC,
	OpJLT,
	OpJLE,
	OpJGT,
	OpJGE,
	OpJEQ,
	OpJNE,
	OpRAMODE,

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
	IMEM_ERROR,	//IMEM错误
	DMEM_ERROR,	//DMEM错误
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
	"JLT",
	"JLE",
	"JGT",
	"JGE",
	"JEQ",
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
class Lmachine
{
public:
	/*
	数据成员
	*/
	Command OperandMem[Operand_SIZE];//只读指令存储区
	int Data[Data_SIZE];//数据存储区
	int Register[RegisterNum];//寄存器
	queue<Token> LmachineToken; //汇编代码字符流
	fstream Code;//要加载的汇编文件
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
	Result Lad_Instruction(Command * command);
	Result Ldc_Instruction(Command * command);
	Result Jlt_Instruction(Command * command);
	Result Jle_Instruction(Command * command);
	Result Jgt_Instruction(Command * command);
	Result Jge_Instruction(Command * command);
	Result Jeq_Instruction(Command * command);
	Result Jne_Instruction(Command * command);
};

#endif