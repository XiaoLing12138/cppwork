Version1:
In this version, I implement the normal functions like:
1. A struct for Matrix
2. Making the calculating strong and returning error for the matrix doesn't match
3. Calculating the time

But in the case of two matrixes with 10^6 elements(200*5000 and 5000*200), it needs 850ms+-.
With 200M(10^8 elements for each), 2000*50000 and 50000*2000, it needs almost 850s+-.
So we will focus on how to reduce the calculating time.


Version2:
In this version, I use the multithreading with 10 threads.
And compared with openBlas.

Matrix                        My Time(x86 & x64)       OpenBlas Time(x64)
200*5000 and 5000*200              0.2s+-                  0.013s+-
200*50000 and 50000*200             13s+-                  0.078s+-
2000*50000 and 50000*2000         475s+-(?)                 4.8s+-
My program is much more slower.


version3:
As we all know, CUDA is a platform published by NVIDIA, and it can use GPU to solve the 
complex computational problems. Thus, I decide to use CUDA to do the calculation.
Matrix                              Calculating Time(x64)      Writing Memory Time(x64)
2000*50000 and 50000*2000                50us+-                  16s+-(shift to 7s+-)

(Reference: https://blog.csdn.net/qq_38128961/article/details/100151316)


version4:
By using CUDA, the calculating time is mini. But I have seen a algorithm named Tile.
That sounds good.

By using the Tile algorithm, the Calculating Time is reduced to 40us+-, and the Writing Memory Time
is reduced to 7s+-. That's weird because I haven't changed the memory part.
After I roll back, the old version just need 7s+- to write memory. The reason maybe I was running other
program while testing last time. 

Matrix                              Calculating Time(x64)      Writing Memory Time(x64)
2000*50000 and 50000*2000                 40us+-                         7s+-

(Reference: https://blog.csdn.net/qq_38128961/article/details/100151316)