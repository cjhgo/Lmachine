#ifndef _GLOBAL_H
#define _GLOBAL_H
typedef unsigned char Bytes; //一个字节
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
#endif
