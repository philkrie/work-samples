CXX = g++
CXXFLAGS = -g -std=c++11 
# Uncomment the CXXFLAGS definition below to use the parallel MR runtime
#CXXFLAGS = -g -std=c++11 -pthread -Wl,--no-as-needed -DPARALLEL_MR

all: test-wordCount test-sentenceStats


%.o : %.cpp mr.hpp
	$(CXX) -c $< $(CXXFLAGS) 

WC_OBJECTS = test-wordCount.o wordCount.o ioutils.o	
test-wordCount: $(WC_OBJECTS)
	$(CXX) -o $@ $(WC_OBJECTS) $(CXXFLAGS)
	
SS_OBJECTS = test-sentenceStats.o sentenceStats.o ioutils.o	
test-sentenceStats: $(SS_OBJECTS)
	$(CXX) -o $@ $(SS_OBJECTS) $(CXXFLAGS)

PH_OBJECTS = test-phrases.o phrases.o ioutils.o	
test-phrases: $(PH_OBJECTS)
	$(CXX) -o $@ $(PH_OBJECTS) $(CXXFLAGS)

clean:
	$(RM) *.o test-wordCount test-sentenceStats test-phrases
