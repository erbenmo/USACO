ds = [(180, 180), (0,120), (150, 90), (60, 90), (180, 60)]
vs = [70, 30, 50, 60, 90]

for t in range(10):
    for i in range(5):
        s,e = ds[i]
        s += t*vs[i]
        s %= 360
        e += t*vs[i]
        e %= 360
        print str(s) + " ~ " + str(e)
    print "-------"
    
    
