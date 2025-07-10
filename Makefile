CXX = g++
CXXFLAGS = -std=c++17 -Wall

TARGET = stock_management

SRCS = main.cpp product.cpp

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean
