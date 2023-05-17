import segyio
import numpy as np

sum = 0.0
with segyio.open("filt_mig.sgy") as f:
    for trace in f.trace:
        for samp in trace:
           sum += samp

print("Sum = {}".format(sum))
