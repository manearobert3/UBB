from random import *
import copy
from heapq import heappush, heappop
from itertools import combinations
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
            self.__Inbound[x].append(y)
            self.__Outbound[y].append(x)
            self.__Costs[(x,y)]=c
            self.__Costs[(y, x)] = c
        else:
            raise NewError()

    def modifyCost(self, x, y, c):
        if self.isEdge(x,y):
            self.__Costs[(x,y)]=c
            self.__Costs[(y, x)] = c
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
                if(p!=v):
                    del self.__Costs[(v,p)]
                    self.__Inbound[p].remove(v)

            for p in self.Inbound_of_vertex(v):
                if (p != v):
                    del self.__Costs[(p,v)]
                    self.__Outbound[p].remove(v)
                else:
                    del self.__Costs[(v,v)]
                    self.__Inbound[v].remove(v)

            del self.__Outbound[v]
            del self.__Inbound[v]
        else:
            raise NewError()

    def numberOfEdges(self):
        return len(self.__Costs)

    def numberOfVertices(self):
        return len(self.__Inbound)
    def bfsOfgraphConnectedComp(self):
        bfs=[]
        visited=[False]*self.numberOfVertices()
        for i in range(self.numberOfVertices()):
            if visited[i]==False:
                queue=[]
                visited[i]=True
                queue.append(i)
                list=[]
                list.append(i)
                while(len(queue)>0):
                    node=queue.pop(0)
                    if(visited[node]==False):
                        list.append(node)
                    for index in self.Inbound_of_vertex(node):
                        if(visited[index]==False):
                            visited[index]=True
                            list.append(index)
                            queue.append(index)
                if (len(list) != 0):
                    bfs.append(list)
        return bfs


def find_maximum_clique(graph):
    vertices = graph.parseKeys()
    max_clique = []

    # Generate all possible subsets of vertices
    subsets = []
    for r in range(1, len(vertices) + 1):
        subsets.extend(combinations(vertices, r))

    # Check each subset if it forms a clique
    for subset in subsets:
        is_clique = True
        for i in range(len(subset)):
            for j in range(i + 1, len(subset)):
                if not graph.isEdge(subset[i], subset[j]):
                    is_clique = False
                    break
            if not is_clique:
                break
        if is_clique and len(subset) > len(max_clique):
            max_clique = subset

    return max_clique



def prim(graph, start_vertex):
    visited = {start_vertex}
    edges = []
    current_node = start_vertex
    selected_edges = []
    while len(visited) < graph.numberOfVertices():
        for neighbor in graph.Outbound_of_vertex(current_node):
            weight = graph.Costs_of_vertices(current_node, neighbor)
            if neighbor not in visited:
                heappush(edges, (weight, current_node, neighbor))

        while edges:
            weight, u, v = heappop(edges)
            if v not in visited:
                visited.add(v)
                #print("Selected edge:", u, "->", v, "Weight:", weight)
                selected_edges.append((u, v, weight))
                current_node = v
                break
    return selected_edges


def returnGraphFromList(list,graph):
    for k in range (len(list)):
        graphtest=copy.deepcopy(graph)
        for i in list:
            if(list[k]!=i):
                for j in i:
                    graphtest.removeVertex(j)
        print("graph number ",k," ")
        graphtest.printGraph()

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
            i += 2
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