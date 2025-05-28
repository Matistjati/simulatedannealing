from matplotlib import pyplot as plt

x = []
y = []
z = []
with open("delete/res.txt", "r") as f:
    for row in f.readlines():
        a,b,c = map(float,row.split())
        if int(c)<62:
            continue
        x.append(a)
        y.append(b)
        z.append(c)

sc = plt.scatter(x,y,c=z,cmap='viridis')
cbar = plt.colorbar(sc)
plt.yscale('log')
plt.xscale('log')
plt.legend()
plt.show()
