all:
	g++ alpha_blending.cpp main.cpp -O3 -g -o alpha_blending -lsfml-graphics

profile:
	valgrind --tool=callgrind ./alpha_blending
	gprof2dot -f callgrind callgrind.out.24572 | dot -Tsvg -o Images/test0_1graph.svg