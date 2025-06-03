from matplotlib import pyplot as plt

def get_pts_filter(upper_bound):

    x = []
    y = []
    z = []
    with open("v1/res.txt", "r") as f:
        for row in f.readlines():
            a,b,c = map(float,row.split())
            if float(c)>upper_bound:
                continue
            x.append(a)
            y.append(b)
            z.append(c)
    return x,y,z

x,y,z=get_pts_filter(64)
print(f"{min(z)=}")
sc = plt.scatter(x,y,c=z,cmap='viridis')
cbar = plt.colorbar(sc)
plt.xlabel = "t_end"
plt.ylabel = "t_start"
plt.yscale('log')
plt.xscale('log')
plt.legend()
plt.show()
