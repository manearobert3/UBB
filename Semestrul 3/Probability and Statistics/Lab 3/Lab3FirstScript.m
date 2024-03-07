clc
clear All

theInput=input("Select your model:Normal,Chi2,Student,Fisher\n","s");
alfa=input("Input alfa:\n");
beta=input("Input beta:\n");
switch theInput
    case "Normal"
        fprintf("Normal distribution model\n")
        mu=input("input mu");
        sigma=input("input sigma");
        a1=normcdf(0,mu,sigma);
        a2=1-a1;
        b1=normcdf(1,mu,sigma)-normcdf(-1,mu,sigma);
        b2=1-b1;
        Xalfa=norminv(alfa,mu,sigma);
        Xbeta=norminv(1-beta,mu,sigma);
    case "Student"
        fprintf("Student distribution model\n")
        studentM=input("n=");
        a1=tcdf(0,studentM);
        a2=1-a1;
        b1=tcdf(1,studentM)-tcdf(-1,studentM);
        b2=1-b1;
        Xalfa=tinv(alfa,studentM);
        Xbeta=tinv(1-beta,studentM);
    case "chi2"
        fprintf("chi2 distribution model\n")
        chi=("input chi2");
        a1=chi2cdf(0,chi);
        a2=1-chi2cdf(0,chi);
        b1=chi2cdf(1,chi)-chi2cdf(-1,chi);
        b2=1-b1;
        Xalfa=chi2inv(alfa,chi);
        Xbeta=chi2inv(1-beta,chi);
    case "Fisher"
        fprintf("Fisher distribution model\n")
        fisherM=input("m=");
        fisherN=input("n=");
        a1=fcdf(0,fisherM,fisherN);
        a2=1-a1;
        b1=fcdf(1,fisherM,fisherN)-fcdf(-1,fisherM,fisherN);
        b2=1-b1;
        Xalfa=finv(alfa,fisherM,fisherN);
        Xbeta=finv(1-beta,fisherM,fisherN);
    otherwise 
        fprintf("Not a valid model\n")
end
fprintf("P(X<=0)=%9.5f\n",a1)
fprintf("P(X>=0)=%9.5f\n",a2)
fprintf("P(-1<=X<=1)=%9.5f\n",b1)
fprintf("P(X<=-1 or X>=1)=%9.5f\n",b2)
fprintf("P(X<Xalfa)= P(X<=Xalfa)=alfa, Xalfa=%9.5f\n",Xalfa)
fprintf("P(X>Xbeta)= P(X>=Xbeta)=beta, Xbeta=%9.5f\n",Xbeta)