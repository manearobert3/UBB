clc
clear ALL

X = [7,7,4,5,9,9,4,12,8,1,8,7,3,13,2,1,17,7,12,5,6,2,1,13,14,10,2,4,9,11,3,5,12,6,10,7]
n= length (X)
sigma= 5
confLevel= input("What is the confidence level?")
Xbar = mean(X)
sqrtLen= sqrt(n)
alfa = 1-confLevel
w=norminv(1-alfa/2)
w2=norminv(alfa/2)
tl=Xbar-sigma/sqrtLen*w;
tu=Xbar-sigma/sqrtLen*w2;
fprintf("a) The %2.0f%% confidence interval for the mean is (%5.3f,%5.3f)\n",confLevel*100,tl,tu)

s=std(X);
t1=Xbar-s/sqrtLen*tinv(1-alfa/2,n-1)
t2=Xbar-s/sqrtLen*tinv(alfa/2,n-1)

fprintf("a) The %2.0f%% confidence interval for the mean is (%5.3f,%5.3f)\n",confLevel*100,t1,t2)

% c)

chi2_1=chi2inv(1-alfa/2,n-1);
chi2_2=chi2inv(alfa/2,n-1);
t3=(((n-1)*var(X))/chi2_1)
t4=(((n-1)*var(X))/chi2_2)
t5=sqrt(t3)
t6=sqrt(t4)



