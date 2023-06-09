#
#
#
CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic

INCLUDES = -Iinclude
LFLAGS = -Llib

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
BINARY = sos_gaming

$(BIN_DIR)/$(BINARY): $(OBJ) | $(BIN_DIR)
	@$(CC) $(OBJ) $(LFLAGS) -o $@
	@echo "done. check bin directory."
$(BIN_DIR):
	mkdir -p $@

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "compiled $<"
$(OBJ_DIR):
	mkdir -p $@

.PHONY: clean
clean:
	rm -f obj/*.o ../bin/sos_gaming
