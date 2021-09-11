# Variables
BIN = bin
SOURCE = src
INC = include

# Executable file name
TARGET = $(BIN)/executable

# Flags for the compiler
CXXFLAGS = -std=c++11 -I$(INC)

# Compiler definition
CXX = g++ -Ofast

# Definition of source files
SRC = $(SOURCE)/main.cpp $(SOURCE)/Board.cpp $(SOURCE)/Car.cpp $(SOURCE)/Router.cpp $(SOURCE)/Node.cpp
# Order to be executed by default
all: clean $(TARGET)

# Execution rule
$(TARGET):
	@echo "Generating executable."
	@$(CXX) -o $@ $(CXXFLAGS) $(SRC)

# Rule for clean.
clean:
	@echo "Removing executable."
	@rm  -f $(TARGET)

run:
	@make && ./$(TARGET)
