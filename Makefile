CC= gcc
BUILD = ./build
CFLAGS=-W -Wall -ansi -pedantic
EXEC_NAME = run


all: main IO server
	#Linking phase
	gcc $(BUILD)/*.o -o $(BUILD)/$(EXEC_NAME)
	
main : 
	#Generate OBJECT for Main
	gcc -c ./src/main.c -o  $(BUILD)/main.o  

SRC_IO=$(wildcard ./src//IO/*.c)
IO: $(SRC_IO)
	#Generate OBJECT for IO
	gcc -c  $^ 
	mv *.o $(BUILD)/


SRC_SERVER=$(wildcard ./src//server/*.c)
server: $(SRC_SERVER)
	#Generate OBJECT for server
	gcc -c  $^ 
	mv *.o $(BUILD)/




clean: 
	#Clean all files
	rm -r $(BUILD)/*

run:
	#Exec 
	$(BUILD)/$(EXEC_NAME)





