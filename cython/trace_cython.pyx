cimport seistrace
from libc.stdint cimport uintptr_t

cdef class TraceHeader:
    cdef seistrace.SeisTraceHeader* _ptr

    def __cinit__(self, uintptr_t pointer = 0):
        if pointer:
            self._ptr = <seistrace.SeisTraceHeader*>pointer
        else:
            self._ptr = seistrace.seis_trace_header_new()

    def __dealloc__(self):
        seistrace.seis_trace_header_unref(self._ptr)

    def set(self, hdr_name, val):
        """Cast val whether to inti or to float to write header
        in appropriate format"""
        if isinstance(val, int):
            seistrace.seis_trace_header_set_int(self._ptr, hdr_name.encode(),
                                                val)
        elif isinstance(val, float):
            seistrace.seis_trace_header_set_real(self._ptr, hdr_name.encode(),
                                                 val)
        else:
            raise TypeError("Header value could be only integer"
                            " or floating point")

    def get(self, hdr_name):
        cdef const long long *ir
        cdef const double *dr
        if not seistrace.seis_trace_header_exist(self._ptr, hdr_name.encode()):
            raise ValueError("No such header")
        if seistrace.seis_trace_header_is_int(self._ptr, hdr_name.encode()):
            ir = seistrace.seis_trace_header_get_int(self._ptr,
                                                      hdr_name.encode())
            return ir[0]
        else:
            dr = seistrace.seis_trace_header_get_real(self._ptr,
                                                       hdr_name.encode())
            return dr[0]

cdef class Trace:
    cdef seistrace.SeisTrace* _ptr

    def __cinit__(self, int samp_num, uintptr_t pointer = 0):
        if pointer:
            self._ptr = <seistrace.SeisTrace*>pointer
        else:
            self._ptr = seistrace.seis_trace_new(samp_num)

    def __dealloc__(self):
        seistrace.seis_trace_unref(self._ptr)

    def header(self):
        cdef seistrace.SeisTraceHeader* hp = seistrace.seis_trace_get_header(self._ptr)
        seistrace.seis_trace_header_ref(hp)
        return TraceHeader(pointer=<uintptr_t>hp)

    def samples(self):
        cdef long long num = seistrace.seis_trace_get_samples_num(self._ptr)
        cdef double *samp = seistrace.seis_trace_get_samples(self._ptr)
        return <double[:num]>samp
