make:
	g++ *.cpp -o a -pthread -Ofast -march=native
	sudo ./a

compile:
	g++ *.cpp -o a -pthread -Ofast -march=native

run:
	sudo ./a

regular:
	g++ *.cpp -o a
	sudo ./a

native:
	g++ *.cpp -o a -march=native
	sudo ./a

fast:
	g++ *.cpp -o a -Ofast
	sudo ./a
