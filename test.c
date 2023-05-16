#include <SeisISegy.h>
#include <SeisTrace.h>

int main(void) {
	SeisISegy *sgy = seis_isegy_new();
	seis_isegy_open(sgy,"filt_mig.sgy");
	double sum = 0.0;
	while(!seis_isegy_end_of_data(sgy)){
		SeisTrace *trc = seis_isegy_read_trace(sgy);
		long long samp_num = seis_trace_get_samples_num(trc);
		double *samples = seis_trace_get_samples(trc);
		for (int i = 0; i < samp_num; ++i)
			sum += samples[i];
		seis_trace_unref(trc);
	}
	seis_isegy_unref(sgy);
	printf("Sum = %f\n", sum);
}
