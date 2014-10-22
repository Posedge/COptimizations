## COptimizations

Some timing benchmarks of a few C99 codes which I come across throughout my Systems Programming and Computer Architecture course at the university.

### Nested vs Multilevel Arrays
multi-dimensional arrays in C can be nested (basically converting them to a longer one-dimensional array,
and having the data stored consecutively in memory with indexing offsets)
or they can be java-like arrays of arrays, meaning an array which contains pointers (arrays).
The latter should, in theory, be a lot slower. Accessing an element in a nested array requires only a single memory load/store,
in addition there should be optimizations in the processor design which allow caching of elements likely to be loaded, when traversing a two-dimensional array in any direction.
A two-dimensional multilevel-array on the other hand requires two memory loads every time.
A third way is to store everything in a regular dynamically allocated array, and offset column indizes by row length * row index. This should be a little slower than nested
arrays, as the compiler cannot optimize the index and has to perform a regular multiplication every time.
With this code you can compare the speed of the three methods. It also heavily depends on the optimization level.
