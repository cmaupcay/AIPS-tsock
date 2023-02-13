INCLUDE_DIR=include
SRC_DIR=src
BIN_DIR=bin
BUILD_DIR=build
CC=gcc
CC_FLAGS=-Wall

default: tsock

all: erase tsock

tsock: main.o
	@mkdir -p $(BIN_DIR) ||:
	@$(CC) -o $(BIN_DIR)/tsock $(BUILD_DIR)/main.o $(GCC_FLAGS) ||:
	@chmod +x $(BIN_DIR)/tsock
	@echo "   tsock compilé avec succès."

pre:
	@mkdir -p $(BUILD_DIR) ||:

%.o: $(SRC_DIR)/%.c pre
	@echo " + Compilation de $<..."
	@$(CC) -o $(BUILD_DIR)/$@ -c $< $(GCC_FLAGS) ||:

clean:
	@rm -rf $(BUILD_DIR) ||:

erase: clean
	@rm -rf $(BIN_DIR) ||:
	@echo " - Répertoire nettoyé."