CXX	= g++

CXXFLAGS= -std=c++11 -g
LDFLAGS	= 

TARGET	= editor
OBJS	= main.o tui.o

RUNFLAGS=test.txt

%.o:%cc
	$(CXX) $(CXXFLAGS) $< -o $@

default:
	make $(TARGET)

run:
	make
	./$(TARGET) $(RUNFLAGS)

full:
	make clean
	make run

clean:
	rm -f $(TARGET)
	rm -f $(OBJS)

$(TARGET):$(OBJS)
	$(CXX) $(LDFLAGS) $^ -o $@

