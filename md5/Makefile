all: new.c 
	gcc new.c -lssl -o mdsum
check: mdsum
	./mdsum /usr/share/dict/words/