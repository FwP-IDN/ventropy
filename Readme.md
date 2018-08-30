# Binary Entropy Visualizer

This tool can help you visualize binary entropy value per block into graphic file. 

## Getting Started

Currently, we only support in Linux.

### Prerequisites

What things you need to use tool, you have to install following package

```
$ apt-get install libpng12-dev:i386
```

### Installing

```
$ cd src
$ make
```

### How to use

```
$ ./vent --help
Vent v.0.1, an entropy level measurement tool for ELF
Usage: ./vent [OPTIONS]

Options:
  -h,--help                   Print this help message and exit
  -f,--file FILE REQUIRED     file for information visualization
  -o,--output TEXT            output graphic format, default is png
  -i,--info TEXT              information extraction method, default is entropy
  -b,--block enum/Block in {b8=8, b16=16, b32=32}
                              Block size
```

```
$ ./vent -f vent -s 256 && eog vent.png
```
![](vent256block.png)

```
$ ./vent -f vent -s 64 -b 8 && eog vent.png
```
![](vent64_8.png)

## Todo
- ELF parser
- PE parser
- CMAKE
- UT
- ...

## Authors

* **Lattice Chang** 

## License

This project is licensed under the MIT License - see the [LICENSE.txt](LICENSE.txt) file for details.

## Acknowledgments

* Thanks for youtuber [GynvaelEN](https://www.youtube.com/watch?v=qDYwcIf0LZw) inspire me to implement this tool.