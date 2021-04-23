# Alpha blending

## Table of contents

[Main page](https://github.com/Panterrich/Alpha_blending)

[№1 optimization - reduce overhead costs](https://github.com/Panterrich/Alpha_blending/tree/ver_1)

[№2 optimization - getting rid of divisions](https://github.com/Panterrich/Alpha_blending/tree/ver_2)

[№3 optimization - SSE optinization](https://github.com/Panterrich/Alpha_blending/tree/ver_3)
## First simple version without optimizations.

So this is the simplest version of the program that performs alpha blending.

Example of the program result:
![alt text](Images/output.png "The funny picture")

Now let's run the tests. Repeat alpha blending 100 times. (Read from files 1 time, but don't write to files)

# With -O0 
```makefile
g++ alpha_blending.cpp main.cpp -O0 -g -o alpha_blending -lsfml-graphics 
```

![alt text](Images/test_0(0).png "The hottest function")
![alt text](Images/test_0(1).png "Important thing")
![alt text](Images/test0_graph.svg "Graph profile")

# With -O3

```makefile
g++ alpha_blending.cpp main.cpp -O3 -g -o alpha_blending -lsfml-graphics 
```

![alt text](Images/test_0(2).png "The hottest function")
![alt text](Images/test_0(3).png "Important thing")
![alt text](Images/test0_1graph.svg "Graph profile")