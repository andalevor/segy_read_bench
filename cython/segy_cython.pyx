cimport seissegy
from libc.stdint cimport uintptr_t
from trace_cython import Trace, TraceHeader

cdef class ISegy:
    cdef seissegy.SeisISegy* _ptr

    def __cinit__(self, file_name):
        self._ptr = seissegy.seis_isegy_new()
        seissegy.seis_isegy_open(self._ptr, file_name.encode())

    def __dealloc__(self):
        seissegy.seis_isegy_unref(self._ptr)

    def __iter__(self):
        seissegy.seis_isegy_rewind(self._ptr)
        return self

    def __next__(self):
        if seissegy.seis_isegy_end_of_data(self._ptr):
            raise StopIteration
        else:
            return Trace(0, pointer=<uintptr_t>seissegy.seis_isegy_read_trace(self._ptr))

    def read_trace(self):
        return Trace(0, pointer=<uintptr_t>seissegy.seis_isegy_read_trace(self._ptr))


