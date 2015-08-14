CXX = g++ -std=c++11 -Wall -g

%.o : %.c 
	$(CXX) -c $< 

testMaze: testMaze.o maze.o
	$(CXX) -std=c++11 -o testMaze maze.o testMaze.o

main: utils.o main.o maze.o
	$(CXX) -o main maze.o utils.o main.o

clean:
	$(RM) main testMaze *.o
