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
