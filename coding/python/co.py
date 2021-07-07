import cvxpy as cp
import numpy as np
import math
from matplotlib import pyplot as plt

n=100
h=cp.Variable((n,1))
e=np.empty((n,1))
D1=0.08
D2=0.025
D3=0.005
for i in range(n):
  e[i]=5*(math.sin((i*3*(math.pi))/n))+math.sin((i*10*(math.pi)/n))
e.reshape(n,1)

constraints=[]
for i in range(1,n,1):
  constraints+=[cp.abs(h[i]-h[i-1])<=0.08]
  if(i>1):
    constraints+=[cp.abs(h[i]-2*h[i-1]+h[i-2])<=0.025]
  if(i>2):
    constraints+=[cp.abs(h[i]-3*h[i-1]+3*h[i-2]-h[i-3])<=0.005]


k1=cp.scalene(h-e,1,0)
k2=cp.scalene(e-h,1,0)

c=(2*cp.square(k1))+(12*cp.square(k2))+(30*k1)+k2
Cost=cp.sum(c)

Objective=cp.Minimize(Cost)
Prob=cp.Problem(Objective,constraints)
Prob.solve(solver=cp.ECOS)

print(Cost.value)


x=np.linspace(0,100,100)
plt.plot(x,h.value)
plt.plot(x,e)
plt.plot(x,h.value-e)
plt.legend(["h", "e","h-e"])
plt.show()

x=np.linspace(1,10,100)
y=12*x*x+x
plt.plot(x,y)
plt.show()