import numpy as np
import cvxpy as cp
import matplotlib.pyplot as plt


def problemsolve(n,arg):
  N=100
  X = np.linspace(-1,1,num = 2*N+1)
  X.shape = (2*N+1,1)
  A = cp.Variable((n,1))
  Y = np.zeros((n,2*N+1))

  for j in range(2*N+1):
    c=X[j]
    for i in range(n):
     Y[i][j]=c**i

  cost = (X**n-Y.T@A)
  k=sum(cost**2)
  j=cp.norm1(cost)

  if arg==0:
    Objective = cp.Minimize(k)
  else :
    Objective = cp.Minimize(j)
  
  prob = cp.Problem(Objective)  
  prob.solve()
  return Objective.value

lst=np.arange(1,21)
Y=[]
Y1=[]
for n in lst :
  y=problemsolve(n,0)
  y1=problemsolve(n,1)
  Y.append(y)
  Y1.append(y1)
  if n in [5,10,20]:
    print("l2 norm at",n,":",y)
    print("l1 norm at",n,":",y1)

plt.plot(lst,Y)
plt.title("L2 norm")
plt.show()

plt.plot(lst,Y1)
plt.title("L1 norm")
plt.show()