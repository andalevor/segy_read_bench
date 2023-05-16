/**
 * \file SeisISegy.h
 * \brief Main type and functions for SEGY manipulation.
 * \author andalevor
 * \date 2022\11\20
 */

 /**
 * \struct SeisTrace
 * \brief Main type for seismic trace.
 */
typedef struct SeisTrace SeisTrace;

/**
 * \struct SeisTraceHeader
 * \brief Type for seismic trace header
 */
typedef struct SeisTraceHeader SeisTraceHeader;

/**
 * \fn seis_trace_new
 * \brief Creates new SeisTrace object.
 * \param samp_num Number of samples in created trace. Can not be zero.
 * \return Pointer to SeisTrace or NULL if there are no free memory.
 */
SeisTrace *seis_trace_new(long long samp_num);

/**
 * \fn seis_trace_new
 * \brief Creates new SeisTrace object.
 * \param samp_num Number of samples in created trace. Can not be zero.
 * \param hdr SeisTraceHeader object. Trace will own header. Can not be zero.
 * \return Pointer to SeisTrace or NULL if there are no free memory.
 */
SeisTrace *seis_trace_new_with_header(long long samp_num, SeisTraceHeader *hdr);

/**
 * \fn seis_trace_ref
 * \brief Makes rc increment.
 * \param t Pointer to SeisTrace object.
 * \return Pointer to SeisTrace object.
 */
SeisTrace *seis_trace_ref(SeisTrace *trc);

/**
 * \fn seis_trace_unref
 * \brief Rc decrement. Frees memory when rc = 0.
 * \param t Pointer to SeisTrace object.
 */
void seis_trace_unref(SeisTrace *trc);

/**
 * \fn seis_trace_get_header
 * \brief Gets trace header.
 * It's a part of trace. And should not be fried.
 * \param t Pointer to SeisTrace object.
 */
SeisTraceHeader *seis_trace_get_header(SeisTrace *trc);

/**
 * \fn seis_trace_get_header_const
 * \brief Gets trace header.
 * It's a part of trace. And should not be fried.
 * \param t Pointer to SeisTrace object.
 */
SeisTraceHeader const *seis_trace_get_header_const(SeisTrace const *trc);

/**
 * \fn seis_trace_get_samples
 * \brief Gets data samples from struct. You should not free memory.
 * \param t SeisTrace object.
 */
double *seis_trace_get_samples(SeisTrace *trc);

/**
 * \fn seis_trace_get_samples_const
 * \brief Gets const data samples from struct. You should not free memory.
 * \param t SeisTrace object.
 */
double const *seis_trace_get_samples_const(SeisTrace const *trc);

/**
 * \fn seis_trace_get_samples_num_const
 * \brief Gets data samples number from struct.
 * \param t SeisTrace object.
 */
long long seis_trace_get_samples_num(SeisTrace const *trc);

/**
 * \fn seis_trace_header_new
 * \brief Creates new SeisTraceHeader object.
 * \return Pointer to SeisTraceHeader or NULL if there are no free memory.
 */
SeisTraceHeader *seis_trace_header_new(void);

/**
 * \fn seis_trace_header_ref
 * \brief Makes rc increment.
 * \param t Pointer to SeisTraceHeader object.
 * \return Pointer to SeisTraceHeader object.
 */
SeisTraceHeader *seis_trace_header_ref(SeisTraceHeader *trc);

/**
 * \fn seis_trace_header_unref
 * \brief Rc decrement. Frees memory when rc = 0.
 * \param t Pointer to SeisTraceHeader object.
 */
void seis_trace_header_unref(SeisTraceHeader *trc);

/**
 * \fn seis_trace_header_set_int
 * \brief Sets integer trace header value.
 * \param t Pointer to SeisTraceHeader object.
 * \param hdr_name Trace header name to set value.
 * \param val Value to set.
 */
void seis_trace_header_set_int(SeisTraceHeader *hdr, char const *hdr_name,
							   long long val);

/**
 * \fn seis_trace_header_set_real
 * \brief Sets real trace header value.
 * \param t Pointer to SeisTraceHeader object.
 * \param hdr_name Trace header name to set value.
 * \param val Value to set.
 */
void seis_trace_header_set_real(SeisTraceHeader *hdr, char const *hdr_name,
							   	double val);

/**
 * \fn seis_trace_header_get_cint
 * \brief Gets trace header value.
 * \param t Pointer to SeisTraceHeader object.
 * \param hdr_name Trace header name to get value.
 * \return Pointer to constant trace header value or NULL if no such header name
 */
long long const *seis_trace_header_get_int(SeisTraceHeader const *hdr,
										   char const *hdr_name);

/**
 * \fn seis_trace_header_get_creal
 * \brief Gets trace header value.
 * \param t Pointer to SeisTraceHeader object.
 * \param hdr_name Trace header name to get value.
 * \return Pointer to constant trace header value or NULL if no such header name
 */
double const *seis_trace_header_get_real(SeisTraceHeader const *hdr,
										 char const *hdr_name);

/**
 * \fn seis_trace_header_is_int
 * \brief Checks whether header integer or not
 * \param t Pointer to SeisTraceHeader object.
 * \param hdr_name Trace header name to check value.
 * \return True if integer.
 */
bool seis_trace_header_is_int(SeisTraceHeader const *hdr, char const *hdr_name);

/**
 * \fn seis_trace_header_is_real
 * \brief Checks whether header floating point or not
 * \param t Pointer to SeisTraceHeader object.
 * \param hdr_name Trace header name to check value.
 * \return True if real.
 */
bool seis_trace_header_is_real(SeisTraceHeader const *hdr,
							   char const *hdr_name);

/**
 * \fn seis_trace_header_exist
 * \brief Checks whether header exist or not
 * \param t Pointer to SeisTraceHeader object.
 * \param hdr_name Trace header name to check value.
 * \return True if exist.
 */
bool seis_trace_header_exist(SeisTraceHeader const *hdr, char const *hdr_name);

/**
 * \struct SeisSegyBinHdr
 * \brief SEGY binary header struct
 */
typedef struct SeisSegyBinHdr {
	int32_t job_id;
	int32_t line_num;
	int32_t reel_num;
	int16_t tr_per_ens;
	int16_t aux_per_ens;
	int16_t samp_int;
	int16_t samp_int_orig;
	int16_t samp_per_tr;
	int16_t samp_per_tr_orig;
	int16_t format_code;
	int16_t ens_fold;
	int16_t sort_code;
	int16_t vert_sum_code;
	int16_t sw_freq_at_start;
	int16_t sw_freq_at_end;
	int16_t sw_length;
	int16_t sw_type_code;
	int16_t sw_ch_tr_num;
	int16_t taper_at_start;
	int16_t taper_at_end;
	int16_t taper_type;
	int16_t corr_traces;
	int16_t bin_gain_recov;
	int16_t amp_recov_meth;
	int16_t measure_system;
	int16_t impulse_sig_pol;
	int16_t vib_pol_code;
	int32_t ext_tr_per_ens;
	int32_t ext_aux_per_ens;
	int32_t ext_samp_per_tr;
	double ext_samp_int;
	double ext_samp_int_orig;
	int32_t ext_samp_per_tr_orig;
	int32_t ext_ens_fold;
	int32_t endianness;
	uint8_t SEGY_rev_major_ver;
	uint8_t SEGY_rev_minor_ver;
	int16_t fixed_tr_length;
	int16_t ext_text_headers_num;
	int32_t max_num_add_tr_headers;
	int16_t time_basis_code;
	uint64_t num_of_tr_in_file;
	uint64_t byte_off_of_first_tr;
	int32_t num_of_trailer_stanza;
} SeisSegyBinHdr;

/**
 * \enum SeisSegyErrCode
 * \brief Enumeration for error codes.
 */
typedef enum SeisSegyErrCode {
	SEIS_SEGY_ERR_OK,
	SEIS_SEGY_ERR_FILE_OPEN,
	SEIS_SEGY_ERR_FILE_READ,
	SEIS_SEGY_ERR_NO_MEM,
	SEIS_SEGY_ERR_UNKNOWN_ENDIANNESS,
	SEIS_SEGY_ERR_UNSUPPORTED_FORMAT,
	SEIS_SEGY_ERR_BROKEN_FILE,
	SEIS_SEGY_ERR_FILE_WRITE,
} SeisSegyErrCode;

/**
 * \struct SeisSegyErr
 * \brief Type for SEGY manipulations error checking.
 */
typedef struct SeisSegyErr {
	SeisSegyErrCode code;
	char *message;
} SeisSegyErr;

/**
 * \struct SeisCommonSegy
 * \brief SEGY common parts.
 */
typedef struct SeisCommonSegy {
	struct SeisSegyBinHdr bin_hdr;
	struct SeisSegyErr err;
	FILE *file;
	char *samp_buf, *hdr_buf;
	int bytes_per_sample;
	long samp_per_tr;
} SeisCommonSegy;

/**
 * \fn seis_common_segy_new
 * \brief Initiates SeisCommonSegy instance.
 * \return Initiated SeisCommonSegy or NULL.
 */
SeisCommonSegy *seis_common_segy_new();

/**
 * \fn seis_common_segy_unref
 * \brief Frees memory.
 * \param com Pointer to SeisCommonSegy object.
 */
void seis_common_segy_unref(SeisCommonSegy *com);

/**
 * \fn seis_common_segy_set_text_header
 * \brief sets text header by its index
 * \param com Pointer to SeisCommonSegy object.
 * \param idx index of header. must be less than number of headers
 * \param hdr text header. must have 3200 chars length
 */
void seis_common_segy_set_text_header(SeisCommonSegy *com, size_t idx,
									  char const *hdr);

/**
 * \fn seis_common_add_text_header
 * \brief adds SEGY text header to internal storage.
 * \param com Pointer to SeisCommonSegy object.
 * \param com Pointer to buffer with header.
 */
void seis_common_segy_add_text_header(SeisCommonSegy *com, char const *buf);

/**
 * \fn seis_common_add_stanza
 * \brief adds SEGY end stanza to internal storage.
 * \param com Pointer to SeisCommonSegy object.
 * \param com Pointer to buffer with stanza.
 */
void seis_common_segy_add_stanza(SeisCommonSegy *com, char const *buf);

/**
 * \fn seis_common_get_text_headers_num
 * \brief gets number of SEGY text headers.
 * \param com Pointer to SeisCommonSegy object.
 * \return number of text headers.
 */
size_t seis_common_segy_get_text_headers_num(SeisCommonSegy const*com);

/**
 * \fn seis_common_get_text_header
 * \brief Gets text header by its index in storage. Main header at 0.
 * \param com Pointer to SeisCommonSegy object.
 * \prarm idx Index of desired text header from 0 to text_headers_num - 1.
 * \return Pointer to header. Should not be freed.
 */
char const* seis_common_segy_get_text_header(SeisCommonSegy const*com, size_t idx);

/**
 * \fn seis_common_get_stanzas_num
 * \brief gets number of SEGY end stanzas.
 * \param com Pointer to SeisCommonSegy object.
 * \return number of stanzas.
 */
size_t seis_common_segy_get_stanzas_num(SeisCommonSegy const*com);

/**
 * \fn seis_common_get_stanza
 * \brief Gets end stanza by its index in storage. Main header at 0.
 * \param com Pointer to SeisCommonSegy object.
 * \prarm idx Index of desired end stanza from 0 to end_stanzas_num - 1.
 * \return Pointer to stanza. Should not be freed.
 */
char const* seis_common_segy_get_stanza(SeisCommonSegy const*com, size_t idx);

/**
 * \brief Text header from SEGY revision 0 standard
 */
extern char const* seis_segy_default_text_header_rev0;

/**
 * \brief Text header from SEGY revision 1 standard
 */
extern char const* seis_segy_default_text_header_rev1;

/**
 * \brief Text header from SEGY revision 2 standard
 */
extern char const* seis_segy_default_text_header_rev2;

/**
 * \struct SeisISegy
 * \brief Main type for SEGY manipulation.
 */
typedef struct SeisISegy SeisISegy;

/**
 * \fn seis_isegy_new
 * \brief Initiates SeisISegy instance.
 * \return NULLable.
 */
SeisISegy *seis_isegy_new();

/**
 * \fn seis_isegy_ref
 * \brief Makes rc increment.
 * \param sgy Pointer to SeisISegy object.
 * \return nonNULL. Pointer to SeisISegy object.
 */
SeisISegy *seis_isegy_ref(SeisISegy *sgy);

/**
 * \fn seis_isegy_unref
 * \brief Frees memory.
 * \param sgy Pointer to SeisISegy object.
 */
void seis_isegy_unref(SeisISegy *sgy);

/**
 * \fn seis_isegy_get_error
 * \brief Gets SeisISegyErr structure for error checking.
 * \return nonNULL. You should not free this memory.
 */
SeisSegyErr const *seis_isegy_get_error(SeisISegy const *sgy);

/**
 * \fn seis_isegy_open
 * \brief Opens file, loads headers, prepares for trace reading.
 * \param sgy SeisISegy instance.
 * \param file_name Name of file to open.
 * \return Error code.
 */
SeisSegyErrCode seis_isegy_open(SeisISegy *sgy, char const *file_name);

/**
 * \fn seis_isegy_read_trace
 * \brief Reads current trace from file.
 * \param sgy SeisISegy instance.
 * \return NULLable. You should free this memory.
 */
SeisTrace *seis_isegy_read_trace(SeisISegy *sgy);

/**
 * \fn seis_isegy_read_trace_header
 * \brief Reads current trace header from file.
 * SeisISegy should be created in 'r' mode.
 * \param sgy SeisISegy instance.
 * \return NULLable. You should free this memory.
 */
SeisTraceHeader *seis_isegy_read_trace_header(SeisISegy *sgy);


/**
 * \fn seis_isegy_get_text_headers_num
 * \brief gets number of text headers in SEGY
 * \param sgy SeisISegy instance.
 * return number of text headers in file.
 */
size_t seis_isegy_get_text_headers_num(SeisISegy const *sgy);

/**
 * \fn seis_isegy_get_text_header
 * \brief gets text header by its index.
 * \param sgy SeisISegy instance.
 * \param idx index of tet header. main headers index 0
 * \return nonNULL. Zero terminated header. You should not free this memory.
 */
char const *seis_isegy_get_text_header(SeisISegy const *sgy, size_t idx);

/**
 * \fn seis_isegy_get_binary_header
 * \brief Getter for struct SeisISegyBinHdr
 * \param sgy SeisISegy instance.
 * \return nonNULL. You should not free this memory.
 */
SeisSegyBinHdr const *seis_isegy_get_binary_header(SeisISegy const *sgy);

/**
 * \fn seis_isegy_end_of_data
 * \brief Checks if it is possible to read one more trace.
 * \param sgy SeisISegy instance.
 * \return true if end of file reached
 */
bool seis_isegy_end_of_data(SeisISegy const *sgy);

/**
 * \fn seis_isegy_rewind
 * \brief Lets start reading data from first trace.
 * \param sgy SeisISegy instance.
 */
void seis_isegy_rewind(SeisISegy *sgy);

