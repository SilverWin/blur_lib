This code is based on algorithm from http://blog.ivank.net/fastest-gaussian-blur.html

## Example
There is simple program in `test` folder.

To build it do:
```bash
cd test
make
```
Then run it with:
```
./test in.png out.png
```

## How to use in your project
Just add `blur.c` and `blur.h` to your project and blur image with `fast_gauss_blur` function.

