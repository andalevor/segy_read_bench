require("seissegy")

sgy = seissegy.seis_isegy_new()
seissegy.seis_isegy_open(sgy, "filt_mig.sgy")
sum = 0.0
while(not seissegy.seis_isegy_end_of_data(sgy))
do
	trc = seissegy.seis_isegy_read_trace(sgy)
	samp = seissegy.seis_trace_get_samples(trc)
	samp_num = seissegy.seis_trace_get_samples_num(trc)
	for i = 0,samp_num,1
	do
		sum = sum + seissegy.doubleArray_getitem(samp, i)
	end
end
print(sum)
