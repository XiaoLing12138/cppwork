__________________________________________
Windows 10\n
Intel i7-9750H @2.60Hz
Intel UHD Graphics 630
NVIDIA GTX 1660 Ti
__________________________________________
Version1:
In this version, I implement the normal functions like:
1. A struct for Matrix
2. Making the calculating strong and returning error for the matrix doesn't match
3. Calculating the time

But in the case of two matrixes with 10^6 elements(200*5000 and 5000*200), it needs 850ms+-.
With 200M(10^8 elements for each), 2000*50000 and 50000*2000, it needs almost 850s+-.
So we will focus on how to reduce the calculating time.

------------------------------------------------------------------------------------------------------

Version2:
In this version, I use the multithreading with 10 threads.
And compared with openBlas.

Matrix                        My Time(x86 & x64)       OpenBlas Time(x64)
200*50000 and 50000*200            4.0s+-                   66ms+-
2000*50000 and 50000*2000          747s+-                   3.9s+-
My program is much more slower.

------------------------------------------------------------------------------------------------------

version3:  !!!WARNING -> version5

As we all know, CUDA is a platform published by NVIDIA, and it can use GPU to solve the 
complex computational problems. Thus, I decide to use CUDA to do the calculation.
Matrix                              Calculating Time(x64)      Writing Memory Time(x64)
2000*50000 and 50000*2000                50us+-                  16s+-(shift to 7s+-)

(Reference: https://blog.csdn.net/qq_38128961/article/details/100151316)

------------------------------------------------------------------------------------------------------

version4:   !!!WARNING -> version5

By using CUDA, the calculating time is mini. But I have seen a algorithm named Tile.
That sounds good.

By using the Tile algorithm, the Calculating Time is reduced to 40us+-, and the Writing Memory Time
is reduced to 7s+-. That's weird because I haven't changed the memory part.
After I roll back, the old version just need 7s+- to write memory. The reason maybe I was running other
program while testing last time. 

Matrix                              Calculating Time(x64)      Writing Memory Time(x64)
2000*50000 and 50000*2000                 40us+-                         7s+-

Running the second time                  ->2us+-
The second time is interesting. Calculation only need 2us+-. That may because of pretreatment.
And in another test, the writing memory time is 13s. It always change from time to time. 
Costing in copy back from CUDA.

(Reference: https://blog.csdn.net/qq_38128961/article/details/100151316)

------------------------------------------------------------------------------------------------------

version 5:  (Important)
First I have to mentioned that the time count in previous program is wrong, the cuda kernel will return for just the first
thread and the chrono will stop counting, that's why it only cost 40us+-. But it's wrong, we need to count time by cudaEvent!

ACTUALLY
Matrix                              Calculating Time(x64)      
2000*50000 and 50000*2000                6000ms+-                         

It seems slower than openBlas, I think it is because my kernel fuction is not as good as their optimization.
But comparing to my original, it is faster 125 times.

------------------------------------------------------------------------------------------------------

Version 6:
This time I decide to use the cuBlas, and it has completely find out the computing power of GPU.
Matrix                              Calculating Time(x64)      
2000*50000 and 50000*2000                95ms+-   