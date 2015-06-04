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
	Lcpu.Carry = false;

	Lcpu.Accumulator = 0;
	Lcpu.IndexRegister = 0;
	Lcpu.BasePointer = 0;
	Lcpu.StackPointer = 0;
	Lcpu.ProgramCounter = 0;
	LcpuStatus = Running;
	do
	{
		Lcpu.InstructionRegister = Memory[Lcpu.ProgramCounter];//从内存中取指令送入指令寄存器
		ProgramValue = Lcpu.ProgramCounter;
		Increment(Lcpu.ProgramCounter);//PC指向向一条将要执行的指令地址
		switch (Lcpu.InstructionRegister)
		{
		case OpHALT:	//CPU暂停指令 格式：HALT
			LcpuStatus = Finished;
			break;
		case OpCLEARAX:	//累加器清0
			Lcpu.Accumulator = 0;
			break;
		case OpClEARC:	//进位标志器清0
			Lcpu.Carry = 0;
			break;
		case OpCLEARI://变址寄存器清0
			Lcpu.IndexRegister = 0;
			break;
		case OpINAXD:	//将10进制数写入累加器
		case OpINAXB:	//将2进制数写入累加器
		case OpINAXA:	//将ascii字符写入累加器
		case OpOUTAXD:	//将累加器数据以10进制形式输出
		case OpOUTAXB:	//将累加器数据以2进制形式输出
		case OpOUTAXA:	//将累加器数据以ascii字符形式输出

		case OpINCAX://累加器加1，影响标志器
			Increment(Lcpu.Accumulator);
			SetFlags(Lcpu.Accumulator);
			break;
		case OpDECAX://累加器减1，影响标志器
			Decrement(Lcpu.Accumulator);
			SetFlags(Lcpu.Accumulator);
			break;
		case OpINCI://变址寄存器加1，影响标志器
			Increment(Lcpu.IndexRegister);
			SetFlags(Lcpu.IndexRegister);
			break;
		case OpDECI://变址寄存器减1，影响标志器
			Decrement(Lcpu.IndexRegister);
			SetFlags(Lcpu.IndexRegister);
			break;
		case OpAXTOI://累加器内容送入变址寄存器 x
			Lcpu.IndexRegister = Lcpu.Accumulator;
			break;
		case OpPUSH://压栈，堆栈指针减1，累加器的内容压入栈顶。
			Decrement(Lcpu.StackPointer);
			Memory[Lcpu.StackPointer] = Lcpu.Accumulator;
			break;
		case OpPOP://出栈，堆栈指针加1，将栈顶内容压入栈内
			Lcpu.Accumulator = Memory[Lcpu.StackPointer];
			Increment(Lcpu.StackPointer);
			Memory[Lcpu.StackPointer] = Lcpu.Accumulator;
			break;
		case OpLOADBAX://格式 LDA B ，将B地址单元中的内容送入累加器中，以当前PC所指内存的数值作为地址偏移
			Lcpu.Accumulator = Memory[Memory[Lcpu.ProgramCounter]];
			Increment(Lcpu.ProgramCounter);
			SetFlags(Lcpu.Accumulator);
			break;
				OpLOADIBAX,//将变址寄存器+立即数B所指的内存单元的内容送入累加器 A=[I+B]
				OpLOADVBAX,//将立即数B送入累加器
				OpLOADVBSP,//将立即数B中的内容送到SP寄存器
				OpSTOREAXB,//[B]=A
				OpSIOREAXBI,//[B+I]=A
				//加法
				OpADDB,//A=A+[B]
				OpADDIB,//A=A+[I+B]
				OpADDVB,//A=A+B
				OpADCB,//A=A+C+[B]
				OpADCIB,//A=A+C+[I+B]
				OpADCVB,//A=A+C+B
				//减法
				OpSUBB,//A=A-[B]
				OpSUBIB,//A=A-[I+B]
				OpSUBVB,//A=A-B
				OpSBCB,//A=A-C-[B]
				OpSBCIB,//A=A-C-[I+B]
				OpSBCVB,//A=A-C-B
				//比较
				OpCMPB,//A与[B]内容进行比较，影响标志位
				OpCMPIB,//A与[B+I]内容进行比较，影响标志位
				OpCMPVP,//A与B比较，影响标志位
				//与
				OpANDB,//A与[B]的内容位与，影响标志位
				OpANDVB,//A与B位与，影响标志位
				OpANDIB,//A与[I+B]位与，影响标志位
				//或
				OpORB,//A与[B]的内容位或，影响标志位
				OpORVB,//A与B位或，影响标志位
				OpORIB,//A与[I+B]位或，影响标志位
				//跳转
				OpJMPB,//跳转到B地址
				OpJZB,//如果Z标志为1，跳转到B单元
				OpJNZB,//如果Z标志为0，跳转到B单元
				OpJSB,//如果S标志为1，跳转到B单元
				OpJNSB,//如果S标志为0，跳转到B单元
				OpJC,//如果C标志为1，跳转到B单元
				OpJNC,//如果C标志为0，跳转到B单元
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