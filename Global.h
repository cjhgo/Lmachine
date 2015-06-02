#ifndef _GLOBAL_H
#define _GLOBAL_H

#include <string>
#include <boost\regex.hpp>


boost::regex Regex("(\s)|([0-9]+)|([A-Z_a-z]*[A-Z_a-z0-9]+)|(;)"); //正则表达式
boost::smatch what;
typedef unsigned char Bytes; //一个字节
#define MemSize 256 //虚拟机内存

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
