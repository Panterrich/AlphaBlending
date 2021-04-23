all:
	g++ alpha_blending.cpp main.cpp -O3 -g -o alpha_blending -lsfml-graphics

profile:
	#valgrind --tool=callgrind ./alpha_blending
	gprof2dot -f callgrind callgrind.out.47415 | dot -Tsvg -o Images/test1_graph.svg
	gprof2dot -f callgrind callgrind.out.47742 | dot -Tsvg -o Images/test1_1graph.svg