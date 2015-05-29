#include <iostream>
#include <boost/regex.hpp>
#include <fstream>
#include "Lmachine.h"
using namespace std;
/*
	Assembler实现
*/
Assembler::Assembler(fstream *code, Lmachine *lmachine)
{
	
}
//初始化
void Lmachine::Init()
{
	/*
		打开的指定的汇编代码文件
	*/
	*Code.open("code.txt");
	/*
		初始化
	*/
	Data[0] = Data_SIZE - 1;
	for (int i = 1; i < Data_SIZE; i++) //清空数据区
		Data[i] = 0;
	for (int i = 0; i < Operand_SIZE; i++)//初始化只读指令存储区
	{
		OperandMem[i].op = OpHALT;
		OperandMem[i].data1 = 0;
		OperandMem[i].data2 = 0;
		OperandMem[i].data3 = 0;
	}
	for (int i = 0; i = RegisterNum; i++)//清空寄存器
		Register[i] = 0;
}
//将Code一行一行读取到LmachineToken队列中
void Lmachine::ReadLine()
{
	string Line;
	while (getline(Code, Line)) //每行读取汇编代码
	{
		if (boost::regex_search(Line, what, Regex))
		{
			while (what[0].length() != 0)
			{
				if (what[2].matched == true) //number
				{
					string tokentext(what[2].first, what[2].second);
					int tokennumber = atoi(tokentext.c_str());
					Token token(tokennumber);
					LmachineToken.push(token);
					if ((Line.length() - tokentext.length() - 1) == 0)
						break;
					Line = Line.substr((Line.length() - tokentext.length() - 1));
				}
				else if (what[3].matched == true) //ID
				{
					string tokentext(what[3].first, what[3].second);
					Token token(tokentext);
					LmachineToken.push(token);
					if ((Line.length() - tokentext.length() - 1) == 0)
						break;
					Line = Line.substr((Line.length() - tokentext.length() - 1));
				}
				if (boost::regex_search(Line, what, Regex))
				{
					continue;
				}
			}
		}
	}
}
int Lmachine::OpClass(int c)
{
	if (c <= OpRRMODE)
		return OperandRR;
	else if (c <= OpRMMODE)
		return OperandRM;
	else
		return OperandRA;
}
//将指令加载到只读指令存储区
void Lmachine::Load()
{
	int i = 0;
	while (!LmachineToken.empty())
	{
		OperandMem[i].op = Token2Op(LmachineToken.front());//获取指令
		LmachineToken.pop();
		//data1
		if (Token2Int(LmachineToken.front()) < 0 || Token2Int(LmachineToken.front()) >= RegisterNum)
		{
			Error("data1:no such register");
			break;
		}
		OperandMem[i].data1 = Token2Int(LmachineToken.front());
		LmachineToken.pop();
		//data2
		if (Token2Int(LmachineToken.front()) < 0 || Token2Int(LmachineToken.front()) >= RegisterNum)
		{
			Error("data1:no such register");
			break;
		}
		OperandMem[i].data2 = Token2Int(LmachineToken.front());
		LmachineToken.pop();
		//data3
		if (OperandMem[i].op<OpRRMODE&&(Token2Int(LmachineToken.front()) < 0 || Token2Int(LmachineToken.front()) >= RegisterNum))
		{
			Error("data1:no such register");
			break;
		}
		OperandMem[i].data1 = Token2Int(LmachineToken.front());
		LmachineToken.pop();
		i++;
	}
}
//运行虚拟机
void Lmachine::Run()
{
	Command * command = NULL;
	Result result; //运行结果
	command = &OperandMem[Register[PC_Register]];
	while (command->op != OpHALT)
	{
		if ((result = OpRun(command)) != OK)
			Error(ResultTable[result]);
		if (command->op < OpJLT)
			Register[PC_Register]++;
		command = &OperandMem[Register[PC_Register]];

	}
}
//指令执行
Result Lmachine::OpRun(Command * command)
{
	switch (command->op)
	{
	case OpIN:	return In_Instruction(command);
	case OpOUT:	return Out_Instruction(command);
	case OpADD: return Add_Instruction(command);
	case OpSUB:	return Sub_Instruction(command);
	case OpMUL:	return Mul_Instruction(command);
	case OpDIV:	return Div_Instruction(command);
	case OpLOAD:return Load_Instruction(command);
	case OpSTORE:return Store_Instruction(command);
	case OpLDA:	return Lad_Instruction(command);
	case OpLDC:return Ldc_Instruction(command);
	case OpJLT:return Jlt_Instruction(command);
	case OpJLE:return Jle_Instruction(command);
	case OpJGT:return Jgt_Instruction(command);
	case OpJGE:return Jge_Instruction(command);
	case OpJEQ:return Jeq_Instruction(command);
	case OpJNE:return Jne_Instruction(command);
	default:
		Error("None Command");
		break;
	}
}
Result Lmachine::In_Instruction(Command *command)
{
	int data = command->data1;
	cin >> Register[data];
	return OK;
}
Result Lmachine::Out_Instruction(Command * command)
{
	int data = command->data1;
	cout << Register[data] << endl;
	return OK;
}
Result Lmachine::Add_Instruction(Command * command)
{
	int num1 = command->data1;
	int num2 = command->data2;
	int num3 = command->data3;
	Register[num1] = Register[num2] + Register[num3];
	return OK;
}
Result Lmachine::Sub_Instruction(Command * command)
{
	int num1 = command->data1;
	int num2 = command->data2;
	int num3 = command->data3;
	Register[num1] = Register[num2] - Register[num3];
	return OK;
}
Result Lmachine::Mul_Instruction(Command * command)
{
	int num1 = command->data1;
	int num2 = command->data2;
	int num3 = command->data3;
	Register[num1] = Register[num2] * Register[num3];
	return OK;
}
Result Lmachine::Div_Instruction(Command * command)
{
	int num1 = command->data1;
	int num2 = command->data2;
	int num3 = command->data3;
	if (Register[num3] == 0)
		return ZERO_ERROR;
	Register[num1] = Register[2] / Register[3];
	return OK;
}
Result Lmachine::Load_Instruction(Command * command)
{
	int num1 = command->data1;
	int num2 = command->data2;
	int num3 = command->data3;
	if (Register[num2] + num3 < 0 || Register[num2] + num3 >= Data_SIZE)
		return DataMEM_ERROR;
	Register[num1] = Data[Register[num2] + num3];
	return OK;
}
Result Lmachine::Store_Instruction(Command * command)
{
	int num1 = command->data1;
	int num2 = command->data2;
	int num3 = command->data3;
	if (Register[num2] + num3 < 0 || Register[num2] + num3 >= Data_SIZE)
		return DataMEM_ERROR;
	Data[Register[num2] + num3] = Register[num1];
	return OK;
}
Result Lmachine::Lda_Instruction(Command * command)
{
	int num1 = command->data1;
	int num2 = command->data2;
	int num3 = command->data3;
	if (Register[num2] + num3 < 0 || Register[num2] + num3 >= Data_SIZE)
		return DataMEM_ERROR;
	Register[num1] = Register[num2] + num3;
	return OK;
}
Result Lmachine::Ldc_Instruction(Command * command)
{
	int num1 = command->data1;
	int num3 = command->data3;
	Register[num1] = num3;
	return OK;
}
Result Lmachine::Jl_Instruction(Command * command) //<
{
	int num1 = command->data1;
	int num2 = command->data2;
	int num3 = command->data3;
	if (Register[num2] + num3 < 0 || Register[num2] + num3 >= Data_SIZE)
		return OperandMEM_ERROR;
	if (Register[num1] < 0)
		Register[PC_Register] = Register[num2] + num3;
	return OK;
}
Result Lmachine::Jle_Instruction(Command * command)//<=
{
	int num1 = command->data1;
	int num2 = command->data2;
	int num3 = command->data3;
	if (Register[num2] + num3 < 0 || Register[num2] + num3 >= Data_SIZE)
		return OperandMEM_ERROR;
	if (Register[num1] <=0)
		Register[PC_Register] = Register[num2] + num3;
	return OK;
}
Result Lmachine::Jnle_Instruction(Command * command)//>
{
	int num1 = command->data1;
	int num2 = command->data2;
	int num3 = command->data3;
	if (Register[num2] + num3 < 0 || Register[num2] + num3 >= Data_SIZE)
		return OperandMEM_ERROR;
	if (Register[num1]> 0)
		Register[PC_Register] = Register[num2] + num3;
	return OK;
}
Result Lmachine::Jle_Instruction(Command * command)
{
	int num1 = command->data1;
	int num2 = command->data2;
	int num3 = command->data3;
	if (Register[num2] + num3 < 0 || Register[num2] + num3 >= Data_SIZE)
		return OperandMEM_ERROR;
	if (Register[num1]>= 0)
		Register[PC_Register] = Register[num2] + num3;
	return OK;
}
Result Lmachine::Je_Instruction(Command * command)//==
{
	int num1 = command->data1;
	int num2 = command->data2;
	int num3 = command->data3;
	if (Register[num2] + num3 < 0 || Register[num2] + num3 >= Data_SIZE)
		return OperandMEM_ERROR;
	if (Register[num1] == 0)
		Register[PC_Register] = Register[num2] + num3;
	return OK;
}
Result Lmachine::Jne_Instruction(Command * command)//!=
{
	int num1 = command->data1;
	int num2 = command->data2;
	int num3 = command->data3;
	if (Register[num2] + num3 < 0 || Register[num2] + num3 >= Data_SIZE)
		return OperandMEM_ERROR;
	if (Register[num1] != 0)
		Register[PC_Register] = Register[num2] + num3;
	return OK;
}
//主函数
int main()
{
	Lmachine *Lvm=new Lmachine;
	Assembler Asm(Lvm->Code, Lvm);


}