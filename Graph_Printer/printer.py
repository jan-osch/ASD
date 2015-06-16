#!/Users/Janusz/anaconda/bin/python2

from __future__ import print_function
__author__ = "Janusz Grzesik"

import graphviz as gv
import argparse

def create_graph(parsed_arguments):
    number_of_nodes = parsed_arguments.number_of_nodes
    elements_of_matrix = parsed_arguments.Matrix.split(" ")

    if not parsed_arguments.l:
        labels = []
    else:
        labels = parsed_arguments.l.split(' ')

    if parsed_arguments.j:
        highlights = parsed_arguments.j.split(' ')
    else:
        highlights = range(len(elements_of_matrix))

    if parsed_arguments.d:
        graph = gv.Digraph()
    else:
        graph = gv.Graph()

    for y in range(number_of_nodes):
        graph.node(get_label(y,labels))
        for x in range(number_of_nodes):
            weight = int(elements_of_matrix [y * number_of_nodes + x])
            if ( weight != 0 ):

                if parsed_arguments.d:
                    if( highlights [y * number_of_nodes + x]=='+'):
                        if parsed_arguments.w:
                            #Weighted directional with highlights
                            graph.edge(get_label(y,labels), get_label(x,labels), label=str(weight), color ='red')
                        else:
                            #Non weighted directional with highlights
                            graph.edge(get_label(y,labels), get_label(x,labels), color ='red')
                    else:
                        if parsed_arguments.w:
                            #Weighted directional without highlights
                            graph.edge(get_label(y,labels), get_label(x,labels), label=str(weight))
                        else:
                            #Non weighted directional without highlights
                            graph.edge(get_label(y,labels), get_label(x,labels))

                else:
                    if int(elements_of_matrix [x * number_of_nodes + y]) != -1:
                        if parsed_arguments.w:
                            if ( highlights [y * number_of_nodes + x]=='+' or highlights [x * number_of_nodes + y] =='+'):
                                #Weighted non directional with highlights
                                graph.edge(get_label(y,labels), get_label(x,labels), label=str(weight), color ='red')
                            else:
                                #Weighted non directional without highlights
                                graph.edge(get_label(y,labels), get_label(x,labels), label=str(weight))
                            elements_of_matrix[y * number_of_nodes + x] =-1
                        else:
                            if( highlights [y * number_of_nodes + x]=='+' or highlights [x * number_of_nodes + y] =='+'):
                                #Non weighted non directional with highlights
                                graph.edge(get_label(y,labels), get_label(x,labels), color ='red')
                            else:
                                #Non weighted non directional without highlights
                                graph.edge(get_label(y,labels), get_label(x,labels))
                            elements_of_matrix[y * number_of_nodes + x] =-1
                            
    return graph

def print_graph(graph):
    graph.render('output.gv')

def get_label(index, labels):
    if not labels:
        return str(index)
    return labels[index]
    
def parse_arguments():
    parser = argparse.ArgumentParser(description='Process some integers.')
    parser.add_argument('number_of_nodes', metavar='N', type=int,
                   help='number of nodes')
    parser.add_argument('-w', action='store_true',
                    default=False,
                    help='build a weighted graph (default: non weighted)')
    parser.add_argument('-d', action='store_true',
                    default=False,
                    help='build a directional graph (default: undirected)')
    parser.add_argument('Matrix',  metavar="M",
                    help='Matrix od adjacency as continious space separated string')
    parser.add_argument('-l',  metavar="L",
                    help='labels as space continious separated string', default = False)
    parser.add_argument('-j',  metavar="J",
                    help='highlights as space continious separated string', default = False)


    args = parser.parse_args()
    return args

def main():
    arguments = parse_arguments()
    graph = create_graph(arguments)
    print_graph(graph)
    return 0

if __name__ == '__main__':
    main()
    