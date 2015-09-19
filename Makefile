CC= gcc
BUILD = ./build
CFLAGS=-W -Wall -ansi -pedantic
EXEC_NAME = run
TESTS= ./tests


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


#compile tests files
tests: list_test
	#Generate OBJECT for tests end
	

list_test: list 
	#Generate OBJECT for tests list
	gcc -c $(TESTS)/list_test.c -o $(TESTS)/list_test.o 
	mv $(TESTS)/*.o $(BUILD)/
	gcc $(BUILD)/list_test.o $(BUILD)/list.o -o $(BUILD)/list_test



clean: 
	#Clean all files
	rm -r $(BUILD)/*

run:
	#Exec 
	$(BUILD)/$(EXEC_NAME)

run_tests:
	#Exec list_test
	$(BUILD)/list_test



