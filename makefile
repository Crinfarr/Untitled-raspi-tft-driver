default: main

init:
	mkdir -p obj bin
main: main.o fbcanvas.o
	g++ -Wall -g -o bin/main obj/main.o obj/fbcanvas.o -lc

test: fbcanvas.o test.o
	g++ -Wall -g -o bin/test obj/test.o obj/fbcanvas.o -lc

main.o: src/main.cpp src/main.hpp 
	g++ -Wall -g -c src/main.cpp -o obj/main.o

test.o: src/test.cpp
	g++ -Wall -g -c src/test.cpp -o obj/test.o

fbcanvas.o: lib/fbcanvas.cpp lib/fbcanvas.hpp
	g++ -Wall -g -c lib/fbcanvas.cpp -o obj/fbcanvas.o