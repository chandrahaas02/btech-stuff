import matplotlib.pyplot as plt
from expense_stream_data import *
import cvxpy as cp


#intialize
ones=np.ones([m,1])
x=cp.Variable((29,1))
b=cp.Variable((36,1))
w=cp.Variable((36,1))

#objective
objective=cp.Minimize(b[0]+(ones.T)@x)

#constraints
constraints=[x>=0,b>=0,w + P@x== e]
constraints +=[(b[t+1]==(1+rho)*b[t]-w[t]) for t in range(35)]

#probsolve
prob=cp.Problem(objective,constraints)
prob.solve()
print(objective.value)
#plotting the value
t=np.arange(0,36)

fig1=plt.subplot(1,3,1)
fig1.plot(t,e)
fig1.set_title("expenditure")

fig2=plt.subplot(1,3,2)
for i in range(m):
    fig2.plot(t,P[:,i]*x[i].value)
fig2.set_title("payouts for each one")

fig3=plt.subplot(1,3,3)
fig3.plot(t,b.value)
fig3.set_title("bank balance")

plt.show()
