# balloc (big alloc cuz balls)
i recently saw a video of sphaerophoria where they talked about thei allocator sphalloc and i thought:
"well that's a bit overcomplicated", so i made my own.

this allocator is basically an arena allocator, with the added benefit of being able to free your
allocations and that it automatically grows in size.

## quickstart
```
clang -o nob nob.c
./nob
```

this will build the object file & the tests, to run the tests, simply run
```
./nob test
```
(tests will be expanded)
