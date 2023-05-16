from pysedaman import ISEGY

sum = 0.0
for trc in ISEGY("filt_mig.sgy"):
    for samp in trc.samples():
        sum += samp

print("Sum = {}".format(sum))
