def maximum(x,list,i):
    if i>len(list)-1:
        return x
    if(list[i]>x):
        x=list[i]
    return maximum(x,list,i+1)

lista=[2,565,34,25]
print(maximum(-999,lista,0))