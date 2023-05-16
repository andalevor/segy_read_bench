from libcpp cimport bool
from libc.stdint cimport int32_t, int16_t, uint8_t, uint64_t
from seistrace cimport SeisTrace, SeisTraceHeader

cdef extern from "/usr/local/include/SeisCommonSegy.h":
    ctypedef struct SeisSegyBinHdr:
        int32_t job_id
        int32_t line_num
        int32_t reel_num
        int16_t tr_per_ens
        int16_t aux_per_ens
        int16_t samp_int
        int16_t samp_int_orig
        int16_t samp_per_tr
        int16_t samp_per_tr_orig
        int16_t format_code
        int16_t ens_fold
        int16_t sort_code
        int16_t vert_sum_code
        int16_t sw_freq_at_start
        int16_t sw_freq_at_end
        int16_t sw_length
        int16_t sw_type_code
        int16_t sw_ch_tr_num
        int16_t taper_at_start
        int16_t taper_at_end
        int16_t taper_type
        int16_t corr_traces
        int16_t bin_gain_recov
        int16_t amp_recov_meth
        int16_t measure_system
        int16_t impulse_sig_pol
        int16_t vib_pol_code
        int32_t ext_tr_per_ens
        int32_t ext_aux_per_ens
        int32_t ext_samp_per_tr
        double ext_samp_int
        double ext_samp_int_orig
        int32_t ext_samp_per_tr_orig
        int32_t ext_ens_fold
        int32_t endianness
        uint8_t SEGY_rev_major_ver
        uint8_t SEGY_rev_minor_ver
        int16_t fixed_tr_length
        int16_t ext_text_headers_num
        int32_t max_num_add_tr_headers
        int16_t time_basis_code
        uint64_t num_of_tr_in_file
        uint64_t byte_off_of_first_tr
        int32_t num_of_trailer_stanza

    ctypedef enum SeisSegyErrCode:
        SEIS_SEGY_ERR_OK
        SEIS_SEGY_ERR_FILE_OPEN
        SEIS_SEGY_ERR_FILE_READ
        SEIS_SEGY_ERR_NO_MEM
        SEIS_SEGY_ERR_UNKNOWN_ENDIANNESS
        SEIS_SEGY_ERR_UNSUPPORTED_FORMAT
        SEIS_SEGY_ERR_BROKEN_FILE
        SEIS_SEGY_ERR_FILE_WRITE

    ctypedef struct SeisSegyErr:
        SeisSegyErrCode code
        char *message

cdef extern from "/usr/local/include/SeisISegy.h":
    ctypedef struct SeisISegy:
        pass

    SeisISegy *seis_isegy_new();
    SeisISegy *seis_isegy_ref(SeisISegy *sgy);
    void seis_isegy_unref(SeisISegy *sgy);
    const SeisSegyErr *seis_isegy_get_error(const SeisISegy *sgy);
    SeisSegyErrCode seis_isegy_open(SeisISegy *sgy, const char *file_name);
    SeisTrace *seis_isegy_read_trace(SeisISegy *sgy);
    SeisTraceHeader *seis_isegy_read_trace_header(SeisISegy *sgy);
    size_t seis_isegy_get_text_headers_num(const SeisISegy *sgy);
    const char *seis_isegy_get_text_header(const SeisISegy *sgy, size_t idx);
    const SeisSegyBinHdr *seis_isegy_get_binary_header(const SeisISegy *sgy);
    bool seis_isegy_end_of_data(const SeisISegy *sgy);
    void seis_isegy_rewind(SeisISegy *sgy);
