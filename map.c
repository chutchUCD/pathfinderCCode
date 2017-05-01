/*
 * map.c
 *
 *  Created on: Apr 29, 2017
 *      Author: admin
 */

#include "map.h"
#include <stdio.h>


typedef char bool;

struct car {
	dir direction;
};

//returns a valid index for a path or a number less than zero.
//check to make sure that the index returned is greater than 0
int pathOpen(const int path){
		return path-1;
}

void openNodes(struct GRAPHHEAD* g){
	for (int i = 0; i < g->vertex_count; i++){
		openNode(g, i);
	}
}

void openNode(struct GRAPHHEAD* g, int node){
	g->vertices[node].visited = C;
}

void grayNode (struct GRAPHHEAD g, int node){
	g.vertices[node].visited = G;
}

void blackNode (struct GRAPHHEAD g, int node){
	g.vertices[node].visited = B;
}

int countAt(struct GRAPHHEAD g, int i){
	int n = pathOpen(i);
	if(n == -1){
		return -1;
	} else{
		int count = 0;
		if (g.vertices[n].north > 0){++count;}
		if (g.vertices[n].south > 0){++count;}
		if (g.vertices[n].east > 0){++count;}
		if (g.vertices[n].west > 0){++count;}
		return count;
	}
}

void countEdges (struct GRAPHHEAD *g){
	int count = 0;
	for (int i = 0; i< g->vertex_count; i++){
		if (g->vertices[i].north > 0){++count;}
		if (g->vertices[i].south > 0){++count;}
		if (g->vertices[i].east > 0){++count;}
		if (g->vertices[i].west > 0){++count;}
	}
	g->edge_count=count;
}


void clearWeight(struct GRAPHHEAD* g, int node){
	g->vertices[node].wn=0;
	g->vertices[node].ws=0;
	g->vertices[node].we=0;
	g->vertices[node].ww=0;
}

void clearWeights(struct GRAPHHEAD* g){
	for (int i = 0; i< g->vertex_count;i++){
		g->vertices[i].wn=0;
		g->vertices[i].ws=0;
		g->vertices[i].we=0;
		g->vertices[i].ww=0;
	}
}

void setWeight(graph g, vertex node, dir heading, char weight){
	//if this graph node has already been visited return
	if (node->visited==B){return;}
	//set the graph to be B, indicating that it has been visited.
	node->visited=B;
	//if the vertice has a visitable location that is not blackened (the paths have not already been calculated for that edge):
	if (node->north){
		if (heading==N){
			node->wn = 1 + weight;
		} else if (heading == S){
			node->wn = 3 + weight;
		} else {
			node->wn = 2 + weight;
		}
	}
	if (node->south){
		if (heading==S){
			node->ws = 1 + weight;
		} else if (heading == N){
			node->ws = 3 + weight;
		} else {
			node->ws = 2 + weight;
		}
	}
	if (node->east){
		if (heading==E){
			node->we = 1 + weight;
		} else if (heading == W){
			node->we = 3 + weight;
		} else {
			node->we = 2 + weight;
		}
		}
	if (node->west){
		if (heading==W){
			node->ww = 1 + weight;
		} else if (heading == E){
			node->ww = 3 + weight;
		} else {
			node->ww = 2 + weight;
		}
	}
}

//takes a pointer to the map and the node to start weighting the graph from.
void setWeights (graph g, int node, dir initial_heading){
	int dbgcount = 0;
	//make sure all nodes are white.
	openNodes(g);
	vertex queue[g->vertex_count];
	int qsize=1;
	queue[0]= &(g->vertices[node]);
	//heading queue
	dir hqueue[g->vertex_count];
	hqueue[0]=initial_heading;
	//shares qsize with queue
	char weights[g->vertex_count];
	weights[0]=0;
	queue[0]->visited=G;
	printf("Here\n");
	while(qsize > 0){
		printf("%i,%i,%i,%i\n", queue[0]->north, queue[0]->south, queue[0]->east, queue[0]->west);
		setWeight(g, queue[0], hqueue[0], weights[0]);
		dbgcount++;
		for(int i=1; i < qsize; i++){
			queue[i-1]=queue[i];
			hqueue[i-1]=hqueue[i];
			weights[i-1]=weights[i];
		}
		--qsize;
		//set the queues to be the first found instances of clear nodes.
		//if it is either a g or a b node, will not update.
		//otherwise, sets the initial heading into the node, the weight added to that node.
		if(queue[0]->north && g->vertices[(int)queue[0]->north - 1].visited == C){
			queue[qsize]= &(g->vertices[(int)queue[0]->north - 1]);
			g->vertices[(int)queue[0]->north - 1].visited = G;
			hqueue[qsize] = g->vertices[(int)queue[0]->north - 1].enternorth;
			weights[qsize]=weights[0]+1;
			qsize++;
		}

		if(queue[0]->south && g->vertices[(int)queue[0]->south - 1].visited == C){
			queue[qsize]= &(g->vertices[(int)queue[0]->south - 1]);
			g->vertices[(int)queue[0]->south - 1].visited = G;
			hqueue[qsize] = g->vertices[(int)queue[0]->south - 1].entersouth;
			weights[qsize]=weights[0]+1;
			qsize++;
		}

		if(queue[0]->east && g->vertices[(int)queue[0]->east - 1].visited == C){
			queue[qsize]= &(g->vertices[(int)queue[0]->east - 1]);
			g->vertices[(int)queue[0]->east - 1].visited = G;
			hqueue[qsize] = g->vertices[(int)queue[0]->east - 1].entereast;
			weights[qsize]=weights[0]+1;
			qsize++;
		}

		if(queue[0]->west && g->vertices[(int)queue[0]->west - 1].visited == C){
			queue[qsize]= &(g->vertices[(int)queue[0]->west - 1]);
			g->vertices[(int)queue[0]->west - 1].visited = G;
			hqueue[qsize] = g->vertices[(int)queue[0]->west - 1].enterwest;
			weights[qsize]=weights[0]+1;
			qsize++;
		}

	}
	printf("dbgcnt: %i", dbgcount);
}
