from ctypes import CDLL, c_bool, c_char_p, c_int, c_int32, c_int16, c_void_p, POINTER
from ctypes import Structure, c_double, c_uint8, c_uint64, c_size_t, create_string_buffer
from trace_ctypes import Trace, TraceHeader

lib = CDLL("./ctypes/lib/libseissegy.so")

(ERR_OK,
 ERR_FILE_OPEN,
 ERR_FILE_READ,
 ERR_NO_MEM,
 ERR_UNKNOWN_ENDIANNESS,
 ERR_UNSUPPORTED_FORMAT,
 ERR_BROKEN_FILE,
 ERR_FILE_WRITE) = (0, 1, 2, 3, 4, 5, 6, 7)

class SegyError(Structure):
    _fields_ = [("code", c_int), ("message", c_char_p)]

class SegyBinHdr(Structure):
    _fields_ = [
            ("job_id", c_int32),
            ("line_num", c_int32),
            ("reel_num", c_int32),
            ("tr_per_ens", c_int16),
            ("aux_per_ens", c_int16),
            ("samp_int", c_int16),
            ("samp_int_orig", c_int16),
            ("samp_per_tr", c_int16),
            ("samp_per_tr_orig", c_int16),
            ("format_code", c_int16),
            ("ens_fold", c_int16),
            ("sort_code", c_int16),
            ("vert_sum_code", c_int16),
            ("sw_freq_at_start", c_int16),
            ("sw_freq_at_end", c_int16),
            ("sw_length", c_int16),
            ("sw_type_code", c_int16),
            ("sw_ch_tr_num", c_int16),
            ("taper_at_start", c_int16),
            ("taper_at_end", c_int16),
            ("taper_type", c_int16),
            ("corr_traces", c_int16),
            ("bin_gain_recov", c_int16),
            ("amp_recov_meth", c_int16),
            ("measure_system", c_int16),
            ("impulse_sig_pol", c_int16),
            ("vib_pol_code", c_int16),
            ("ext_tr_per_ens", c_int32),
            ("ext_aux_per_ens", c_int32),
            ("ext_samp_per_tr", c_int32),
            ("ext_samp_int", c_double),
            ("ext_samp_int_orig", c_double),
            ("ext_samp_per_tr_orig", c_int32),
            ("ext_ens_fold", c_int32),
            ("endianness", c_int32),
            ("SEGY_rev_major_ver", c_uint8),
            ("SEGY_rev_minor_ver", c_uint8),
            ("fixed_tr_length", c_int16),
            ("ext_text_headers_num", c_int16),
            ("max_num_add_tr_headers", c_int32),
            ("time_basis_code", c_int16),
            ("num_of_tr_in_file", c_uint64),
            ("byte_off_of_first_tr", c_uint64),
            ("num_of_trailer_stanza", c_int32)]

class ISegy:
    __seis_isegy_new = lib.seis_isegy_new
    __seis_isegy_new.restype = c_void_p
    __seis_isegy_unref = lib.seis_isegy_unref
    __seis_isegy_unref.argtypes = [c_void_p]
    __seis_isegy_get_error = lib.seis_isegy_get_error
    __seis_isegy_get_error.argtypes = [c_void_p]
    __seis_isegy_get_error.restype = POINTER(SegyError)
    __seis_isegy_open = lib.seis_isegy_open
    __seis_isegy_open.argtypes = [c_void_p, c_char_p]
    __seis_isegy_read_trace = lib.seis_isegy_read_trace
    __seis_isegy_read_trace.argtypes = [c_void_p]
    __seis_isegy_read_trace.restype = c_void_p
    __seis_isegy_read_trace_header = lib.seis_isegy_read_trace_header
    __seis_isegy_read_trace_header.argtypes = [c_void_p]
    __seis_isegy_read_trace_header.restype = c_void_p
    __seis_isegy_get_text_headers_num = lib.seis_isegy_get_text_headers_num
    __seis_isegy_get_text_headers_num.argtypes = [c_void_p]
    __seis_isegy_get_text_headers_num.restype = c_size_t
    __seis_isegy_get_text_header = lib.seis_isegy_get_text_header
    __seis_isegy_get_text_header.argtypes = [c_void_p, c_size_t]
    __seis_isegy_get_text_header.restype = c_char_p
    __seis_isegy_get_binary_header = lib.seis_isegy_get_binary_header
    __seis_isegy_get_binary_header.argtypes = [c_void_p]
    __seis_isegy_get_binary_header.restype = POINTER(SegyBinHdr)
    __seis_isegy_end_of_data = lib.seis_isegy_end_of_data
    __seis_isegy_end_of_data.argtypes = [c_void_p]
    __seis_isegy_end_of_data.restype = c_bool
    __seis_isegy_rewind = lib.seis_isegy_rewind
    __seis_isegy_rewind.argtypes = [c_void_p]

    def __init__(self, file_name):

        self.__pimpl = self.__seis_isegy_new()
        if self.__pimpl == 0:
            raise RuntimeError("No memory")
        code = self.__seis_isegy_open(self.__pimpl, file_name.encode())
        self.__err = self.__seis_isegy_get_error(self.__pimpl)
        if code != ERR_OK:
            raise RuntimeError(self.__err.contents.message)

    def read_trace(self):
        if self.__seis_isegy_end_of_data(self.__pimpl):
            raise StopIteration
        ptr = self.__seis_isegy_read_trace(self.__pimpl)
        if self.__err.contents.code != ERR_OK:
            raise RuntimeError(self.__err.contents.message)
        return Trace(pointer=ptr)

    def read_header(self):
        if self.__seis_isegy_end_of_data(self.__pimpl):
            raise StopIteration
        ptr = self.__seis_isegy_read_trace_header(self.__pimpl)
        if self.__err.contents.code != ERR_OK:
            raise RuntimeError(self.__err.contents.message)
        return TraceHeader(pointer=ptr)

    def get_text_headers(self):
        num = self.__seis_isegy_get_text_headers_num(self.__pimpl)
        lst = []
        for i in range(num):
            lst.append(self.__seis_isegy_get_text_header(self.__pimpl, i))
        return lst

    def get_binary_header(self):
        return self.__seis_isegy_get_binary_header(self.__pimpl).contents

    def traces(self):
        return self.TraceIter(self)

    def headers(self):
        return self.HeaderIter(self)

    def __enter__(self):
        return self

    def __exit__(self):
        self.__seis_isegy_unref(self.__pimpl)

    class TraceIter:
        def __init__(self, isegy):
            self.__isegy = isegy

        def __iter__(self):
            self.__isegy._ISegy__seis_isegy_rewind(self.__isegy._ISegy__pimpl)
            return self

        def __next__(self):
            return self.__isegy.read_trace()

    class HeaderIter:
        def __init__(self, isegy):
            self.__isegy = isegy

        def __iter__(self):
            self.__isegy._ISegy__seis_isegy_rewind(self.__isegy._ISegy__pimpl)
            return self

        def __next__(self):
            return self.__isegy.read_header()

__ascii_to_ebcdic = lib.ascii_to_ebcdic
__ascii_to_ebcdic.argtypes = [c_char_p]
def ascii_to_ebcdic(string):
    mutable = create_string_buffer(string)
    __ascii_to_ebcdic(mutable)
    return mutable.value

__ebcdic_to_ascii = lib.ebcdic_to_ascii
__ebcdic_to_ascii.argtypes = [c_char_p]
def ebcdic_to_ascii(string):
    mutable = create_string_buffer(string)
    __ebcdic_to_ascii(mutable)
    return mutable.value
