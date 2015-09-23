# Simeon-
The main purpose of Simeon is to be able to run a Graphic software (such as firefox, gedit, etc...) on a remote computer, because it is not possible with ssh.

CONTENT
	./src/*
	The source code of Simeon
	./init
	The file to control Simeon as a Demon
		

INSTALL
./configure

COMPILE 
make

EXECUTE 
'make run' or './build/run' then use telnet 'telnelt [IP] [PORT]'
example: telnet 127.0.0.1 8888
