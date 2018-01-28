all: xqueuesys

xqueuesys: xqueuesys.o process_queue.o process.o
	g++ -o bin/xqueuesys obj/xqueuesys.o obj/process_queue.o obj/process.o -pthread -lX11 `pkg-config --libs gtk+-2.0`

xqueuesys.o: src/xqueuesys.cpp
	g++ -c -g src/xqueuesys.cpp -std=c++11 -o obj/xqueuesys.o `pkg-config --cflags gtk+-2.0`

process_queue.o: src/process_queue.cpp
	g++ -c -g src/process_queue.cpp -std=c++11 -o obj/process_queue.o `pkg-config --cflags gtk+-2.0`
				
process.o: src/process.cpp
	g++ -c -g src/process.cpp -std=c++11 -o obj/process.o

clean:
	rm obj/*
