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
	bool Carry;//进位标志器
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
	//B 代表立即数，前面加V 代表立即数本身  不加V代表[B] 即B地址单元中的内容
	OpHALT,	//CPU暂停指令 格式：HALT
	OpCLEARACC,		//累加器清0
	OpClEARCARRY,	//进位标志器清0
	OpCLEARINDEXREG,//变址寄存器清0
	OpINACCD,	//将10进制数写入累加器
	OpINACCB,	//将2进制数写入累加器
	OpINACCA,	//将ascii字符写入累加器
	OpOUTACCD,	//将累加器数据以10进制形式输出
	OpOUTACCB,	//将累加器数据以2进制形式输出
	OpOUTACCA,	//将累加器数据以ascii字符形式输出
	OpINC,//累加器加1，影响标志器
	OpDEC,//累加器减1，影响标志器
	OpINCINDEXREG,//变址寄存器加1，影响标志器
	OpDECINDEXREG,//变址寄存器减1，影响标志器
	OpACCTOINDEXREG,//累加器内容送入变址寄存器 x
	OpPUSH,//压栈，堆栈指针减1，累加器的内容压入栈顶。
	OpPOP,//出栈，堆栈指针加1，将栈顶内容压入栈内
	OpLAB,//格式 LDA B ，将B地址单元中的内容送入累加器中，以当前PC所指内存的数值作为地址偏移
	OpLAIB,//将变址寄存器+立即数B所指的内存单元的内容送入累加器 A=[I+B]
	OpLAVB,//将立即数B送入累加器
	OpLSVB,//将立即数B中的内容送到SP寄存器
	OpSBA,//[B]=A
	OpSIBA,//[B+I]=A
	//加法
	OpADDB,//A=A+[B]
	OpADDIB,//A=A+[I+B]
	OpADDVA,//A=A+B
	OpADCB,//A=A+C+[B]
	OpADCIB,//A=A+C+[I+B]
	OpADCVB,//A=A+C+B
	//减法
	OpSUBB,//A=A+[B]
	OpSUBIB,//A=A+[I+B]
	OpSUBVA,//A=A+B
	OpSBCB,//A=A+C+[B]
	OpSBCXB,//A=A+C+[I+B]
	OpSBCVB,//A=A+C+B
	//比较
	OpCMPB,//A与[B]内容进行比较，影响标志位
	OpCMPIB,//A与[B+I]内容进行比较，影响标志位
	OpCMPVP,//A与B比较，影响标志位
	//与
	OpANDB,//A与[B]的内容位与，影响标志位
	OpANDVB,//A与B位与，影响标志位
	OpANDIB,//A与[I+B]位与，影响标志位
	//或


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
