#ifndef _GLOBAL_H
#define _GLOBAL_H

#include <string>
#include <boost\regex.hpp>


boost::regex Regex("(\s)|([0-9]+)|([A-Z_a-z]*[A-Z_a-z0-9]+)|(;)"); //正则表达式
boost::smatch what;
typedef unsigned char Bytes; //一个字节
#define MemSize 256 //虚拟机内存

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
//CPU设计
struct CPU
{
	Bytes Accumulator;//累加器
	Bytes StackPointer;//堆栈指针SP
	Bytes IndexRegister;//变址寄存器
	Bytes InstructionRegister;//指令寄存器
	Bytes ProgramCounter;//程序计数器
	Bytes BasePointer;//基址指针
	bool Psw1, Psw2, Psw3;//标志寄存器
};
//虚拟机的运行状态
enum Status
{
	Running,
	Finished,
	ErrorOp,
	ErrorData,
};
//代码字符流
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
//字符流类型
enum TokenType
{
	ASMCode,
	Lablel,
	ReferLabel,
	Number,
	ID,
	UnKnown
};
//虚拟机机器指令表
enum Operand
{
	OpHALT,	//CPU暂停指令 格式：HALT
	OpIN,	//将一个数写入Register[data1] 
	OpOUT,	//将Register[data1]的数输出
	OpADD,
	OpSUB,
	OpMUL,
	OpDIV,
	OpINC,//+1
	OpDEC,//-1
	OpPUSH,
	OpPOP,
	OpCMP,
	OpJMP,
	OpLOAD,	//将内存中Data[Register[num2]+num3] 存到Register[num1]
	OpSTORE,//将Register[num1]存到Data[Register[num2]+num3]
	OpLDA,	//load regs[s]+t into regs[r]
	OpLDC,	// load t into regs[r]
	OpJL,	//<
	OpJLE,	//<=
	OpJNLE,	//>
	OpJNL,	//>=
	OpJE,	//==
	OpJNE,	//!=
	OpError,//错误指令

};
//指令助记符
string OpMemonic[] =
{
	"HALT",
	"IN",
	"OUT",
	"ADD",
	"SUB",
	"MUL",
	"DIV",
	"INC"
	"DEC"
	"PUSH"
	"POP"
	"CMP"
	"JMP"
	"LOAD",
	"STORE",
	"LDA",
	"LDC",
	"JL",
	"JLE",
	"JNLE",
	"JNL",
	"JE",
	"JNE",
};
#endif
