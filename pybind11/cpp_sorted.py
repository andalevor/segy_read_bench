from pysedaman import ISEGYSorted1D

sum = 0.0
for trace in ISEGYSorted1D("/home/andalevor/Work/UNGF/mozga/vas.stk.segy", "TRC_SEQ_LINE"):
    for samp in trace.samples():
        sum += samp

print("Sum = {}".format(sum))
