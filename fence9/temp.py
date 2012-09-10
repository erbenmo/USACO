import sys
for y in range(0, 5):
    sys.stdout.write(str(y))
    sys.stdout.write(" ")

    x1 = 7.0/5*y
    sys.stdout.write(str(x1))
    sys.stdout.write(" ")
    x2 = 10-3.0/5*y
    sys.stdout.write(str(x2))
    sys.stdout.write(" ")
    print x2-x1
