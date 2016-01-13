all:	main 

main:	main.o Generator.o Memory_manager.o Processor.o memTree.o Timer.o
	g++ main.o Generator.o Memory_manager.o Processor.o memTree.o Timer.o

main.o:	main.cpp 
	g++ -c main.cpp

Generator.o:	Generator.cpp Generator.h
	g++ -c Generator.cpp

Memory_manager.o:	Memory_manager.cpp Memory_manager.h
	g++ -c Memory_manager.cpp

Processor.o:	Processor.cpp Processor.h
	g++ -c Processor.cpp

memTree.o:		memTree.cpp memTree.h
	g++ -c memTree.cpp
	
Timer.o:		Timer.cpp timer.h
	g++ -c Timer.cpp