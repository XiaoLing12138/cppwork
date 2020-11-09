Version1:
In this version, I implement the normal functions like:
1. A struct for Matrix
2. Making the calculating strong and returning error for the matrix doesn't match
3. Calculating the time

But in the case of two matrixes with 10^6 elements(200*5000 and 5000*200), it needs 850ms+-.
With 200M(10^8 elements for each), 2000*50000 and 50000*2000, it needs almost 850s+-.
So we will focus on how to reduce the calculating time.

Version2: