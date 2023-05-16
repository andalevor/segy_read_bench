from segpy.reader import create_reader

sum = 0.0
with open('/home/andalevor/Work/UNGF/mozga/vas.stk.segy', 'rb') as segy_in_file:
    reader = create_reader(segy_in_file)
    for trace_index in reader.trace_indexes():
        for samp in reader.trace_samples(trace_index):
            sum += samp

print("Sum = {}".format(sum))
