#include <m-dict.h>
#include <m-string.h>
#include <m-variant.h>
#include <stdlib.h>
#include <assert.h>
#include "SeisTrace.h"

VARIANT_DEF2(val, (INT, long long), (REAL, double))
#define M_OPL_val_t() VARIANT_OPLIST(val, M_BASIC_OPLIST, M_BASIC_OPLIST)
DICT_DEF2(val_dict, string_t, val_t)
#define M_OPL_val_dict_t() DICT_OPLIST(val_dict, STRING_OPLIST, M_OPL_val_t())

struct SeisTraceHeader {
	int rc;
	val_dict_t dict;
};

struct SeisTrace {
	int rc;
	SeisTraceHeader *header;
	double *samples;
	long long samp_num;
};

typedef enum {INT, REAL} SEIS_TRACE_HEADER_VALUE;

SeisTrace *seis_trace_new(long long samp_num)
{
	assert(samp_num);
	SeisTrace *t = (SeisTrace *)malloc(sizeof(struct SeisTrace));
	if (!t)
		goto error;
	t->header = seis_trace_header_new();
	if (!t->header)
		goto error;
	t->samples = (double *)malloc(sizeof(double) *samp_num);
	if (!t->samples)
		goto error;
	t->rc = 1;
	t->samp_num = samp_num;
	return t;
error:
	if (t) {
		if (t->header) {
			val_dict_clear(t->header->dict);
			free(t->header);
		}
		free(t);
	}
	return NULL;
}

SeisTrace *seis_trace_new_with_header(long long samp_num, SeisTraceHeader *hdr)
{
	assert(samp_num);
	assert(hdr);
	SeisTrace *t = (SeisTrace *)malloc(sizeof(struct SeisTrace));
	if (!t)
		goto error;
	t->samples = (double *)malloc(sizeof(double) *samp_num);
	if (!t->samples)
		goto error;
	t->rc = 1;
	t->header = hdr;
	t->samp_num = samp_num;
	return t;
error:
	seis_trace_header_unref(hdr);
	if (t) {
		free(t);
	}
	return NULL;
}

SeisTrace *seis_trace_ref(SeisTrace *t)
{
	++t->rc;
	return t;
}

void seis_trace_unref(SeisTrace *t)
{
	if (--t->rc == 0) {
		free(t->samples);
		seis_trace_header_unref(t->header);
		free(t);
	}
}

SeisTraceHeader *seis_trace_header_new(void)
{
	SeisTraceHeader *hdr = (SeisTraceHeader *)
		malloc(sizeof(struct SeisTraceHeader));
	if (!hdr)
		return NULL;
	val_dict_init(hdr->dict);
	hdr->rc = 1;
	return hdr;
}

SeisTraceHeader *seis_trace_get_header(SeisTrace *trc)
{
	return trc->header;
}

SeisTraceHeader const *seis_trace_get_header_const(SeisTrace const *trc)
{
	return trc->header;
}

SeisTraceHeader *seis_trace_header_ref(SeisTraceHeader *hdr)
{
	++hdr->rc;
	return hdr;
}

void seis_trace_header_unref(SeisTraceHeader *hdr)
{
	if (--hdr->rc == 0) {
		val_dict_clear(hdr->dict);
		free(hdr);
	}
}

void seis_trace_header_set_int(SeisTraceHeader *hdr, char const *hdr_name,
							   long long val)
{
	string_t header_name;
	string_init_set_str(header_name, hdr_name);
	val_t v;
	val_init(v);
	val_set_INT(v, val);
	val_dict_set_at(hdr->dict, header_name, v);
	val_clear(v);
	string_clear(header_name);
}

void seis_trace_header_set_real(SeisTraceHeader *hdr, char const *hdr_name,
							   	double val)
{
	string_t header_name;
	string_init_set_str(header_name, hdr_name);
	val_t v;
	val_init(v);
	val_set_REAL(v, val);
	val_dict_set_at(hdr->dict, header_name, v);
	val_clear(v);
	string_clear(header_name);
}

long long const *seis_trace_header_get_int(SeisTraceHeader const *hdr,
										   char const *hdr_name)
{
	string_t header_name;
	string_init_set_str(header_name, hdr_name);
	val_t *v = val_dict_get(hdr->dict, header_name);
	string_clear(header_name);
	if (v)
		return val_get_INT(*v);
	else
		return NULL;
}

double const *seis_trace_header_get_real(SeisTraceHeader const *hdr,
										 char const *hdr_name)
{
	string_t header_name;
	string_init_set_str(header_name, hdr_name);
	val_t *v = val_dict_get(hdr->dict, header_name);
	string_clear(header_name);
	if (v)
		return val_get_REAL(*v);
	else
		return NULL;
}

double *seis_trace_get_samples(SeisTrace *t)
{
	return t->samples;
}

long long seis_trace_get_samples_num(SeisTrace const *t)
{
	return t->samp_num;
}

double const *seis_trace_get_samples_const(SeisTrace const *t)
{
	return t->samples;
}

bool seis_trace_header_is_int(SeisTraceHeader const *hdr, char const *hdr_name)
{
	string_t header_name;
	string_init_set_str(header_name, hdr_name);
	val_t *v = val_dict_get(hdr->dict, header_name);
	return val_INT_p(*v);
}

bool seis_trace_header_is_real(SeisTraceHeader const *hdr, char const *hdr_name)
{
	string_t header_name;
	string_init_set_str(header_name, hdr_name);
	val_t *v = val_dict_get(hdr->dict, header_name);
	return val_REAL_p(*v);
}

bool seis_trace_header_exist(SeisTraceHeader const *hdr, char const *hdr_name)
{
	string_t header_name;
	string_init_set_str(header_name, hdr_name);
	val_t *v = val_dict_get(hdr->dict, header_name);
	return v ? true : false;
}
