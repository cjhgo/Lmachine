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
void Lmachine::LmachineRun()
{
	Bytes Carry;//程序进位位的状态
	cpu.Psw1 = false;
	cpu.Psw2 = false;
	cpu.Psw3 = false;
	cpu.Accumulator = 0;
	cpu.IndexRegister = 0;
	cpu.BasePointer = 0;
	cpu.StackPointer = 0;
	cpu.ProgramCounter = 0;
	CPUStatus = Running;
	do
	{
		cpu.InstructionRegister = Memory[cpu.ProgramCounter];

	}
}
//主函数
int main()
{
	Lmachine *lmachine=new Lmachine;
	lmachine->Init();
	Assembler * assembler = new Assembler;


}