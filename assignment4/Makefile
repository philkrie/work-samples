CXX = g++ -std=c++11 -Wall -g

%.o : %.c 
	$(CXX) -c $< 

testMaze: utils.o testMaze.o
	$(CXX) -o $@ testMaze.o utils.o

main: utils.o main.o
	$(CXX) -o $@ main.o utils.o

clean:
	$(RM) main testMaze *.o
