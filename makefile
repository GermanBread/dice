all:
	g++ *.cpp -O3 -o dice

static:
	g++ *.cpp -static -O3 -o dice

run:
	make
	@clear
	@./a.out 2