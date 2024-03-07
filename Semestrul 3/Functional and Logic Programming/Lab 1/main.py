

def invert(list,L,R):
    if L>len(list) or R<0 or L>=R:
        return list
    aux=list[L]
    list[L]=list[R]
    list[R]=aux
    return invert(list,L+1,R-1)

lista=[1,2,3,4]
print(invert(lista,0,len(lista)-1))