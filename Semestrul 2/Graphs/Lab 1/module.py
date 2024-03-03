from random import *
class NewError(Exception):
    pass
class Graph():
    def __init__(self,n):
        self.__Inbound = {}
        self.__Outbound = {}
        self.__Costs = {}
        for i in range(n):
            self.__Inbound[i] = []
            self.__Outbound[i] = []

    def parseKeys(self):
        return list(self.__Outbound.keys())

    def parseCosts(self):
        return list(self.__Costs.keys())

    def parsedCosts(self):
        return self.__Costs

    def InboundDict(self):
        return self.__Inbound

    def OutboundDict(self):
        return self.__Outbound

    def Inbound_of_vertex(self, v):
        return self.__Inbound[v]

    def Outbound_of_vertex(self, v):
        return self.__Outbound[v]

    def Costs_of_vertices(self, x, y):
        return self.__Costs[(x, y)]

    def isVertex(self,v):
        vertices=self.parseKeys()
        return v in vertices

    def isEdge(self,x,y):
        return y in self.__Outbound[x]

    def saveFile(self, filename):
        f = open(filename, 'w')
        costs = self.parsedCosts()
        edges = self.parseCosts()
        for index in edges:
            line = str(index[0]) + ' ' + str(index[1]) + ' ' + str(costs[index])
            f.write(line)
            f.write('\n')
        f.write('\n')
        f.close()

    def printGraph(self):
        costs = self.parsedCosts()
        edges = self.parseCosts()
        for index in edges:
            line = str(index[0]) + ' ' + str(index[1]) + ' ' + str(costs[index])
            print(line)

    def addEdge(self,x,y,c):
        if not self.isEdge(x,y):
            self.__Inbound[y].append(x)
            self.__Outbound[x].append(y)
            self.__Costs[(x,y)]=c
        else:
            raise NewError()

    def modifyCost(self, x, y, c):
        if self.isEdge(x,y):
            self.__Costs[(x,y)]=c
        else:
            raise ValueError

    def addVertex(self,v):
        if not self.isVertex(v):
            self.__Inbound[v] = []
            self.__Outbound[v] = []
        else:
            raise ValueError

    def removeEdge(self,x,y):
        if self.isEdge(x,y):
            del self.__Costs[(x,y)]
            self.__Outbound[x].remove(y)
            self.__Inbound[y].remove(x)
        else:
            raise ValueError

    def removeVertex(self,v):
        if self.isVertex(v):
            for p in self.Outbound_of_vertex(v):
                del self.__Costs[(v,p)]
                self.__Inbound[p].remove(v)

            for p in self.Inbound_of_vertex(v):
                del self.__Costs[(p,v)]
                self.__Outbound[p].remove(v)
            del self.__Outbound[v]
            del self.__Inbound[v]
        else:
            raise NewError()

    def numberOfEdges(self):
        return len(self.__Costs)

    def numberOfVertices(self):
        return len(self.__Inbound)


def CreateRandom(n,m,graph,filename):
    if m > n * n:
        f = open(filename, 'w')
        f.write("Graph can't be made")
        return
    i = 0
    while i < m:
        x = randrange(0, n)
        y = randrange(0, n)
        c = randint(0, 3500)
        if not graph.isEdge(x, y):
            graph.addEdge(x, y, c)
            i += 1
        graph.saveFile(filename)

def readFromFile(n,m,graph,filename):
        f = open(filename, 'r')
        line = f.readline()
        for i in range(m):
            line=f.readline()
            line=line.strip().split(" ")
            x=int(line[0])
            y=int(line[1])
            c=int(line[2])
            try:
                graph.addEdge(x,y,c)
            except:
                continue
        f.close()
        return graph