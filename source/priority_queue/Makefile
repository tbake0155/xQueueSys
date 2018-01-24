all: xqueuesys

xqueuesys: xqueuesys.o xqueue.o process_queue.o process.o
	g++ -o bin/xqueuesys obj/xqueuesys.o obj/xqueue.o obj/process_queue.o obj/process.o -pthread `pkg-config --libs gtk+-2.0`

xqueuesys.o: src/xqueuesys.cpp
	g++ -c -g src/xqueuesys.cpp -std=c++11 -o obj/xqueuesys.o -lpthread `pkg-config --cflags gtk+-2.0`
	
	
xqueue.o: src/xqueue.cpp
	g++ -c -g src/xqueue.cpp -std=c++11 -o obj/xqueue.o 

process_queue.o: src/process_queue.cpp
	g++ -c -g src/process_queue.cpp -std=c++11 -o obj/process_queue.o
				
process.o: src/process.cpp
	g++ -c -g src/process.cpp -std=c++11 -o obj/process.o

clean:
	rm obj/*
