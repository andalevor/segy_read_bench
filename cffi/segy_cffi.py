import _cffi
from trace_cffi import Trace, TraceHeader

class ISegy:
    def __init__(self, file_name):
        self.__ptr = _cffi.lib.seis_isegy_new()
        if self.__ptr == 0:
            raise RuntimeError("No memory")
        code = _cffi.lib.seis_isegy_open(self.__ptr, file_name.encode())
        self.__err = _cffi.lib.seis_isegy_get_error(self.__ptr)
        if code != _cffi.lib.SEIS_SEGY_ERR_OK:
            raise RuntimeError(self.__err.message)

    def read_trace(self):
        if _cffi.lib.seis_isegy_end_of_data(self.__ptr):
            raise StopIteration
        ptr = _cffi.lib.seis_isegy_read_trace(self.__ptr)
        if self.__err.code != _cffi.lib.SEIS_SEGY_ERR_OK:
            raise RuntimeError(self.__err.message)
        return Trace(pointer=ptr)

    def read_header(self):
        if _cffi.lib.seis_isegy_end_of_data(self.__ptr):
            raise StopIteration
        ptr = _cffi.lib.seis_isegy_read_trace_header(self.__ptr)
        if self.__err.code != _cffi.lib.SEIS_SEGY_ERR_OK:
            raise RuntimeError(self.__err.message)
        return TraceHeader(pointer=ptr)

    def get_text_headers(self):
        num = _cffi.lib.seis_isegy_get_text_headers_num(self.__ptr)
        lst = []
        for i in range(num):
            lst.append(_cffi.lib.seis_isegy_get_text_header(self.__ptr, i))
        return lst

    def get_binary_header(self):
        return _cffi.lib.seis_isegy_get_binary_header(self.__ptr)

    def traces(self):
        return self.TraceIter(self)

    def headers(self):
        return self.HeaderIter(self)

    def __enter__(self):
        return self

    def __exit__(self):
        _cffi.lib.seis_isegy_unref(self.__ptr)

    class TraceIter:
        def __init__(self, isegy):
            self.__isegy = isegy

        def __iter__(self):
            _cffi.lib.seis_isegy_rewind(self.__isegy._ISegy__ptr)
            return self

        def __next__(self):
            return self.__isegy.read_trace()

    class HeaderIter:
        def __init__(self, isegy):
            self.__isegy = isegy

        def __iter__(self):
            _cffi.lib.seis_isegy_rewind(self.__isegy._ISegy__ptr)
            return self

        def __next__(self):
            return self.__isegy.read_header()
