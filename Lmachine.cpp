#include <iostream>
#include <fstream>
#include "Lmachine.h"
#include "Assembler.h"
using namespace std;
/*
--------------------------------------------------------------
|						虚拟机                               |
--------------------------------------------------------------
*/

//初始化
void Lmachine::Init()
{
	
	/*
		初始化
	*/

}
//执行加1操作
void Lmachine::Increment(Bytes & data)
{
	data = (data + 257) % 256;
}
//执行减1操作
void Lmachine::Decrement(Bytes & data)
{
	data = (data + 255) % 256;
}
void Lmachine::LmachineRun()
{
	Bytes ProgramValue;//保存PC的当前值
	Bytes Carry;//程序进位位的状态
	cpu.Carry = false;

	cpu.Accumulator = 0;
	cpu.IndexRegister = 0;
	cpu.BasePointer = 0;
	cpu.StackPointer = 0;
	cpu.ProgramCounter = 0;
	CPUStatus = Running;
	do
	{
		cpu.InstructionRegister = Memory[cpu.ProgramCounter];//从内存中取指令送入指令寄存器
		ProgramValue = cpu.ProgramCounter;
		Increment(cpu.ProgramCounter);//PC指向向一条将要执行的指令地址
		switch (cpu.InstructionRegister)
		{
		case OpCLEARACC://CPU累加器清0
			cpu.Accumulator = 0;
			break;
		default:
			break;
		}
	}
}
//主函数
int main()
{
	Lmachine *lmachine=new Lmachine;
	lmachine->Init();
	Assembler * assembler = new Assembler;


}