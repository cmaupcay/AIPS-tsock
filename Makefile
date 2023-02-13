default: tsock

all: erase tsock

tsock: tsock_v1.o
	@mkdir -p bin ||:
	@gcc -o bin/tsock build/tsock_v1.o ||:
	@chmod +x bin/tsock

tsock_v1.o:
	@echo Compilation de la version 1...
	@mkdir -p build ||:
	@gcc -o build/tsock_v1.o -c tsock_v1.c -Wall ||:

clean:
	@rm -rf build ||:

erase: clean
	@rm -rf bin ||:
	@echo Répertoire nettoyé.