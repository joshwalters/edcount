# `edcount`

Estimate distinct count of values from standard input.

`edcount` provides a very fast way to perform unique count estimates on the
command line.

## Examples

Counting 10 million unique records:

Using `sort` and `wc`:
```
$ seq 1 10000000 | shuf | sort -u | wc -l
10000000

$ time $(seq 1 10000000 | shuf | sort -u | wc -l > /dev/null)
real	0m46.034s
user	0m45.928s
sys	0m1.040s
```

Using `edcount`:
```
$ seq 1 10000000 | shuf | edcount
Unique Estimate: 10003339

$ time $(seq 1 10000000 | shuf | edcount > /dev/null)
real	0m5.713s
user	0m6.940s
sys	0m0.432s
```

## Compiling

### Requirements

`cmake`, `make`, `gcc`

### Building

Run `make`

## License

`edcount` is licensed under GPLv3. See the `LICENSE` file for more information.
