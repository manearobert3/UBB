import numpy as np
import matplotlib.pyplot as plt

def gradient_descent(gradient, start, learn_rate, n_iter):
    vector = start
    for _ in range(n_iter):
        diff = -learn_rate * gradient(vector)

        vector += diff
        y.append(vector)
    return vector

#The function f is x-log(x), the gradient of this function is 1-1/x
#First we get a result that is close to 0
y=[]
gradient_descent(lambda x: 1 - 1 / x, start=2.5, learn_rate=0.5,n_iter=10)
plt.plot(y, linewidth=2,marker='o')
plt.show()
#After that we increase the learn rate and it gets to 0 faster
y=[]
gradient_descent(lambda x: 1 - 1 / x, start=2.5, learn_rate=0.8,n_iter=10)
plt.plot(y, linewidth=2,marker='o')
plt.show()
#After that we increase the learn rate even more and it can lead to divergence
y=[]
gradient_descent(lambda x: 1 - 1 / x, start=2.5, learn_rate=5,n_iter=10)
plt.plot(y, linewidth=2,marker='o')
plt.show()


