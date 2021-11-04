CXX       := clang++
CXX_FLAGS := -Wall -Wextra -std=c++98 -fsanitize=address

BIN     := bin 
SRC     := 	src/server/server.o\
			src/client/client.o\
			src/main.o

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
