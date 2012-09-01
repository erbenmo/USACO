for i in range(10000):
    name = str(i) + '.cpp'
    print name
    f = open(name, 'w')
    f.close()
