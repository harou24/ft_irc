CXX       := clang++
CXX_FLAGS := -Wall -Wextra -std=c++98 -fsanitize=address

BIN     := bin/server.o 
SRC     := 	src/server/server.cpp\
			src/client/client.cpp\
			src/main.cpp

INCLUDE := src/server/server.hpp\
			src/client/client.hpp

LIB     := lib
LIBRARIES   := 
EXECUTABLE  := server.exe


all: $(BIN)/$(EXECUTABLE)

run: clean all
	clear
	@echo "🚀 Executing..."
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)
	@echo "🚧 Building..."
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES)

clean:
	@echo "🧹 Clearing..."
	-rm $(BIN)/*
