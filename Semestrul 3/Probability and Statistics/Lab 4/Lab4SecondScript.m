clc
clf
clear ALL


p=123;
while (p<=0) || (p>=1)
    p=input("input p (where 0<p<1):\n");
end

s=input("input number of simulations");
X=zeros(1,s)
for i=1:s
    c=0;
   while(true)
       randomnumber=rand()
        randomnumber=randomnumber<p
       if(randomnumber==0)
           c=c+1;
       else
           break;
       end
   end
   X(i)=c;
end
U_X= unique(X)
n_X=hist(X,length(U_X))
[U_X;n_X]
relfreq=n_X/s
[U_X,relfreq]
a=geopdf(U_X,s);
plot(s,a)