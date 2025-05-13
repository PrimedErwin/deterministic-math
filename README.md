## What is this lib
This is a experimental math lib based on [musl libc](https://musl.libc.org/), aiming at the determinism on all platforms. Different from musl libc, there are no code for a specific platform(like asm instructions). 

## Changelog
### [Origin musl libc](https://github.com/PrimedErwin/deterministic-math/commit/a5c1df1e2ae5a744c28a7bc4167d0b90ceec297e): the original musl libc.
### [Keepping math only](https://github.com/PrimedErwin/deterministic-math/commit/00146e092a89ddc9d3afb56438dee311981978af): deleted most of the code.
Deleted ./arch: code for different platforms, file like `fp_arch.h` and `float.h` defines behavior for specific platforms. 
Deleted ./compat, ./crt, ./dist, ./ldso, ./tools: not related with math. 

Modified ./include: only kept `float.h, math.h, stdint.h`, which are related to math. 

Modified ./src: only kept folders related by `math.h`. `./src/include/features.h` is included by `math.h`, kept. `./src/internal/libm.h` is included by many math functions, kept. `./src/math`, kept. 

!! Deleted ./src/math/(some platform) folders: some functions (especially sqrt) have the corresponding assembly instruction on different platforms. These folders are deleted to make sure that all the functions are implemented by ourselves.
### [Gather files](https://github.com/PrimedErwin/deterministic-math/commit/afa45a78c17b8a86d1a86f90bff9920d93849d34): put files together. 
After deletion, I put the rest files like this:
```
./include
    | -- features.h
    | -- float.h
    | -- libm.h
    | -- math.h
    | -- stdint.h
./src
    | -- math
           | -- math function files
```
### [Integrate math.h](https://github.com/PrimedErwin/deterministic-math/commit/1f3874a66037aa904484768fde94a3ef943114a1): integrate include files into math.h
Deleted `features.h`: platform feature defines.

Deleted `float.h, libm.h, stdint.h`.

Modified `math.h`: paste code from `float.h, libm.h, stdint.h`.
### [Modified ./src/math](https://github.com/PrimedErwin/deterministic-math/commit/98724ef2ca8a03c80a0afd570c4b217fe95fb210): changes, deletions of math functions
Deletion: These functions for calculation are kept. input and output are `double`.
```
acos, asin, atan, atan2, ceil, cos, exp, fabs, floor, fmod, 
log, log10, log2, modf, pow, scalbn, sin, sqrt, tan, trunc
```
Internal functions like `__cos.c`, error handling functions like `__math_invalid.c` are kept.

Addition: functions for degree computation, reduction, factorial, gcd. 
```
double degrees(double);
int    factorial(int);
double fsum(double*, int);
int    gcd(int, int);
double radians(double);
```

Modification: all files' include headers are changed. 
Files like `cos.c` including `libm.h` are changed to `math.h`.
Files like `__fpclassify.c` including `math.h, stdint.h` are changed to `math.h`.

## Test
Simple tests with `determinism_test.c`. Tested on Windows11, 22H2, x64_64, AMD Ryzen Threadripper 3990X. 

**Cumulative error** is found in the test. A small number equal to DBL_EPSILON is produced during the computation. 
For example, sqrt(2), the result of pow(sqrt(2), 2) is 2.0+2*DBL_EPSILON. The same phenomenon is found on the following compilers. 
### Clang 20.1.4
No problem.
### GNU 14.2.0
No problem.
### MSVC 19.29.30154
/fp:strict will get C2099 and C2177, /fp:precise will get C2177.

C2099: defines should be constant, #ifdef .. #define VALUE 10 #elif .. is not allowed.
C2177: INFINITY in this repo is 1e5000f, which is too big, this is not allowed.
Try other values to replace INFINITY in test case to make the test run.
