Version 1:
Basic realization without error detect.

Version 2:
Basic realization with error detect. And it uses string to check the input.

Version 3:
I add a time counter, but there is something wrong with the time.

Version 4:
After checking my code, I solved the time problem. But the program is slow.
Calculating vectors of 200000 elements need more than 5 seconds.
So the 200000000 may need 5000 seconds or longer.
By the way, I change the error status and reset the error input with 0.

Version 5:
In this version, I use the binary input and output, it reduce the total time to 119s(almost 42 times faster).
But in this way, I can't find out whether the input is legal or not.

Warning: The old version codes doesn't release the memory!

Version 6:
Ignoring the IO time, it need 383ms to calculate for two vectors each with 100M elements.

Version 7:
By using the multithreading, the calculate time is reduced to almost 284ms for 200M elements.
But at the first time, I chose the atomic variable and it was very slow. 
