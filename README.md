# segy_read_bench
testing segy reading speed

data: http://s3.amazonaws.com/teapot/filt_mig.sgy

I ran 10 times

| c        |  2.1 |
| c++      |  2.3 |
| pybind11 |  9.4 |
| cffi     | 15.6 |
| ctypes   | 15.7 |
| cython   | 59.5 |
