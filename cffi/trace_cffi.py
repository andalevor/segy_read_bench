import _cffi
from numpy import frombuffer

class TraceHeader:
    def __init__(self, pointer = None) -> None:
        if pointer:
            self.__ptr = pointer
        else:
            self.__ptr = _cffi.lib.seis_trace_header_new()

    def __enter__(self):
        return self

    def __exit__(self):
        _cffi.lib.seis_trace_header_unref(self.__ptr)

    def set(self, hdr_name, val):
        """Cast val whether to int or to float to write header
        in appropriate format"""
        if isinstance(val, int):
            _cffi.lib.seis_trace_header_set_int(self.__ptr, hdr_name.encode(),
                                             val)
        elif isinstance(val, float):
            _cffi.lib.seis_trace_header_set_real(self.__ptr, hdr_name.encode(),
                                              val)
        else:
            raise TypeError("Header value could be only integer"
                            " or floating point")

    def get(self, hdr_name):
        if not _cffi.lib.seis_trace_header_exist(self.__ptr, hdr_name.encode()):
            raise ValueError("No such header")
        if _cffi.lib.seis_trace_header_is_int(self.__ptr, hdr_name.encode()):
            res = _cffi.lib.seis_trace_header_get_int(self.__ptr,
                                                   hdr_name.encode())
        else:
            res = _cffi.lib.seis_trace_header_get_real(self.__ptr,
                                                    hdr_name.encode())
        return res[0]

class Samples:
    def __init__(self, pointer, num):
        self.ptr = pointer
        self.num = num

    def __iter__(self):
        self.counter = 0
        return self

    def __next__(self):
        if self.counter < self.num:
            res = self.ptr[self.counter]
            self.counter += 1
            return res
        else:
            raise StopIteration

class Trace:
    def __init__(self, samp_num = None, hdr = None, pointer = None):
        if pointer:
            self.__ptr = pointer
        elif samp_num:
            if hdr:
                self.__ptr = _cffi.lib.seis_trace_new_with_header(samp_num, hdr.__ptr)
            else:
                self.__ptr = _cffi.lib.seis_trace_new(samp_num)
        else:
            raise TypeError("Pointer or samp_num should be specified")

    def __enter__(self):
        return self

    def __exit__(self):
        _cffi.lib.seis_trace_unref(self.__ptr)

    def header(self):
        return TraceHeader(_cffi.lib.seis_trace_get_header(self.__ptr))

    def samples(self):
        num = _cffi.lib.seis_trace_get_samples_num(self.__ptr)
        samp = _cffi.lib.seis_trace_get_samples(self.__ptr)
        samp = _cffi.ffi.cast("double *", samp)
        #  return frombuffer(_cffi.ffi.buffer(samp, num*_cffi.ffi.sizeof("double")))
        return Samples(samp, num)
