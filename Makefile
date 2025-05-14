CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++17 -O0 -g

TARGET = egzek

SRCS = main.cpp ./struktury/heap.cpp
HEADERS = algorytmy.hh generator.hh ./struktury/dynamic_array.hh ./struktury/list.hh ./struktury/adjacency_list.hh ./struktury/adjacency_matrix.hh ./struktury/pair.hh ./struktury/heap.hh ./struktury/prique.hh ./struktury/edge_list.hh

all: $(TARGET)

$(TARGET): $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)
