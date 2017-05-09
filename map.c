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

void openNode(struct GRAPHHEAD* g, char node){
	g->vertices[(int)node].visited = C;
}

void grayNode (struct GRAPHHEAD *g, char node){
	g->vertices[(int)node].visited = G;
}

void blackNode (struct GRAPHHEAD *g, char node){
	g->vertices[(int)node].visited = B;
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
	queue[0]= &(g->vertices[node-1]);
	queue[0]->visited=G;
    //heading queue
	dir hqueue[g->vertex_count];
	hqueue[0]=initial_heading;
	//shares qsize with queue
	char weights[g->vertex_count];
	weights[0]=0;
	while(qsize >= 1){		
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
			g->vertices[(int)queue[0]->north - 1].visited = G;
            queue[qsize]= &(g->vertices[(int)queue[0]->north - 1]);
			hqueue[qsize] = g->vertices[(int)queue[0]->north - 1].enternorth;
			weights[qsize]=weights[0]+1;
			qsize++;
		}



		if(queue[0]->south && g->vertices[(int)queue[0]->south - 1].visited == C){
			g->vertices[(int)queue[0]->south - 1].visited = G;
            queue[qsize]= &( g->vertices[(int)queue[0]->south - 1] );
			hqueue[qsize] = g->vertices[(int)queue[0]->south - 1].entersouth;
			weights[qsize]=weights[0]+1;
			qsize = qsize + 1;
		}



		if(queue[0]->east && g->vertices[(int)queue[0]->east - 1].visited == C){
			g->vertices[(int)queue[0]->east - 1].visited = G;
			queue[qsize]= &(g->vertices[(int)queue[0]->east - 1]);
			hqueue[qsize] = g->vertices[(int)queue[0]->east - 1].entereast;
			weights[qsize]=weights[0]+1;
			qsize++;
		}


		if(queue[0]->west && g->vertices[(int)queue[0]->west - 1].visited == C){
			g->vertices[(int)queue[0]->west - 1].visited = G;
			queue[qsize]= &(g->vertices[(int)queue[0]->west - 1]);
			hqueue[qsize] = g->vertices[(int)queue[0]->west - 1].enterwest;
			weights[qsize]=weights[0]+1;
			qsize++;
		}
	}
}
/*
//insertion sort of PathData.
//most node lists we are going to deal with are short enough that this is efficient.
//expects the size of the array it is sorting and a pointer to the array.
void sortPathData(struct PATHDATA data[], int sz){
	//safety check
	if(sz < 1){
		return;
	}

	int i,j=0;
	int itersize = sz;
	struct PATHDATA swapper;
	while (i < itersize){
		j=sz-1;
		while (j > i){
			//if the wieghts change, swap data
			if (data[j].cost < data[i].cost){
				swapper.cost = data[j].cost;
				swapper.facing = data[j].facing;
				swapper.vertex = data[j].vertex;

				data[j].cost = data[i].cost;
				data[j].facing = data[i].facing;
				data[j].vertex = data[i].vertex;

				data[i].cost = swapper.cost;
				data[i].facing = swapper.facing;
				data[i].vertex = swapper.vertex;
			}
			--j;
		}
		++i;
	}
}
//takes a pointer to a graph, a node
//and a node to be excluded from consideration.
char cheapestPath(graph g, char node, char exclude){
	struct PATHDATA pos[4];
	int sz = 0;
	vertex v = &g->vertices[(int)node];
	if (v->north && g->vertices[v->north-1].visited==C){
		++sz;
		pos[sz-1].cost = v->wn;
		pos[sz-1].facing = v->enternorth;
		pos[sz-1].vertex = v->north;
	}
	if (v->south && g->vertices[v->south-1].visited==C){
		++sz;
		pos[sz-1].cost = v->ws;
		pos[sz-1].facing = v->entersouth;
		pos[sz-1].vertex = v->south;
	}
	if (v->east && g->vertices[v->east-1].visited==C){
		++sz;
		pos[sz-1].cost = v->we;
		pos[sz-1].facing = v->entereast;
		pos[sz-1].vertex = v->east;
	}
	if (v->west && g->vertices[v->west-1].visited==C){
		++sz;
		pos[sz-1].cost = v->ww;
		pos[sz-1].facing = v->enternorth;
		pos[sz-1].vertex = v->west;
	}
        
	if (sz>1){
		sortPathData(pos, sz);
        if (exclude && exclude == pos[0].vertex){
            return pos[1].vertex;
        }
        for (int i = 0; i < sz; i++){
            printf("c - %i\n", pos[i].vertex);
        }
		return pos[0].vertex;
	} else if (sz==1){
        if (exclude && exclude ==pos[0].vertex){
            return 0;
            }
        for (int i = 0; i < sz; i++){
        printf("c - %i\n", pos[i].vertex);
    }
		return pos[0].vertex;
	} else{
		return 0;
	}
}

void setPath(path p, graph g, char at, char next){
    p->vertex = next;
    if (next == g->vertices[(int)at-1].north){
        p->facing = g->vertices[(int)at-1].enternorth;
        p->cost = g->vertices[(int)at - 1].wn + (p-1)->cost;
        return;
    }
    if (next == g->vertices[(int)at-1].south){
        p->facing = g->vertices[(int)at-1].entersouth;
        p->cost = g->vertices[(int)at - 1].ws +(p-1)->cost;
        return;
    }
    if (next == g->vertices[(int)at-1].east){
        p->facing = g->vertices[(int)at-1].entereast;
        p->cost = g->vertices[(int)at - 1].we + (p-1)->cost;
        return;
    }
    if (next == g->vertices[(int)at-1].west){
        p->facing = g->vertices[(int)at-1].enterwest;
        p->cost = g->vertices[(int)at - 1].ww + (p-1)->cost;
        return;
    }
}*/
/*
char allExitsBlack(graph g, char n, char endNode){
    char rt = 1;
    //see if g .vertices north has been visited.
    if (g->vertices[ n-1 ].north){
        rt = g->vertices[g->vertices[ n-1 ].north - 1].visited == B 
            && g->vertices[ n-1 ].north == endNode;
    }
    if (g->vertices[ n-1 ].south){
        rt = rt && g->vertices[g->vertices[ n-1 ].south - 1].visited == B
        && g->vertices[ n-1 ].south == endNode;
    }
    if (g->vertices[ n-1 ].east){
        rt = rt && g->vertices[g->vertices[ n-1 ].east - 1].visited == B
        && g->vertices[ n-1 ].east == endNode;
    }
    if (g->vertices[ n-1 ].west){
        rt = rt && g->vertices[g->vertices[ n-1 ].west - 1].visited == B
        && g->vertices[ n-1 ].west == endNode;
    }
    return rt;
}*/
/*
char checkNoExits(graph g, char n){
    char rt = 1;
    //see if g .vertices north has been has a clear node
    //and that clear node is not the last node we came from
    //if such a node exits there is a clear node to exit into.
    if (g->vertices[ n-1 ].north){
        rt = g->vertices[g->vertices[ n-1 ].north - 1].visited != C;
            //&& g->vertices[ n-1 ].north == lastNode;
    }
    if (g->vertices[ n-1 ].south){
        rt = rt && g->vertices[g->vertices[ n-1 ].south - 1].visited != C;
        //&& g->vertices[ n-1 ].south != lastNode;
    }
    if (g->vertices[ n-1 ].east){
        rt = rt && g->vertices[g->vertices[ n-1 ].east - 1].visited != C;
        //&& g->vertices[ n-1 ].east != lastNode;
    }
    if (g->vertices[ n-1 ].west){
        rt = rt && g->vertices[g->vertices[ n-1 ].west - 1].visited != C;
        //&& g->vertices[ n-1 ].west != lastNode;
    }
    return rt;
    }

void findPath(graph g, char startNode, char endNode, dir initial_dir, char* rpath){
	//sanity check
	
    if (! (endNode && startNode) ){
        printf("s!\n");
		return;
	}
    //set up a character m and n
	char n, m, found = 0;
    //set up path data and relaxed path
	struct PATHDATA initialPath[g->vertex_count + 1];
	struct PATHDATA relaxPath[g->vertex_count + 1];
	//the size of each array is stored separately.
    int szip = 1;
	//and he relaxed path array is initialized her to zero.
    int szrp,i = 0;
    //n is the start node
    n = startNode;
    //the initial paths first element is initialized here.
	initialPath[0].vertex = startNode;
	initialPath[0].facing = initial_dir;
	initialPath[0].cost = 0;
    //the initial path is set to gray
	g->vertices[ (int)(startNode-1) ].visited = G;
	//using flag found for now
    fprintf(stdout,"Here2");
    int dbg = 0;
    while( n != endNode  ){

        //get the next node label into m
        m = cheapestPath(g, n - 1, 0);
        //if m exists, increase the size of m, set it's statistics and 
        //gray the node at it's location. Move the path n onto it.
        if(m){
            ++szip;
            //set the path in the array to be the next node in the sequence.
            setPath(&initialPath[szip-1], g, n, m);
            grayNode(g, (int)m-1);
            //
            n=m;
        }

        //~ //if n is the end node, copy it into the relaxed path
        //~ if (n==endNode){
            //~ //if the relax path is not filled copy it
            //~ if(!szrp || initialPath[szrp-1].cost < relaxPath[szrp-1].cost){
                //~ for (i = 0; i < szip; i++){
                    //~ relaxPath[i] = initialPath[i];
                    //~ }
                //~ //set size
                //~ szrp = szip;
            //~ }
        //~ }
        
        printf("k %i, %i\n", m, n);
        if ( n == endNode){
                printf("BANG!");
        }
        //Okay, now if m is equal to zero, a cycle was created and we have
        //to walk back from n
        //if m==endEnd node, we also have to start walking back from there
        //to a node that exits into a clear path.
        if (!m){
            int dbg2 =0;
            while( !m && n != endNode ){
                //check no exits, looks to see if the nod m is the end
                printf("1 - %i %i\n", m, n);
                if (!m){
                    //
                    m=initialPath[szip-1].vertex;
                    --szip;
                }
                printf("2 - %i %i\n", m, n);
                if(checkNoExits(g,m)){
                    //if there arent' any exits blacken the node;
                    blackNode(g, m-1);
                }
                
                //fprintf(stderr, "stderr %c %i", m, (int)m); 

                //reduce the size of szip by one
                //because we are selecting the last visited node and using
                //its vertex value.
                //Move n to block the last node visited from consideration.
                //n=initialPath[szip].vertex;
                //m=cheapestPath(g,m,0);
            }
            //set n to be m so a cheapest path can be discovered

            n=m;
            printf("3 - %i %i\n", m, n);

        }
        //printf("%i %c %i %c %i\n", dbg, m,(int)m,n,(int)n);
        //n will be a node with a clear path to the end node.
        //or all nodes will have been blackened and the loop terminates.
	}
    i=0;
    //you created a path of nodes. Okay. Now copy all the directions you
    //are to go into the array of directions
    //this is the nodes the car needs to go.
    printf("%i\n",szip);
    while (i < szip){
        rpath[i] = initialPath[i].vertex;
        ++i;
    }
    for(i = 0; i < szip; i++){
        printf("px%i\n", rpath[i]);
    }
    //set the very end of the string to be zero;
    rpath[szip]=0;
}
*/
void removeEdge(graph g, char n, char m){
    //m and n sanity check
    if( (m > 0) && (n > 0) ){
        return;
    }
    //set the blocking direction to 'no direction'
    dir blockDir = X;
    //if m is equal to a edge from n,
    //block that single path by setting the block Direction to the enter
    //direction and the direction of that edge to nil (zero);
    
    if(m == g->vertices[n-1].north){
        blockDir = g->vertices[n-1].enternorth;
        g->vertices[n-1].north = 0;
        g->vertices[n-1].enternorth=X;
    } else if(m == g->vertices[n-1].south){
        blockDir = g->vertices[n-1].entersouth;
        g->vertices[n-1].south = 0;
        g->vertices[n-1].entersouth=X;
    } else if(m == g->vertices[n-1].east){
        blockDir = g->vertices[n-1].entereast;
        g->vertices[n-1].east = 0;
        g->vertices[n-1].entereast=X;
    } else if(m == g->vertices[n-1].west){
        blockDir = g->vertices[n-1].enterwest;
        g->vertices[n-1].west = 0;
        g->vertices[n-1].enterwest=X;
    }
    //if there is a blocking direction, it means n had a path that entered
    //m from that direction. Make that path no longer exist.
    if (blockDir == N){
        g->vertices[m-1].north = 0;
        g->vertices[m-1].enternorth = X;
    }
    else if (blockDir == S){
        g->vertices[m-1].south = 0;
        g->vertices[m-1].entersouth = X;
    }
    else if (blockDir == E){
        g->vertices[m-1].east = 0;
        g->vertices[m-1].entereast = X;
    }
    else if (blockDir == W){
        g->vertices[m-1].west = 0;
        g->vertices[m-1].enterwest = X;
    }
    return;
}

void bfSearch(graph g, char startNode, char endNode, char* rpath){
	//sanity check
    if (! (endNode && startNode) ){
        //printf("s!\n");
		return;
	}
    //set up path data and resulting tree
	struct PATHDATA q[g->vertex_count];
	struct PATHDATA t[g->vertex_count];
    //the size of the queue is one
    int szip= 1;
    int szt=1;
    //the size of the start tree, the ending location, and a general purpose iterator is 0
    int endloc, i=0;
    //the initial paths first element is initialized here.
	q[0].vertex = startNode;
    q[0].parent=0;
    q[0].depth=1;
    t[0].vertex = q[0].vertex;
    t[0].parent = q[0].parent;
    t[0].depth = q[0].depth;
    //the initial path is set to gray
	g->vertices[ (int)(startNode-1) ].visited = G;
	//using flag found for now
    //fprintf(stdout,"Here2\n");
    int dbg = 0;
    //perform the search
    while (szip){
        //set end location check, done before szt updates.
        dbg++;
        //fprintf(stdout,"dbg cnt %i\n",dbg);
        if(q[0].vertex==endNode){
            endloc=q[0].depth;//set
            //printf("EL %i\n",endloc);
        }

        if (g->vertices[(int)(q[0].vertex -1)].north &&
            g->vertices[g->vertices[(int)(q[0].vertex -1)].north-1].visited==C                    
        ){
            g->vertices[g->vertices[(int)(q[0].vertex -1)].north-1].visited=G;
            //enque
            ++szip;
            ++szt;
            q[szip-1].vertex = g->vertices[(int)(q[0].vertex -1)].north;
            q[szip - 1].depth = q[0].depth + 1;
            q[szip - 1].parent = q[0].vertex;
            t[szt-1]=q[szip-1];
        }
        
        if (g->vertices[(int)(q[0].vertex -1)].south &&
            g->vertices[ g->vertices[(int)(q[0].vertex -1)].south-1].visited==C
        ){

            g->vertices[g->vertices[(int)(q[0].vertex -1)].south-1].visited=G;
            //enque
            ++szip;
            ++szt;
            //printf("%i %i BANG\n",szip,szt);
            q[szip-1].vertex = g->vertices[(int)(q[0].vertex -1)].south;
                    //printf("BANG\n");
            q[szip - 1].depth = q[0].depth + 1;
            q[szip - 1].parent = q[0].vertex;

            t[szt-1]=q[szip-1];
        }

        if (g->vertices[(int)(q[0].vertex -1)].east &&
            g->vertices[g->vertices[(int)(q[0].vertex -1)].east-1].visited==C
        
            ){
            g->vertices[g->vertices[(int)(q[0].vertex -1)].east-1].visited=G;
            //enque
            ++szip;
            ++szt;
            q[szip-1].vertex = g->vertices[(int)(q[0].vertex -1)].east;
            q[szip - 1].depth = q[0].depth + 1;
            q[szip - 1].parent = q[0].vertex;
            t[szt-1]=q[szip-1];
        }
        if (g->vertices[(int)(q[0].vertex -1)].west &&
            g->vertices[g->vertices[(int)(q[0].vertex -1)].west-1].visited==C
        ){
            g->vertices[g->vertices[(int)(q[0].vertex -1)].west-1].visited=G;
            //enque
            ++szip;
            ++szt;
            q[szip-1].vertex = g->vertices[(int)(q[0].vertex -1)].west;
            q[szip - 1].depth = q[0].depth + 1;
            q[szip - 1].parent = q[0].vertex;
            t[szt-1]=q[szip-1];
        }
        //blacken node
        g->vertices[(int)(q[0].vertex -1)].visited = B;
        //de-que node
        for(i=1; i < szip; i++){
			q[i-1]=q[i];
        }
        --szip;
    }
    //update character return from tree;
    //printf("SEARCH DONE\n");
    int parent = 0;
    for (int j = 0; j< szt; j++){
        if (endNode == t[j].vertex){
            parent=j;
            j=szt; 
        }
    }
    //printf("PX -- %i CONF %i\n",parent, t[parent].vertex);
    for(i=0 ;i < endloc; i++ ){
        rpath[endloc-i-1] = t[parent].vertex;
        for (int j = 0; j< szt; j++){
            if (t[parent].parent == t[j].vertex){
                parent= j;
                j=szt; 
            }
            
        }
    }
    rpath[endloc]=0;
    
}

move getMove(graph g, char loc, char going, dir facing){
        if(g->vertices[(int) loc-1 ].north == going){
                switch (facing){
                    case N:
                        return FORWARD;
                        break;
                    case S:
                        return REVERSE;
                        break;
                    case E:
                        return RIGHT;
                        break;
                    case W:
                        return LEFT;
                        break;
                }
            } else if( going == g->vertices[(int) loc-1 ].south){
                switch (facing){
                    case N:
                        return REVERSE;
                        break;
                    case S:
                        return FORWARD;
                        break;
                    case E:
                        return LEFT;
                        break;
                    case W:
                        return RIGHT;
                        break;
                }
            } else if (going == g->vertices[(int) loc-1 ].east){
                switch (facing){
                    case N:
                        return LEFT;
                        break;
                    case S:
                        return RIGHT;
                        break;
                    case E:
                        return FORWARD;
                        break;
                    case W:
                        return REVERSE;
                        break;
                }
            } else if (going == g->vertices[(int) loc-1 ].west ){
                
                switch (facing){
                    case N:
                        return RIGHT;
                        break;
                    case S:
                        return LEFT;
                        break;
                    case E:
                        return REVERSE;
                        break;
                    case W:
                        return FORWARD;
                        break;
                }
            }
    return NOMOVE;
}

dir getDir(graph g, char loc, char next){
    if (g->vertices[(int)loc-1 ].north == next){
        return  g->vertices[(int) loc - 1].enternorth;
    } else if (g->vertices[(int) loc-1 ].south == next){
        return g->vertices[(int) loc - 1].entersouth;
    } else if (g->vertices[(int) loc-1 ].east == next){
        return g->vertices[(int) loc - 1].entereast;
    } else if (g->vertices[(int) loc-1 ].west == next){
        return g->vertices[(int) loc - 1].enterwest;
    }
    return X;
}

void makeDirections(graph g, char *locations, move* direct_arr, dir initial_facing){
    char* lnext= locations + 1;
    char* lprev = locations;
    if (!(*lprev)){
        direct_arr[0] = NOMOVE;
        return;
    }
    move* diter = direct_arr;
    dir facing = initial_facing;
    *diter = getMove(g, *lprev, *lnext, facing);
    facing = getDir(g, *lprev, *lnext);
    
    while (*lnext){
        lprev = lnext;
        ++lnext;
        ++diter;
        *diter = getMove(g, *lprev, *lnext, facing);
        //printf("%i %i %i %i diter\n", *diter, *lprev, *lnext, facing);
        facing = getDir(g, *lprev, *lnext);
    }
    //write one past as no move
    ++diter;
    *diter = NOMOVE;
}

void breakConnection(graph g, char n, char m){
    if (n < 0 || m < 0){
        return;
    }
    dir target_back;
    if (g->vertices[(int)n-1].north == m){
        g->vertices[(int)n-1].north = 0;
        target_back = g->vertices[(int)n-1].enternorth;
        g->vertices[(int)n-1].enternorth = X;
        if (target_back == N){
            g->vertices[(int)m-1].north==0;
            g->vertices[(int)m-1].enternorth=X;
        } else if (target_back == S) {
            g->vertices[(int)m-1].south==0;
            g->vertices[(int)m-1].entersouth=X;
        } else if (target_back == E){
            g->vertices[(int)m-1].east==0;
            g->vertices[(int)m-1].entereast=X;
        }
        if (target_back == W){
            g->vertices[(int)m-1].west==0;
            g->vertices[(int)m-1].enterwest=X;
        }
        
    } else if (g->vertices[(int)n-1].south == m){
        g->vertices[(int)n-1].south = 0;
        target_back = g->vertices[(int)n-1].entersouth;
        g->vertices[(int)n-1].entersouth = X;
        if (target_back == N){
            g->vertices[(int)m-1].north==0;
            g->vertices[(int)m-1].enternorth=X;
        } else if (target_back == S) {
            g->vertices[(int)m-1].south==0;
            g->vertices[(int)m-1].entersouth=X;
        } else if (target_back == E){
            g->vertices[(int)m-1].east==0;
            g->vertices[(int)m-1].entereast=X;
        }
        if (target_back == W){
            g->vertices[(int)m-1].west==0;
            g->vertices[(int)m-1].enterwest=X;
        }
        
    } else if (g->vertices[(int)n-1].east == m){
        g->vertices[(int)n-1].east = 0;
        target_back = g->vertices[(int)n-1].entereast;
        g->vertices[(int)n-1].entereast = X;
        if (target_back == N){
            g->vertices[(int)m-1].north==0;
            g->vertices[(int)m-1].enternorth=X;
        } else if (target_back == S) {
            g->vertices[(int)m-1].south==0;
            g->vertices[(int)m-1].entersouth=X;
        } else if (target_back == E){
            g->vertices[(int)m-1].east==0;
            g->vertices[(int)m-1].entereast=X;
        }
        if (target_back == W){
            g->vertices[(int)m-1].west==0;
            g->vertices[(int)m-1].enterwest=X;
        }
        
    } else if (g->vertices[(int)n-1].west == m){
        g->vertices[(int)n-1].west = 0;
        target_back = g->vertices[(int)n-1].enterwest;
        g->vertices[(int)n-1].enterwest = X;
        if (target_back == N){
            g->vertices[(int)m-1].north==0;
            g->vertices[(int)m-1].enternorth=X;
        } else if (target_back == S) {
            g->vertices[(int)m-1].south==0;
            g->vertices[(int)m-1].entersouth=X;
        } else if (target_back == E){
            g->vertices[(int)m-1].east==0;
            g->vertices[(int)m-1].entereast=X;
        }
        if (target_back == W){
            g->vertices[(int)m-1].west==0;
            g->vertices[(int)m-1].enterwest=X;
        }
        
    }
}
