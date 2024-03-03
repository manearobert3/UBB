
import copy


from module import *


def print_menu():
    print("0.Check if exists vertex")
    print("1.number of vertices")
    print("2.parse the set of vertices")
    print("3.give two vertices and find if there is an edge")
    print("4.get in + out degree of vertex")
    print("5.parse the set of outbound edges of a specified vertex ")
    print("6.parse the set of inbound edges of a specified vertex")
    print("7.retrieve or modify the information attached to a specified edge")
    print("8.add edge")
    print("9.remove edge")
    print("10.add vertex")
    print("11.remove vertex")
    print("12.print graph")
    print("13.copy graph")
    print("14.number of edges")
    print("15.save graph to file")
    print("16.read graph from file")
    print("17.save random graph to file")
    print("18.exit")


graph1=Graph(10)
CreateRandom(7, 20, graph1, "random_graph1.txt")
CreateRandom(6, 40, graph1, "random_graph2.txt")
while(1):
    print_menu()
    option = input("input Option")
    if(option == '1'):
        print(graph1.numberOfVertices())
    elif (option=='2'):
        for x in graph1.parseKeys():
            print (x)
    elif(option=='0'):
        try:
            print(graph1.isVertex(int(input("Input vertex:"))))
        except ValueError:
            print("Invalid Command")
    elif(option=='3'):
        try:
            print(graph1.isEdge(int(input("give vertex")),int(input("give vertex"))))
        except ValueError:
            print("Invalid Command")
    elif(option=='4'):
        try:
            print("Inbound degree of vertex",len(graph1.Inbound_of_vertex(int(input("give vertex")))))
            print("Outbound degree of vertex",len(graph1.Outbound_of_vertex(int(input("give vertex")))))
        except ValueError:
            print("Invalid Command")
    elif (option == '5'):
        try:
            for v in graph1.Inbound_of_vertex(int(input("give vertex"))):
                print(v)
        except ValueError:
            print("Invalid Command")
    elif (option == '6'):
        try:
            for v in graph1.Outbound_of_vertex(int(input("give vertex"))):
                print(v)
        except ValueError:
            print("Invalid Command")
    elif(option=='7'):
        option2=input("1.Retrieve cost or 2.Modify Cost")
        if(option2=='1'):
            try:
                a = int(input("give vertex"))
                b = int(input("give vertex"))
                print(graph1.Costs_of_vertices(a, b))
            except ValueError:
                print("Invalid Command")
        elif(option2=='2'):
            try:
                a = int(input("give vertex"))
                b = int(input("give vertex"))
                c = int(input("give cost"))
                graph1.modifyCost(a, b, c)
            except ValueError:
                print("Invalid Command")
        else:
            print("Invalid Command")

    elif(option=='8'):
        try:
            a = int(input("give vertex"))
            b = int(input("give vertex"))
            c = int(input("give cost"))
            graph1.addEdge(a,b,c)
        except KeyError:
            print("Invalid Edge")
        except ValueError:
            print("Invalid Command")
    elif(option=='9'):
        try:
            a = int(input("give vertex"))
            b = int(input("give vertex"))
            graph1.removeEdge(a,b)
        except KeyError:
            print("Invalid Vertex")
        except ValueError:
            print("Invalid Command")
    elif (option == '10'):
        try:
            a = int(input("give vertex"))
            graph1.addVertex(a)
        except ValueError:
            print("The vertex already exists")
    elif (option == '11'):
        try:
            a = int(input("give vertex"))
            graph1.removeVertex(a)
        except NewError:
            print("Invalid Vertex")
    elif (option == '12'):
        graph1.printGraph()
    elif (option == '14'):
        print(graph1.numberOfEdges())
    elif (option == '15'):
        graph1.saveFile("output.txt")
    elif (option == '16'):
        option3=input("input file name")
        f = open(option3, 'r')
        line = f.readline()
        line = line.strip().split(" ")
        n = int(line[0])
        m = int(line[1])
        graph1 = Graph(n)
        graph1=readFromFile(n,m,graph1,option3)
    elif (option == '17'):
        try:
            n=int(input("input number of vertices"))
            m=int(input("input number of edges"))
            if m >= n * (n - 1):
                print("not valid numbers")
            else:
                randomGraph = CreateRandom(n, m, graph1, "random.txt")

        except ValueError:
            print("not valid  number")
    elif(option=='13'):
        copiedGraph=copy.deepcopy(graph1)
        copiedGraph.saveFile("copied.txt")
    elif (option == '18'):
        exit()


