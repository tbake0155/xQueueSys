all: echo crypto n_countdown n_factorial n_fibonacci ascii_image

echo: echo.o
	g++ -o bin/echo obj/echo.o
	
echo.o: src/echo.cpp
	g++ -c -g src/echo.cpp -std=c++11 -o obj/echo.o
	
crypto: crypto.o
	g++ -o bin/crypto obj/crypto.o

crypto.o: src/crypto.cpp	
	g++ -c -g src/crypto.cpp -std=c++11 -o obj/crypto.o
	
n_countdown: n_countdown.o
	g++ -o bin/n_countdown obj/n_countdown.o

n_countdown.o: src/n_countdown.cpp	
	g++ -c -g src/n_countdown.cpp -std=c++11 -o obj/n_countdown.o
		
n_factorial: n_factorial.o
	g++ -o bin/n_factorial obj/n_factorial.o -pthread

n_factorial.o: src/n_factorial.cpp	
	g++ -c -g src/n_factorial.cpp -std=c++11 -o obj/n_factorial.o -lpthread
	
n_fibonacci: n_fibonacci.o
	g++ -o bin/n_fibonacci obj/n_fibonacci.o -pthread

n_fibonacci.o: src/n_fibonacci.cpp	
	g++ -c -g src/n_fibonacci.cpp -std=c++11 -o obj/n_fibonacci.o -lpthread
	
ascii_image: ascii_image.o
	g++ -o bin/ascii_image obj/ascii_image.o -pthread

ascii_image.o: src/ascii_image.cpp	
	g++ -c -g src/ascii_image.cpp -std=c++11 -o obj/ascii_image.o -lpthread
	
clean:
	rm obj/*.o

