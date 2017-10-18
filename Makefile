CXX	= g++

CXXFLAGS= -std=c++11
LDFLAGS	= 

TARGET	= editor
OBJS	= main.o

%.o:%cc
	$(CXX) $(CXXFLAGS) $< -o $@

$(TARGET):$(OBJS)
	$(CXX) $(LDFLAGS) $^ -o $@

