# Needed to use numpy functions and arrays
import numpy as np
import math
def get_input_samples(first_x, last_x, N):

    h = (last_x - first_x) / N
    return [first_x + i*h for i in range(N+1)]

def apply(f, inputs):
     # Here we apply f for all inputs
     return [f(x) for x in inputs]

def trapezium_rule(samples, h):
     # Apply trapezium rule to sample array equally spaced by h
     return (h/2) * (samples[0] + samples[-1] + 2 * sum(samples[1:-1]))

def estimate_area(f, a,b, N):
     # Estimate the derivative of a function between two points with trapezium rule
     inputs = get_input_samples(a, b, N)
     samples = apply(f, inputs)
     dx = (b - a)/N
     return trapezium_rule(samples, dx)

a=int(input("Input an a considering intervals of the form [-a,a], a="))
b=a
a=0-a
f=lambda x: math.e**(-x**2)
N=100 # Number of trapeziums
print(estimate_area(f, a, b, N))