clc;
clear all;

p=123;
while (p<=0) || (p>=1)
    p=input("input p (where 0<p<1):\n");
end

s=input("input number of simulations");
n=input("input number of trials");
U=rand(1,s)
X= U<p
U_X= unique(X)
n_X=hist(X,length(U_X))
[U_X;n_X]
relfreq=n_X/s
[U_X,relfreq]
plot(U_X,relfreq)
title("a");
%U=rand(n);
%X=sum(U<p);
%U_X=unique(X);
%relfreq=n_X/s;
%a=binopdf(0,n)
%plot(U_X,relfreq,'*')
