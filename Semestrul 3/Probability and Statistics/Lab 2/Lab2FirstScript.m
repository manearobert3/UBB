clc
clf
clear All

n=input("input number of trials");
p=input("input probability of success");

k=[0:n];
xx=0:0.1:n;
px=binopdf(k,n,p);
plot(k,px,'o')
hold on
title("Probability Plot")

py=binocdf(xx,n,p);
plot(xx,py,'--')
legend("pdf","cdf")
hold off
