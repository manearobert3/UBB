clc
clf
clear ALL
p=123;
while (p<0.05) || (p>0.95)
    p=input("input p (where 0.05<=p<=0.95):\n");
end

for n=1:100
    mu=n*p;
    sigma=sqrt(n*p*(1-p));
    k=[0:n];
    a=binopdf(k,n,p);
    plot(k,a)
    hold on
    b=normpdf(k,mu,sigma);

    plot(k,b)
    title("n="+n);
    legend("binopdf","normpdf");
    hold off
    pause(0.5);

end
