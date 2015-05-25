#pragma once
#ifndef _LMACHINE_H
#define _LMACHINE_H
enum Operand
{
	OpHLT,//CPU暂停指令 格式：HLT
	OpIN,//从端口读取数据
	OpOUT,//向端口写数据
	OpADD,
	OpSUB,
	OpMUL,
	OpDIV,
	OpRADDRMODE,//寄存器寻址
	OpLOAD,//读取
	OpSTORE,//存储
	OpMADDRMODE,//内存中寻址

	OpJLT,
	OpJLE,
	OpJGT,
	OpJGE,
	OpJEQ,
	OpJNE,

};
struct Command
{
	Operand op;
	int data1;
	int data2;
	int data3;
};
#endif