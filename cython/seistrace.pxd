from libcpp cimport bool

cdef extern from "/usr/local/include/SeisTrace.h":
    ctypedef struct SeisTrace:
        pass
    ctypedef struct SeisTraceHeader:
        pass

    SeisTrace *seis_trace_new(long long samp_num)
    SeisTrace *seis_trace_new_with_header(long long samp_num, SeisTraceHeader *hdr)
    SeisTrace *seis_trace_ref(SeisTrace *trc)
    void seis_trace_unref(SeisTrace *trc)
    SeisTraceHeader *seis_trace_get_header(SeisTrace *trc)
    const SeisTraceHeader *seis_trace_get_header_const(const SeisTrace *trc)
    double *seis_trace_get_samples(SeisTrace *trc)
    const double *seis_trace_get_samples_const(const SeisTrace *trc)
    long long seis_trace_get_samples_num(const SeisTrace *trc)
    SeisTraceHeader *seis_trace_header_new()
    SeisTraceHeader *seis_trace_header_ref(SeisTraceHeader *trc)
    void seis_trace_header_unref(SeisTraceHeader *trc)
    void seis_trace_header_set_int(SeisTraceHeader *hdr, const char *hdr_name,
                                   long long val)
    void seis_trace_header_set_real(SeisTraceHeader *hdr, const char *hdr_name,
                                    double val)
    const long long *seis_trace_header_get_int(const SeisTraceHeader *hdr,
                                               const char *hdr_name)
    const double *seis_trace_header_get_real(const SeisTraceHeader *hdr,
                                             const char *hdr_name)
    bool seis_trace_header_is_int(const SeisTraceHeader *hdr, const char *hdr_name)
    bool seis_trace_header_is_real(const SeisTraceHeader *hdr,
                                   const char *hdr_name)
    bool seis_trace_header_exist(const SeisTraceHeader *hdr, const char *hdr_name)
