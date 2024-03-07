p=linspace(0,3);
y=p.^5/10;
z=p.*sin(p);
t=cos(p);
plot(p,y,'--',p,z,'r',p,t)
title("First Plot")
legend("x^5/10","x*sin(x)","cos(x)")