# convert the can_log.log from sim into a C file

fin = open("../pc/can_log.log", "r")
fout = open("../src_gen/can_log.c", "w")

fout.write("#include \"../src_11c24/can_log.h\"\n\n")

fout.write("const can_log_entry_t can_log_entries[] = {\n")

for line in fin.readlines():
    p = line.split(",")
    t = float(p[0])
    ti = int(t*100) # 10ms time units
    mid = int(p[1][1:], 16)
    data = []
    for d in p[2:]:
        data.append(int(d[1:], 16))
    dl = len(data)
    while len(data) < 8:
        data.append(0)
    ds = ",".join([str(di) for di in data])
    fout.write("{{{},{},{},{{{}}}}},\n".format(
        ti, mid, dl, ds))

fout.write("{0, 0, 0xFF, {0,0,0,0,0,0,0,0}}\n")
fout.write("};\n")