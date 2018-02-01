# install the package to a folder in the current directory
install: setup
	cp  src/process_tracker/bin/* bin/process_tracker/
	cp  src/priority_queue/bin/* bin/
	cp  src/processes/bin/* bin/processes/

# install the package with built-in processes
install_no_processes: setup-np no_processes
	cp -r src/process_tracker/bin/ bin/
	cp -r src/priority_queue/bin/ bin/

# delete the installation package, if still local to the make file
uninstall:
	rm -r bin/

# build the entire package
all: xqueuesys process_tracker processes

# do not build the provided processes
no_processes: xqueuesys process_tracker 

# create necessary folder heirarchy for install.
setup:
	rm -r bin/*
	mkdir -p bin/processes
	mkdir -p bin/process_tracker
	
setup-np:
	rm -r bin/*
	mkdir -p bin/process_tracker

# xqueuesys
xqueuesys: xqueuesys.o process_queue.o process.o
	g++ -o src/priority_queue/bin/xqueuesys src/priority_queue/obj/xqueuesys.o src/priority_queue/obj/process_queue.o src/priority_queue/obj/process.o -pthread -lX11 `pkg-config --libs gtk+-2.0`

xqueuesys.o: src/priority_queue/src/xqueuesys.cpp
	g++ -c -g src/priority_queue/src/xqueuesys.cpp -std=c++11 -o src/priority_queue/obj/xqueuesys.o `pkg-config --cflags gtk+-2.0`

process_queue.o: src/priority_queue/src/process_queue.cpp
	g++ -c -g src/priority_queue/src/process_queue.cpp -std=c++11 -o src/priority_queue/obj/process_queue.o `pkg-config --cflags gtk+-2.0`
				
process.o: src/priority_queue/src/process.cpp
	g++ -c -g src/priority_queue/src/process.cpp -std=c++11 -o src/priority_queue/obj/process.o 

# process tracker
process_tracker: process_tracker.o
	g++ -o src/process_tracker/bin/process_tracker src/process_tracker/obj/process_tracker.o -pthread -lX11
	
process_tracker.o: src/process_tracker/src/process_tracker.cpp
	g++ -c -g src/process_tracker/src/process_tracker.cpp -std=c++11 -o src/process_tracker/obj/process_tracker.o
	
# included executables
processes: recho crypto n_countdown n_factorial n_fibonacci ascii_image

recho: recho.o
	g++ -o src/processes/bin/recho src/processes/obj/recho.o
	
recho.o: src/processes/src/recho.cpp
	g++ -c -g src/processes/src/recho.cpp -std=c++11 -o src/processes/obj/recho.o
	
crypto: crypto.o
	g++ -o src/processes/bin/crypto src/processes/obj/crypto.o

crypto.o: src/processes/src/crypto.cpp	
	g++ -c -g src/processes/src/crypto.cpp -std=c++11 -o src/processes/obj/crypto.o
	
n_countdown: n_countdown.o
	g++ -o src/processes/bin/n_countdown src/processes/obj/n_countdown.o -pthread -lX11 `pkg-config --libs gtk+-2.0`

n_countdown.o: src/processes/src/n_countdown.cpp	
	g++ -c -g src/processes/src/n_countdown.cpp -std=c++11 -o src/processes/obj/n_countdown.o `pkg-config --cflags gtk+-2.0`
		
n_factorial: n_factorial.o
	g++ -o src/processes/bin/n_factorial src/processes/obj/n_factorial.o -pthread -lX11 `pkg-config --libs gtk+-2.0`

n_factorial.o: src/processes/src/n_factorial.cpp	
	g++ -c -g src/processes/src/n_factorial.cpp -std=c++11 -o src/processes/obj/n_factorial.o `pkg-config --cflags gtk+-2.0`
	
n_fibonacci: n_fibonacci.o
	g++ -o src/processes/bin/n_fibonacci src/processes/obj/n_fibonacci.o -pthread

n_fibonacci.o: src/processes/src/n_fibonacci.cpp	
	g++ -c -g src/processes/src/n_fibonacci.cpp -std=c++11 -o src/processes/obj/n_fibonacci.o 
	
ascii_image: ascii_image.o
	g++ -o src/processes/bin/ascii_image src/processes/obj/ascii_image.o

ascii_image.o: src/processes/src/ascii_image.cpp	
	g++ -c -g src/processes/src/ascii_image.cpp -std=c++11 -o src/processes/obj/ascii_image.o 
	
# clean up the build files after install	
clean:
	rm src/process_tracker/obj/*
	rm src/process_tracker/bin/*
	rm src/priority_queue/obj/*
	rm src/priority_queue/bin/*
	rm src/processes/obj/*
	rm src/processes/bin/*
	
