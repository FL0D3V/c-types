CC				:= gcc
CFLAGS		:= -Wall -Wextra -Wswitch-enum -std=c11 -pedantic -ggdb
LDLIBS		:= 
LDFLAGS		:= 
TARGET		:= ctypes

SRC_DIR		:= src
OBJ_DIR		:= obj
BIN_DIR		:= bin # . for root & e.g. bin for special folder

EXE				:= $(BIN_DIR)/$(TARGET)
SRC				:= $(wildcard $(SRC_DIR)/*.c)
OBJ				:= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)


.PHONY: all clean

all: $(EXE)

$(EXE): $(OBJ) | $(BIN_DIR)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	@$(RM) -rv $(BIN_DIR) $(OBJ_DIR)

-include $(OBJ:.o=.d)
