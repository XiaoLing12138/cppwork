Version 1:
Basic realization with error detect. It will reset the error input to 0.
(Using string to check)
The IO time is too large that I can't get the result.
Including the IO time, calculating vectors of 200000 elements need more than 5 seconds.
So the 200000000 may need 5000 seconds or longer.

Warning: This version codes doesn't release the memory!

Version 2:
In this version, I use the binary input and output, it greatly reduces the IO time to 118s(almost 42 times faster).
Just for calculating, it need 650(+-30)ms to calculate for two vectors each with 200M elements.
And I have changed the error detecting way. 

Version 3:
By using the multithreading, the calculate time is reduced to almost 500(+-50)ms for 200M elements.
But at the first time, I chose the atomic variable and it was slower. 

Version 4:
Comparing with openBlas' cblas_sdot(), my calculating time is twice as much as it.
Thinking about the accuracy, I decide to use double type.(Since my result is different withe cblas's)

And after I turn the variable type of result from float to double, the calculating time is almost the same.
(Sometimes my program will be fast, sometimes my program will be slower.) 

Version 5:
Using cuda to calculate, but it needs more time.

version 6:
Using the code from "GPU高性能编程CUDA实战", it only needs 36us for two vectors of 200000000 elements.
That proves my last code didn't tap its potential somehow.