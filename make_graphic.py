import matplotlib.pyplot as plt
graph_number = 7


f = open("out.csv", "r")
for i in range(graph_number - 1):
    f.readline()
x = list(map(int, f.readline().split(',')))
disp1 = sum(map(lambda el: el * el, x)) / len(x)
disp2 = (sum(x) / len(x)) ** 2
plt.figure(figsize=(600,400))
plt.plot(x)
#plt.ylabel('some numbers')
plt.show()
print('disp =', disp1 - disp2)
