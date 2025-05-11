# Latin Hypercube Sampling
A C++ header-only library reimplementing R's [lhs](https://github.com/bertcarnell/lhs/tree/master) package. The library is very much work in progress and currently only supports [random](lhs/include/visus/lhs/random.h) (derived from [R package]([[https://github.com/bertcarnell/lhs/blob/master/src/randomLHS.cpp](https://github.com/bertcarnell/lhs/blob/4be72495c0eba3ce0b1ae602122871ec83421db6/src/randomLHS.cpp)](https://github.com/bertcarnell/lhs/blob/4be72495c0eba3ce0b1ae602122871ec83421db6/src/randomLHS.cpp))), [maximin](lhs/include/visus/lhs/maximin.h) (derived from [construction](https://github.com/bertcarnell/lhs/blob/master/src/maximinLHS.cpp) and [optimisation](https://github.com/bertcarnell/lhs/blob/4be72495c0eba3ce0b1ae602122871ec83421db6/R/maximinLHS.R) code in the R package) and [centred](lhs/include/visus/lhs/centred.h) (derived from [Rust implementation](https://github.com/relf/egobox/blob/15a1225454f4d1c06df2301b9b5b69a9c900c788/crates/doe/src/lhs.rs#L253-L267)) samples. Additional implementations might be ported as necessary, but do not hold your breath.

## Building
The library is header-only, so you only need to copy the [include](lhs/include/) folder and add it to you `#include` path. For Cmake builds, we have added [CMakeLists.txt](lhs/CMakeLists.txt), which does this for you.

## Usage
The library will create Latin hypercube samples in the form of [matrix](lhs/include/visus/lhs/matrix.h) instances. Each row of the matrices represent a single sample whereas each column represents a parameter. There are usually two types of samples, the ones yielding integer matrices and the ones yielding floating-point matrices. In case of the former, the matrix elements represent zero-based indices into the parameter ranges, whatever these may be. For instance, if a parameter is a numeric value, the index represents the selected qantile of the overall range. If you have categorical parameters, it might represent the category. The floating-point samples are typically from a unit hypercube. You may scale them as necessary.

### Create a unit hypercube sample
The following most basic code creates a four samples with three parameters on a unit hypercube:
```c++
auto lhs = visus::lhs::random<float>(4, 3);
```

You can also provide your own random number generator like this, for instance if you need to have a specific random seed:
```c++
auto lhs = visus::lhs::random<float>(4, 3, false, std::mt19937(42));
```

Finally, it is possible to specify a specific random number distribution, which should, however, typically be a `std::uniform_real_distribution` within [0, 1]. The ability to change this is used for testing and should typically not be required for end users:
```c++
auto lhs = visus::lhs::random(4, 3, false, std::mt19937(42), std::uniform_real_distribution<float>(0.0f, 1.0f));
```

A centred sample can be created like this:
```c++
auto lhs = visus::lhs::centred<float>(4, 3);
```

You can perform maximin optimisation (maximise the pairwise distance between the samples) on an existing sample:
```c++
auto lhs = visus::lhs::random<float>(4, 3);
visus::lhs::maximin(lhs);
```

### Create a discrete sample
The following most basic code creates four samples with values wihtin [0, 4[ for the three parameters:
```c++
auto lhs = visus::lhs::random<std::size_t>(4, 3);
```

### Sample your own numeric and categorical data
The library provides a [sample](lhs/include/visus/lhs/sample.h) convenience function that allows users to create samples of differently shaped parameters in the form of `std::tuple`s. It is based on scaling a unit hypercube sample to the user-defined ranges. The following code creates four samples of a categorical parameter, an range of consecutive integer values and a range of floating-point values:
```c++
auto lhs = visus::lhs::sample(
    [](const std::size_t parameters) {
        // Request four sample points. The number of columns must be 'parameters'.
        return visus::lhs::random<float>(4, parameters);
    },
    std::vector<std::string>({ "Category 1", "Category 2" }),
    visus::lhs::make_range(1, 100),
    visus::lhs::make_range(0.0f, 1.0f));
```
The first parameter is a callback that creates the unit hypercube sample. This way, it is possible for you to choose how the Latin hypercube sample is created. However, it is mandatory that the sample returned (i) is from a unit hypercube, (ii) returns a floating-point matrix and (iii) has the requested number of columns, which is equivalent to the number of parameters specified after the callback (three in the case of the example). The number of rows of the matrix returned determines the number of sample points and can be chosen freely.

## Acknowledgments
This work was partially funded by Deutsche Forschungsgemeinschaft (DFG) as part of [SFB/Transregio 161](https://www.sfbtrr161.de) (project ID 251654672).
