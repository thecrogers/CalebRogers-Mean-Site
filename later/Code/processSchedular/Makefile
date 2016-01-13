all:	main 

main:	main.o Generator.o Schedular.o Processor.o 
	g++ main.o Generator.o Schedular.o Processor.o

main.o:	main.cpp 
	g++ -c main.cpp

Generaor.o:	Generator.cpp Generator.h
	g++ -c Generator.cpp

Schedular.o:	Schedular.cpp Schedular.h
	g++ -c Schedular.cpp

Processor.o:	Processor.cpp Processor.h
	g++ -c Processor.cpp