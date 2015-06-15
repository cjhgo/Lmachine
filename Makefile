Lvm:Main.o Lmachine.o Assembler.o Token.o
	g++ Main.o Lmachine.o Assembler.o Token.o -o Lvm /usr/local/lib/libboost_regex.a
Main.o:Main.cpp  Lmachine.h Assembler.h
	g++ -c Main.cpp
Lmachine.o:Lmachine.cpp Lmachine.h Global.h
	g++ -c Lmachine.cpp
Assembler.o:Assembler.cpp Assembler.h Lmachine.h Global.h
	g++ -c Assembler.cpp
Token.o:Token.cpp Token.h
	g++ -c Token.cpp
