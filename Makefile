CC= gcc
BUILD = ./build
CFLAGS=-W -Wall -ansi -pedantic
EXEC_NAME = run


all: main IO server thread list
	#Linking phase
	gcc $(BUILD)/*.o -o $(BUILD)/$(EXEC_NAME) -pthread
	
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

SRC_THREAD=$(wildcard ./src//thread/*.c)
thread: $(SRC_THREAD)
	#Generate OBJECT for thread
	gcc -c  $^ 
	mv *.o $(BUILD)/

SRC_LIST=$(wildcard ./src//list/*.c)
list: $(SRC_LIST)
	#Generate OBJECT for list
	gcc -c  $^ 
	mv *.o $(BUILD)/



clean: 
	#Clean all files
	rm -r $(BUILD)/*

run:
	#Exec 
	$(BUILD)/$(EXEC_NAME)





