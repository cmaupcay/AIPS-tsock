INCLUDE_DIR=include
SRC_DIR=src
BIN_DIR=bin
BUILD_DIR=build
CC=gcc
CC_FLAGS=-Wall
LD_FLAGS=

default: tsock

all: erase tsock

tsock: main.o
	@mkdir -p $(BIN_DIR) ||:
	@$(CC) -o $(BIN_DIR)/tsock $(BUILD_DIR)/*.o $(LD_FLAGS) ||:
	@chmod +x $(BIN_DIR)/tsock
	@echo "   tsock compilé avec succès."

main.o: affichage.o
affichage.o: config.o
config.o: erreurs.o

pre:
	@mkdir -p $(BUILD_DIR) ||:

%.o: $(SRC_DIR)/%.c pre
	@echo " + Compilation de $<..."
	@$(CC) -o $(BUILD_DIR)/$@ -c $< $(CC_FLAGS) ||:

clean:
	@rm -rf $(BUILD_DIR) ||:

erase: clean
	@rm -rf $(BIN_DIR) ||:
	@echo " - Répertoire nettoyé."