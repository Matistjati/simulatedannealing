import sys

with open(sys.argv[1], "r") as f:
    lines = f.readlines()
lines = [l for l in lines if not l.startswith('c')]

for l in lines:
    if l.startswith('p edge '):
        l = l[len("p edge "):-1]
    else:
        l = l[2:-1]
    
    print(l)