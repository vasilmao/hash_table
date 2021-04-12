import matplotlib.pyplot as plt
graph_number = 7


f = open("out.csv", "r")
for i in range(graph_number - 1):
    f.readline()
x = list(map(int, f.readline().split(',')))
plt.figure(figsize=(600,400))
plt.plot(x)
#plt.ylabel('some numbers')
plt.show()
