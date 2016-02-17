make:
	g++ *.cpp -o a -pthread -Ofast -march=native
	sudo ./a

compile:
	g++ *.cpp -o a -pthread -Ofast -march=native

run:
	sudo ./a