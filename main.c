#include <stdio.h>
#include <malloc.h>
#include "map.h"

void printVertice(struct GRAPHHEAD g, int n){
	char fn, fs, fe, fw;
	struct NODE v = g.vertices[pathOpen(n)];
	switch(v.enternorth){
		case(N):
				fn = 'N';
				break;
		case(S):
				fn = 'S';
				break;
		case(E):
				fn = 'E';
				break;
		case(W):
				fn = 'W';
				break;
		case(X):
				fn='X';
				break;
	};
	switch(v.entersouth){
		case(N):
				fs = 'N';
				break;
		case(S):
				fs = 'S';
				break;
		case(E):
				fs = 'E';
				break;
		case(W):
				fs = 'W';
				break;
		case(X):
				fs='B';
				break;
	};
	switch(v.entereast){
		case(N):
				fe = 'N';
				break;
		case(S):
				fe = 'S';
				break;
		case(E):
				fe = 'E';
				break;
		case(W):
				fe = 'W';
				break;
		case(X):
				fe='B';
				break;
	};
	switch(v.enterwest){
		case(N):
				fw = 'N';
				break;
		case(S):
				fw = 'S';
				break;
		case(E):
				fw = 'E';
				break;
		case(W):
				fw = 'W';
				break;
		case(X):
				fw='B';
				break;
	};
	printf("Vertex %i, Edges %i, Directions: N %i f %c S %i f %c E %i f %c W %i f %c", n, countAt(g,n), v.north, fn, v.south, fs, v.east, fe, v.west,fw);
	printf("\nWeights: n %i s %i e %i w %i Visited: %i \n", v.wn, v.ws, v.we, v.ww, v.visited);
}

void printMap(graph g){
	for (int i=1; i < g->vertex_count+1; i++){
		printVertice(*g, i);
	}
}


int main(){
    
    char pathc[18];
    pathc[0]=4;
    pathc[1]=3;
    pathc[2]=2;
    pathc[3]=8;
    pathc[4]=10;
    pathc[5]=9;
    pathc[6]=12;
    pathc[7]=14;
    
    dir pathdir[18];
    pathdir[0]=4;
    pathdir[1]=3;
    pathdir[2]=2;
    pathdir[3]=8;
    pathdir[4]=10;
    pathdir[5]=9;
    pathdir[6]=12;
    pathdir[7]=14;
    
    
	struct GRAPHHEAD map = {
			.edge_count = 0,
			.vertex_count = 18,
			.vertices ={
					//1
					{.visited=C, .north=5,.south=0,.east=2,.west=0, .enternorth=N,.entersouth=X,.entereast=E,.enterwest=X, .wn=0,.ws=0,.we=0,.ww=0},
					//2
					{.visited=C, .north=8,.south=0,.east=3,.west=1, .enternorth=N,.entersouth=X,.entereast=E,.enterwest=W,.wn=0,.ws=0,.we=0,.ww=0},
					//3
					{.visited=C, .north=4,.south=0,.east=0,.west=2, .enternorth=N,.entersouth=X,.entereast=X,.enterwest=W, .wn=0,.ws=0,.we=0,.ww=0},
					//4
					{.visited=C, .north=0,.south=3,.east=0,.west=0, .enternorth=X,.entersouth=S,.entereast=X,.enterwest=X, .wn=0,.ws=0,.we=0,.ww=0},
					//5
					{.visited=C, .north=11,.south=1,.east=6,.west=0, .enternorth=N,.entersouth=S,.entereast=E,.enterwest=X, .wn=0,.ws=0,.we=0,.ww=0},
					//6
					{.visited=C, .north=11,.south=7,.east=8,.west=5, .enternorth=N,.entersouth=S,.entereast=E,.enterwest=W, .wn=0,.ws=0,.we=0,.ww=0},
					//7
					{.visited=C, .north=6,.south=0,.east=0,.west=0, .enternorth=N,.entersouth=X,.entereast=X,.enterwest=X, .wn=0,.ws=0,.we=0,.ww=0},
					//8
					{.visited=C, .north=10,.south=2,.east=18,.west=6, .enternorth=N,.entersouth=S,.entereast=E,.enterwest=W, .wn=0,.ws=0,.we=0,.ww=0},
					//9
					{.visited=C, .north=12,.south=0,.east=15,.west=10, .enternorth=N,.entersouth=X,.entereast=E,.enterwest=W, .wn=0,.ws=0,.we=0,.ww=0},
					//10
					{.visited=C, .north=0,.south=8,.east=9,.west=11, .enternorth=X,.entersouth=S,.entereast=E,.enterwest=W, .wn=0,.ws=0,.we=0,.ww=0},
					//11
					{.visited=C, .north=0,.south=6,.east=10,.west=5, .enternorth=X,.entersouth=S,.entereast=E,.enterwest=S, .wn=0,.ws=0,.we=0,.ww=0},
					//12
					{.visited=C, .north=0,.south=9,.east=13,.west=14, .enternorth=X,.entersouth=S,.entereast=E,.enterwest=W, .wn=0,.ws=0,.we=0,.ww=0},
					//13
					{.visited=C, .north=0,.south=0,.east=0,.west=12, .enternorth=X,.entersouth=X,.entereast=X,.enterwest=W, .wn=0,.ws=0,.we=0,.ww=0},
					//14
					{.visited=C, .north=0,.south=0,.east=12,.west=0, .enternorth=X,.entersouth=X,.entereast=E,.enterwest=X, .wn=0,.ws=0,.we=0,.ww=0},
					//15
					{.visited=C, .north=0,.south=16,.east=0,.west=9, .enternorth=X,.entersouth=S,.entereast=X,.enterwest=W, .wn=0,.ws=0,.we=0,.ww=0},
					//16
					{.visited=C, .north=15,.south=0,.east=17,.west=0, .enternorth=N,.entersouth=X,.entereast=E,.enterwest=X, .wn=0,.ws=0,.we=0,.ww=0},
					//17
					{.visited=C, .north=0,.south=18,.east=0,.west=16, .enternorth=X,.entersouth=S,.entereast=E,.enterwest=X, .wn=0,.ws=0,.we=0,.ww=0},
					//18
					{.visited=C, .north=17,.south=0,.east=0,.west=8, .enternorth=N,.entersouth=X,.entereast=X,.enterwest=W, .wn=0,.ws=0,.we=0,.ww=0}
			}
	};

	printVertice(map, 1);
	countEdges(&map);
    printf("IN");
	setWeights(&map, 4, S);
    printf("OUT");
	printf("Hello World %i\n", map.edge_count);
	printMap(&map);
	char* stx = (char*)malloc( sizeof(char)*(map.vertex_count+1)) ;
    stx[0]=1;
    printf("Here!!!!\n");
    //make sure you open up all the nodes or this will fail.
    openNodes(&map);
    //findPath(&map, 4, 14, S,stx);
    bfSearch(&map,4,14,stx);
    //make sure you open up all the nodes or findPath will fail.
    char* k = stx;
    while(*k){
        printf("D - %i\n", *k);
        ++k;
    }
    move* dtx = (move*)malloc(sizeof(move)*(map.vertex_count+1));
    makeDirections(&map, stx, dtx, S);
    move* di = dtx;
    while(*di != NOMOVE){
        switch(*di){
            case(FORWARD):
                printf("Forward\n");
            break;
            case(REVERSE):
                printf("Reverse\n");
            break;
            case(LEFT):
                printf("Left\n");
            break;
            case(RIGHT):
                printf("Right\n");
            break;
        }
        ++di;
    }
    breakConnection(&map, 2, 8);
    openNodes(&map);
    bfSearch(&map, 4, 14, stx);
    k = stx;
    while(*k){
        printf("D - %i\n", *k);
        ++k;
    }
    printf("All tests done!\n");
    k=0;
    free(stx);
    free(dtx);
    return 0;
    
}
