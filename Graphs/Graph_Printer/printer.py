#!/Users/Janusz/anaconda/bin/python2

__author__ = "Janusz Grzesik"

from __future__ import print_function

import graphviz as gv
import argparse

def create_weighted_graph(parsed_arguments):
    number_of_nodes = parsed_arguments.number_of_nodes
    elements_of_matrix = parsed_arguments.Matrix.split(" ")

    if not parsed_arguments.l:
        labels = []
    else:
        labels = parsed_arguments.l.split(' ')

    if parsed_arguments.d:
        graph = gv.Digraph()
    else:
        graph = gv.Graph()

    for y in range(number_of_nodes):
        for x in range(number_of_nodes):
            weight = elements_of_matrix [y * number_of_nodes + x]
            if ( weight != 0):
                if parsed_arguments.d:
                    graph.edge(get_label(y,labels), get_label(x,labels), label=weight)
                elif elements_of_matrix [x * number_of_nodes + y] != -1: 
                    graph.edge(get_label(y,labels), get_label(x,labels), label=weight)
                    elements_of_matrix[y * number_of_nodes + x] =-1
    
    return graph

def create_non_weighted_graph(parsed_arguments):
    number_of_nodes = parsed_arguments.number_of_nodes
    elements_of_matrix = parsed_arguments.Matrix.split(' ')
    
    if not parsed_arguments.l:
        labels = []
    else:
        labels = parsed_arguments.l.split(' ')

    if parsed_arguments.d:
        graph = gv.Digraph()
    else:
        graph = gv.Graph()

    for y in range(number_of_nodes):
        for x in range(number_of_nodes):
            weight = elements_of_matrix [y * number_of_nodes + x]
            if ( weight != 0):
                if parsed_arguments.d:
                    graph.edge(get_label(y,labels), get_label(x,labels))
                elif elements_of_matrix [x * number_of_nodes + y] != -1: 
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

    args = parser.parse_args()
    return args

def main():
    arguments = parse_arguments()
    if arguments.w:
        graph = create_weighted_graph(arguments)
    else:
        graph = create_non_weighted_graph(arguments)
    print_graph(graph)
    return 0

if __name__ == '__main__':
    main()
    