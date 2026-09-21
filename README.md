# advent_of_code_24

The Annual Advent of Code, this one is for 2024.

## Building

Visual Studio is still the primary way to work on this — open `AoC_2024.sln`
and go. A `CMakeLists.txt` sits alongside it so the same sources build with
gcc/clang, which is what CI uses and what lets the parent
[Advent_of_Code](https://github.com/JamieDStewart/Advent_of_Code) repository
build and test every year in one pass.

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

The binary lands at `build/bin/aoc_2024`.

## Running

```
aoc_2024 [options]

  --day N        Run only day N. May be repeated. Default: every day.
  --format FMT   'table' (default, human readable) or 'json'.
  --list         Print the days this build knows about as JSON, then exit.
  --help         Show usage.
```

Each day reads its puzzle input from `./input/day_NN.txt`, relative to the
working directory, so run the binary from a directory that has an `input`
folder next to it.

## Puzzle input

Real puzzle inputs are **not** committed — `.gitignore` excludes `input/`,
which is what Advent of Code asks of us. Drop your own inputs into `input/`.

`sample/` holds the worked examples from the puzzle text, and those *are*
committed. Point `input/` at them to get a deterministic run that needs no
private data:

```sh
mkdir -p run && ln -s ../sample run/input
(cd run && ../build/bin/aoc_2024)
```

`aoc-year.json` records the expected sample answers for each day. The test
runner in the parent repository reads that file to verify this year.
