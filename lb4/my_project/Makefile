CXX = g++

CXXFLAGS = -std=c++11 -Iincludes -mconsole

SRC_DIR = classes
SRCS = $(wildcard main.cpp $(SRC_DIR)/*.cpp)

OBJS = $(SRCS:.cpp=.o)

TARGET = sb

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)
