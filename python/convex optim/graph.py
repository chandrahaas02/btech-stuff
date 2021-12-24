from matplotlib import pyplot as plt

x=[5,10,15,20,25,30]

x1 = [2.84,6.76,11.1467,14.795,19.856,23.320]
x2 =[2.56,7.28,11.4860,15.225,19.556,24.100]
x3 =[2.96,7.88,12.8476,17.125,22.976,27.967]




y1 = [16,35,53,103,132,149]
y2 = [11,22,56,94,146,135]
y3 = [4,10,15,20,25,30]
plt.plot(x,y1)
plt.plot(x,y2)
plt.plot(x,y3)
plt.legend(["TAS", "CAS","BOUNDCAS"])
plt.xlabel("no of threads")
plt.ylabel("worst waiting time")
plt.savefig("worst.png")

