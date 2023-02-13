INCLUDE_DIR=include
SRC_DIR=src
BIN_DIR=bin
BUILD_DIR=build
CC=gcc
CC_FLAGS=-Wall
LD_FLAGS=

default: all

all: erase tsock test

tsock: main.o
	@mkdir -p $(BIN_DIR) ||:
	@$(CC) -o $(BIN_DIR)/tsock $(BUILD_DIR)/*.o $(LD_FLAGS) ||:
	@chmod +x $(BIN_DIR)/tsock
	@echo "   tsock compilé avec succès."

main.o: puits.o source.o
puits.o: affichage.o reseau.o
source.o: affichage.o reseau.o
affichage.o: config.o
reseau.o: config.o
config.o: erreurs.o

pre:
	@mkdir -p $(BUILD_DIR) ||:

%.o: $(SRC_DIR)/%.c pre
	@echo " + Compilation de $<..."
	@$(CC) -o $(BUILD_DIR)/$@ -c $< $(CC_FLAGS) ||:

test: test.tcp test.udp

test.tcp: tsock
	@echo Test de tsock avec le protocole TCP...
	$(BIN_DIR)/tsock -p -n 10 7001 & $(BIN_DIR)/tsock -s localhost 7001

test.udp: tsock
	@echo Test de tsock avec le protocole UDP...
	$(BIN_DIR)/tsock -up -n 10 7002 & $(BIN_DIR)/tsock -us localhost 7002

clean:
	@rm -rf $(BUILD_DIR) ||:

erase: clean
	@rm -rf $(BIN_DIR) ||:
	@echo " - Répertoire nettoyé."