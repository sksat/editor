CXX	= g++

CXXFLAGS= -std=c++11
LDFLAGS	= 

TARGET	= editor
OBJS	= main.o

RUNFLAGS=test.txt

%.o:%cc
	$(CXX) $(CXXFLAGS) $< -o $@

default:
	make $(TARGET)

run:
	./$(TARGET) $(RUNFLAGS)

clean:
	rm $(TARGET)
	rm $(OBJS)

$(TARGET):$(OBJS)
	$(CXX) $(LDFLAGS) $^ -o $@

