all:
	g++ alpha_blending.cpp main.cpp -O3 -g -o alpha_blending -lsfml-graphics

profile:
	#valgrind --tool=callgrind ./alpha_blending
	 gprof2dot -f callgrind callgrind.out.49144 | dot -Tsvg -o Images/test2_graph.svg
	 gprof2dot -f callgrind callgrind.out.49225 | dot -Tsvg  -o Images/test2_1graph.svg