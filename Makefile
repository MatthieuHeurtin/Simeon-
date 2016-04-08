CC= gcc
BUILD = ./build
CFLAGS=-W -Wall -ansi -pedantic
EXEC_NAME = run
TESTS= ./tests


all: logs main server thread list IO config
	#Linking phase
	gcc $(BUILD)/*.o -o $(BUILD)/$(EXEC_NAME) -pthread $(CFLAGS)
	#Build is over	

main : 
	#Generate OBJECT for Main
	gcc -c ./src/main.c -o  $(BUILD)/main.o  $(CFLAGS)
	
SRC_IO=$(wildcard ./src//IO/*.c)
IO: $(SRC_IO)
	#Generate OBJECT for IO
	gcc -c  $^ $(CFLAGS)
	mv *.o $(BUILD)/


SRC_SERVER=$(wildcard ./src//server/*.c)
server: $(SRC_SERVER)
	#Generate OBJECT for server
	gcc -c  $^ $(CFLAGS) -D_BSD_SOURCE
	mv *.o $(BUILD)/

SRC_THREAD=$(wildcard ./src//thread/*.c)
thread: $(SRC_THREAD)
	#Generate OBJECT for thread
	gcc -c  $^ $(CFLAGS) -D_GNU_SOURCE
	mv *.o $(BUILD)/

SRC_LIST=$(wildcard ./src//list/*.c)
list: $(SRC_LIST)
	#Generate OBJECT for list
	gcc -c  $^ $(CFLAGS)
	mv *.o $(BUILD)/

SRC_LOGS=$(wildcard ./src//logs/*.c)
logs: $(SRC_LOGS)
	#Generate OBJECT for logs
	gcc -c  $^ $(CFLAGS)
	mv *.o $(BUILD)/

SRC_CONFIG=$(wildcard ./src//config/*.c)
config: $(SRC_CONFIG)
	#Generate OBJECT for config
	gcc -c  $^ $(CFLAGS)
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



