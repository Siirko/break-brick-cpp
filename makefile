CC := clang++
CFLAGS ?= -Wall -g -std=c++20
LDLIBS ?= -lm -lSDL2 -lSDL2_image -lSDL2_ttf

EXEC = break-brick

INCLUDE_PATH ?= ./include
SRC_PATH = ./src
OBJ_PATH = ./obj
BIN_PATH = ./bin

SOURCES := $(filter-out $(SRC_PATH)/main.cpp, $(wildcard $(SRC_PATH)/*.cpp $(SRC_PATH)/*/*.cpp $(SRC_PATH)/*/*/*.cpp))
INCLUDES := $(wildcard $(INCLUDE_PATH)/*.hpp $(INCLUDE_PATH)/*/*.hpp $(INCLUDE_PATH)/*/*/*.hpp)
OBJECTS  := $(SOURCES:$(SRC_PATH)/%.cpp=$(OBJ_PATH)/%.o)

all: 
	$(MAKE) $(BIN_PATH)/$(EXEC)

test: all
	$(MAKE) -C ./test	

docs:
	mkdir -p ./docs
	doxygen Doxyfile

$(BIN_PATH)/$(EXEC): $(OBJ_PATH)/main.o $(OBJECTS)
	mkdir -p $(BIN_PATH)
	$(CC) -o $@ $^ $(CFLAGS) -I$(INCLUDE_PATH) $(LDLIBS)
	@echo "Linking complete!"

$(OBJECTS): $(OBJ_PATH)/%.o : $(SRC_PATH)/%.cpp 
	mkdir -p $(dir $@)
	$(CC) -o $@ -c $< $(CFLAGS) -I$(INCLUDE_PATH) 

$(OBJ_PATH)/main.o: $(SRC_PATH)/main.cpp
	mkdir -p $(dir $@)
	$(CC) -o $@ -c $< $(CFLAGS) -I$(INCLUDE_PATH)


.PHONY: clean
clean:
	rm -fr $(OBJ_PATH)
	rm -fr $(BIN_PATH)
