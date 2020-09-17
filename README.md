This repository demonstrates performance differences between different implementations of a simple interpolation algorithm.

Clone the repository with the version of GSL which is included as a submodule:

```bash
git clone --recursive https://github.com/Shachlan/DataOrientedDemo.git
```

Compile the program:

```bash
make debug    # debug build
# or
make check    # optimized build
```

In order to run the program, call:

```bash
./check <number of models> <average number of animations per model> <number of repetitions>
```

The program will create the models, interpolate them and verify that each implementation reached the same values, and then print the time each implementation took to complete.

PRs are welcome!
