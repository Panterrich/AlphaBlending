# Alpha blending

Example of the program result:
![alt text](Images/output.png "The funny picture")
## Table of contents

[Main page](https://github.com/Panterrich/Alpha_blending)

[№0 optimization - the starting tests](https://github.com/Panterrich/Alpha_blending/tree/ver_0)

[№1 optimization - reduce overhead costs](https://github.com/Panterrich/Alpha_blending/tree/ver_1)

[№2 optimization - getting rid of divisions](https://github.com/Panterrich/Alpha_blending/tree/ver_2)

[№3 optimization - SSE optinization](https://github.com/Panterrich/Alpha_blending/tree/ver_3)

# Best results 

* Without optimizations (-O0), the program sped up compared to the base version by 104% (there were 26,3 billion instructions, now - 12,9 billion). Unfortunately the compiler was not able to optimize SSE with such optimization keys

* With optimization (-O3), it sped up by 560% (there were 15,9 billion instructions, now - 2,4 billion). But here SSE gave a significant optimization
