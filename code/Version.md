Version 1:
Basic realization with error detect. It will reset the error input to 0.
(Using string to check)

Warning: This version codes doesn't release the memory!

Version 2:
The IO time is too large that I can't get the result.
Including the IO time, calculating vectors of 200000 elements need more than 5 seconds.
So the 200000000 may need 5000 seconds or longer.

Warning: This version codes doesn't release the memory!

Version 3:
In this version, I use the binary input and output, it greatly reduces the IO time to 118s(almost 42 times faster).
Just for calculating, it need 650(+-30)ms to calculate for two vectors each with 200M elements.
And I have changed the error detecting way. 

Version 4:
By using the multithreading, the calculate time is reduced to almost 500(+-50)ms for 200M elements.
But at the first time, I chose the atomic variable and it was slower. 
