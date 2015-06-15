#include "Lmachine.h"
#include "Assembler.h"

using namespace std;

//主函数
int main()
{
	Lmachine *lmachine = new Lmachine;
	Assembler *assembler = new Assembler;
	if (lmachine->Init())//判断虚拟机初始化是否成功
	{
		assembler->Init(lmachine->CodeFileName, lmachine);
		assembler->Run_Assembler();
		lmachine->LmachineRun();
	}
	else //不成功
		return 0;
}