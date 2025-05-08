CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++17 -O0

TARGET = egzek

SRCS = main.cpp
HEADERS = ./struktury/dynamic_array.hh ./struktury/list.hh ./struktury/adjacency_list.hh

all: $(TARGET)

$(TARGET): $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)
