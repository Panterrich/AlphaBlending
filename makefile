all:
	g++ alpha_blending.cpp main.cpp -O3 -g -o alpha_blending -lsfml-graphics

profile:
	#valgrind --tool=callgrind ./alpha_blending
	gprof2dot -f callgrind callgrind.out.45435 | dot -Tsvg -o Images/test0_graph.svg
	gprof2dot -f callgrind callgrind.out.45604 | dot -Tsvg -o Images/test0_1graph.svg