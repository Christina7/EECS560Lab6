lab6: lab6.o queue23.o
	g++ -g -std=c++11 lab6.o tree23.o queue23.o -o lab6

lab6.o: lab6.cpp tree23.o
	g++ -c -g -std=c++11 lab6.cpp

tree23.o: tree23.cpp queue23.o
	g++ -c -g -std=c++11 tree23.cpp

queue23.o: queue23.cpp 
	g++ -c -g -std=c++11 queue23.cpp

clean:
	rm -f *~ *.o
