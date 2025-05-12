## What is this lib
This is a experimental math lib based on [musl libc](https://musl.libc.org/), aiming at the determinism on all platforms. Different from musl libc, there are no code for a specific platform(like asm instructions). 

## Changelog
### [origin musl libc](https://github.com/PrimedErwin/deterministic-math/commit/a5c1df1e2ae5a744c28a7bc4167d0b90ceec297e): The original musl libc.
### [keepping math only](https://github.com/PrimedErwin/deterministic-math/commit/00146e092a89ddc9d3afb56438dee311981978af): Deleted most of the code.
Deleted ./arch: code for different platforms, file like `fp_arch.h` and `float.h` defines behavior for specific platforms. 
Deleted ./compat, ./crt, ./dist, ./ldso, ./tools: not related with math. 
Modified ./include: only kept `float.h, math.h, stdint.h`, which are related to math. 
Modified ./src: only kept folders related by `math.h`. `./src/include/features.h` is included by `math.h`, kept. `./src/internal/libm.h` is included by many math functions, kept. `./src/math`, kept. 
!! Deleted ./src/math/(some platform) folders: some functions (especially sqrt) have the corresponding assembly instruction on different platforms. These folders are deleted to make sure that all the functions are implemented by ourselves.