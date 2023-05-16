from segy_cffi import ISegy

sgy = ISegy("filt_mig.sgy")
sum = 0.0
for trc in sgy.traces():
    for samp in trc.samples():
        sum += samp

print("Sum = {}".format(sum))
