# cache-miss-rate-simulator

CPU cache hit/miss Rate caculator and simulator for direct mapped, n-way mapped, fully mapped in 32-bits addressing.

## Environment

Ubuntu 18.04 LTS

## Usage

1. Clone from repo

```shell
$ git clone https://github.com/kaibaooo/cache-miss-rate-simulator.git
```

2. Build

```shell
$ cd cache-miss-rate-simulator
$ make
```

3. Execute

```
$ ./Source.out <tracefile> <cache_size> <block_size> <set_degree> <debug_mode>
$ ./Source.out trace.txt 1024 4 2 0
Trace File : trace.txt
Cache Size : 1 KBytes   Block Size : 4  Set Degree : 2
Total Cache Operation : 5003
Hit : 484,       Miss : 4519
Miss Rate : 0.903258
```

* tracefile : Input address file for simulate.
* cache_size : Cache size in bytes.
* block_size : Block size in bytes.
* set_degree : Number of blocks in a set.
* debug_mode : 0 for no debug info, 1 for showing debug info.
