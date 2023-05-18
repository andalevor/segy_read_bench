/**
 * \file SeisTrace.h
 * \brief Main type and functions declarations.
 * \author andalevor
 * \date 2022/10/31
 */

#ifndef SEIS_TRACE_H
#define SEIS_TRACE_H

#include <stdbool.h>

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
#endif /* SEIS_TRACE_H */
