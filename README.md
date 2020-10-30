# OpenMXM

a optimized matrices multiplication

## Part One

### struct matrix

```c++
struct matrix {
    int row;
    int column;
    float *elements;

    matrix(int a, int b) {
        row = a;
        column = b;
        elements = new float[a * b]{};
    }
};
```
Struct matrix has three member variables, row, column and elements with an initializing function. Here in every matrix we use one dimensional float array to store two dimensional matrix.

### compatibility demonstration

#### one run, multiple try

During one run, there can be multiple input. In the end of each calculation, you can print "YES" to continue or print "NO" to exit.

![multiple_try](./pics/multipletry.png)

#### robust program

This program is robust and can detect whether your input is correct. If not, it won't crash but jump to the next loop and wait for you to input again.

##### matrix size mismatch

![robust](./pics/robust.png)

##### input value mismatch

![mismatch](./pics/mismatch.png)