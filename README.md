# C API

## Dependencies

- [libmicrohttpd](https://www.gnu.org/software/libmicrohttpd/)
- [jansson](https://github.com/akheron/jansson)

## Build

### Dependencies

#### Toolkit

- GCC
- CMake
- PkgConfig
- Make (or Ninja)

#### Headers
- libmicrohttpd
- jansson

### Build executable

```sh
mkdir build
cd build
cmake .. # or cmake -G Ninja ..
make # or ninja

# docker
docker build -t c-api . # or make docker-build
```

## Run

The executable accepts 2 arguments: (1) TCP port to listen to, and (2) thread pool size (defaults to 1).
```sh
./c-api 8080 4

# docker
docker run -itP c-api # or make docker-run
```
