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

//主函数
int main()
{
	Lmachine *lmachine=new Lmachine;
	lmachine->Init();
	Assembler * assembler = new Assembler;


}