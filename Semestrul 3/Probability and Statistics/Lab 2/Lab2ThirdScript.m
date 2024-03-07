clc
clf
clear All

n=3;
p=0.5;

k=[0:n];
s=input("input number of simulations");
X=rand(3,s) > 0.5;
Y=sum(X)
hist(Y)