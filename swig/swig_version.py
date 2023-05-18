import seissegy

sgy = seissegy.seis_isegy_new()
seissegy.seis_isegy_open(sgy, "filt_mig.sgy")
sum = 0.0
while not seissegy.seis_isegy_end_of_data(sgy):
    trc = seissegy.seis_isegy_read_trace(sgy)
    samp = seissegy.seis_trace_get_samples(trc)
    samp_num = seissegy.seis_trace_get_samples_num(trc)
    for i in range(samp_num):
        sum += seissegy.doubleArray_getitem(samp, i)
    seissegy.seis_trace_unref(trc)
seissegy.seis_isegy_unref(sgy)
print(sum)
