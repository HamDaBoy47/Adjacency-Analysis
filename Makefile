CXX= g++
CXXFLAGS=-Wall -Wextra -pedantic -std=c++11

SRCS = main.cpp Rectangle.cpp
OBJ = $(SRCS:.cpp=.o)
EXEC = main.exe

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(EXEC)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)