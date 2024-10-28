C				:= gcc
CFLAGS		:= -Wall -Wextra -Wswitch-enum -std=c11 -pedantic -ggdb
LDLIBS		:= 
LDFLAGS		:= 
TARGET		:= ctypesDemo

SRC_DIR		:= src
OBJ_DIR		:= obj
BIN_DIR		:= bin

EXE				:= $(BIN_DIR)/$(TARGET)
SRC				:= $(wildcard $(SRC_DIR)/*.c)
OBJ				:= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)


all: $(EXE)

$(EXE): $(OBJ) | $(BIN_DIR)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

check: $(EXE)
	valgrind -s --leak-check=full --show-leak-kinds=all $^

clean:
	@$(RM) -rv $(BIN_DIR) $(OBJ_DIR)

run: $(EXE)
	./$(EXE)
	

.PHONY: all check clean

-include $(OBJ:.o=.d)
