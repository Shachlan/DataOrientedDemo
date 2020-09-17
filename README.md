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

For simplicity's sake, there's also the ability to use docker to run the demo:

```bash
make run-debug MODELS=<number of models> ANIMATIONS=<average number of animations per model> REPETITIONS=<number of repetitions>
```

or

```bash
make run-check MODELS=<number of models> ANIMATIONS=<average number of animations per model> REPETITIONS=<number of repetitions>
```

for example:

```bash
make run-check MODELS=5 ANIMATIONS=20 REPETITIONS=100
```

The program will create the models, interpolate them and verify that each implementation reached the same values, and then print the time each implementation took to complete.

PRs are welcome!
