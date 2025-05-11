# Latin Hypercube Samples
A C++ header-only library reimplementing R's [lhs](https://github.com/bertcarnell/lhs/tree/master) package. The library is very much work in progress and currently only supports [random](lhs/include/visus/lhs/random.h) (derived from [R package]([[https://github.com/bertcarnell/lhs/blob/master/src/randomLHS.cpp](https://github.com/bertcarnell/lhs/blob/4be72495c0eba3ce0b1ae602122871ec83421db6/src/randomLHS.cpp)](https://github.com/bertcarnell/lhs/blob/4be72495c0eba3ce0b1ae602122871ec83421db6/src/randomLHS.cpp))), [maximin](lhs/include/visus/lhs/maximin.h) (derived from [construction](https://github.com/bertcarnell/lhs/blob/master/src/maximinLHS.cpp) and [optimisation](https://github.com/bertcarnell/lhs/blob/4be72495c0eba3ce0b1ae602122871ec83421db6/R/maximinLHS.R) code in the R package) and [centred](lhs/include/visus/lhs/centred.h) (derived from [Rust implementation](https://github.com/relf/egobox/blob/15a1225454f4d1c06df2301b9b5b69a9c900c788/crates/doe/src/lhs.rs#L253-L267)) samples. Additional implementations might be ported as necessary, but do not hold your breath.

## Building
The library is header-only, so you only need to copy the [include](lhs/include/visus/lhs) folder and add it to you `#include` path. For Cmake builds, we have added [CMakeLists.txt](lhs/CMakeLists.txt), which does this for you.

## Usage
