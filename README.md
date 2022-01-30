# ZC [![ZC CI](https://github.com/pseudocc/zc/actions/workflows/zc.yml/badge.svg)](https://github.com/pseudocc/zc/actions/workflows/zc.yml)

C library for collections that supports generic types.

In C++ we can use the `std::vector` or other template containers that are pretty helpful,
while in C we don't have those, and that's how this repository came into being.

## Vector

I am not only a big fan of C but JavaScript as well,
so some of the member functions of `zvec_t` are inspired by `Array.prototype`,
like: `shift` and `unshift`.

Example usages are simple, but you might need to suppress some warnings, like `-Wint-convertion` for gcc.

```c
zvec_t ivec = zvec_new(sizeof(int));  // []
zvec_push(ivec, (int)29);             // [29]
zvec_unshift(ivec, (int)11);          // [11,29]
```

|Name|Status|
|:---|-----:|
|Declaration|Done|
|Implementaion|Partial|
|Test|Done|
|Man Pages|In Progress|

## Build

GNU Makefile.

```bash
make
```

### Installation

**TODO:**
Not even started.

## Test

Run all unit tests after the build.
```
./ztest
```

**TODO:**
command line arguments to run specific category and case.

## Documentation

See manual pages under `man/`
