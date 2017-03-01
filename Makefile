BUILD = ./build
CFLAGS=-W -Wall -ansi -pedantic
EXEC_NAME = run
TESTS= ./tests


all: logs main server thread list IO config thread_methods signal_handler
	#LINING PHASE
	gcc $(BUILD)/*.o -o $(BUILD)/$(EXEC_NAME) -pthread $(CFLAGS)
	#BUILD IS OVER	

main : 
	#GENERATE OBJECT FOR 'MAIN'
	gcc -c ./src/main.c -o  $(BUILD)/main.o  $(CFLAGS)
	
SRC_IO=$(wildcard ./src//IO/*.c)
IO: $(SRC_IO)
	#GENERATE OBJECT FOR 'IO'
	gcc -c  $^ $(CFLAGS)
	mv *.o $(BUILD)/


SRC_SERVER=$(wildcard ./src//server/*.c)
server: $(SRC_SERVER)
	#GENERATE OBJECT FOR 'SERVER'
	gcc -c  $^ $(CFLAGS) -D_BSD_SOURCE
	mv *.o $(BUILD)/

SRC_THREAD=$(wildcard ./src//thread/*.c)
thread: $(SRC_THREAD)
	#GENERATE OBJECT FOR 'THREAD'
	gcc -c  $^ $(CFLAGS) -D_GNU_SOURCE
	mv *.o $(BUILD)/

SRC_THREAD_METHODS=$(wildcard ./src//thread/threadMethods/*.c)
thread_methods: $(SRC_THREAD_METHODS)
	#GENERATE OBJECT FOR 'THREAD METHODS'
	gcc -c  $^ $(CFLAGS) -D_GNU_SOURCE
	mv *.o $(BUILD)/


SRC_LIST=$(wildcard ./src//list/*.c)
list: $(SRC_LIST)
	#GENERATE OBJECT FOR 'LIST'
	gcc -c  $^ $(CFLAGS)
	mv *.o $(BUILD)/

SRC_LOGS=$(wildcard ./src//logs/*.c)
logs: $(SRC_LOGS)
	#GENERATE OBJECT FOR 'LOGS'
	gcc -c  $^ $(CFLAGS)
	mv *.o $(BUILD)/

SRC_CONFIG=$(wildcard ./src//config/*.c)
config: $(SRC_CONFIG)
	#GENERATE OBJECT FOR 'CONFIG'
	gcc -c  $^ $(CFLAGS)
	mv *.o $(BUILD)/


SRC_SIGNAL_HANDLER=$(wildcard ./src//signal_handler/*.c)
signal_handler: $(SRC_SIGNAL_HANDLER)
	#GENERATE OBJECT FOR 'SIGNAL_HANDLER'
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



