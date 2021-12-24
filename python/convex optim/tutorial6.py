import cvxpy as cp
import numpy as np

#let x1 be number of days of production for ipods
X= cp.Variable((3,1))
A = np.array([[6000,0,0],[0,5000,0],[0,0,3000]])

#number of ipods,ipads,iphones
N = A@X

space = np.array([4/100,45/1000,21/100])
space.shape = (3,1)
S = space.T@N

Min= np.array([5000,0,4000])
Min.shape = (3,1)

Max= np.array([10000,15000,8000])
Max.shape = (3,1)

P = np.array([4,6,10])
P.shape = (3,1)
cost = P.T@N


Objective = cp.Maximize(cost)
Constraints = [S<=6000,N>=Min,N<=Max,X>=0,sum(X)<=5]
prob = cp.Problem(Objective,Constraints)
prob.solve()

print(Objective.value)
print(X.value)