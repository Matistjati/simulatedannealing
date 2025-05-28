from matplotlib import pyplot as plt

x = []
y = []
z = []
with open("res.txt", "r") as f:
    for row in f.readlines():
        a,b,c = map(float,row.split())
        x.append(a)
        y.append(b)
        z.append("red" if c==0 else "green")


fig, ax = plt.subplots()
scatter = ax.scatter(x, y, c=z)

ax.set_xscale('log')
ax.set_yscale('log')
ax.set_xlabel("T_lo")
ax.set_ylabel("T_hi")

plt.title("Does solution get AC for different pairs of T_lo and T_hi. Note the log scale")
plt.tight_layout()
plt.show()