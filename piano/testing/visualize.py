from matplotlib import pyplot as plt

x = []
y = []
with open("res.txt", "r") as f:
    for row in f.readlines():
        a,b = row.split()
        x.append(int(a)/1000)
        y.append(int(b))


plt.scatter(x,y)
plt.xlabel("Time limit (seconds)")
plt.ylabel("Score")
plt.plot((0,5),(444,444),label="Optimal",color="red")
plt.legend()
plt.show()
