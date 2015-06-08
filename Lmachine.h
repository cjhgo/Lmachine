#pragma once
#ifndef _LMACHINE_H
#define _LMACHINE_H
#include "Global.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

//虚拟机
class Lmachine
{
public:
	/*
		数据成员
	*/
	CPU Lcpu;//虚拟机的CPU
	Status LcpuStatus;//虚拟机CPU的运行状态
	Bytes Memory[MemSize];//虚拟机内存空间

	/*
		成员函数
	*/
	void Init();//初始化
	inline string GetMemonic(int i) //返回机器指令i的助记符
	{
		return  OpMemonic[i];
	}
	void LmachineRun();//执行程序
	void Increment(Bytes &data);//执行加1操作
	void Decrement(Bytes &data);//执行减1操作
	void SetFlags(Bytes Register);//根据寄存器的值设定标志器
	void PrintRunError();//输出程序运行的错误
	Bytes Index();//计算变址地址 AX+B

};

#endif
