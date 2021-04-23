all:
	g++ alpha_blending.cpp main.cpp -O3 -msse4.2 -mavx2 -march=native -g -o alpha_blending -lsfml-graphics

profile:
	#valgrind --tool=callgrind ./alpha_blending
	 gprof2dot -f callgrind callgrind.out.42711 | dot -Tsvg -o Images/test3_graph.svg
	 gprof2dot -f callgrind callgrind.out.42896 | dot -Tsvg  -o Images/test3_1graph.svg