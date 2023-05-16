from segy_cython import ISegy

sgy = ISegy("filt_mig.sgy")
sum = 0.0
for trc in sgy:
    for samp in trc.samples():
        sum += samp

print("Sum = {}".format(sum))
