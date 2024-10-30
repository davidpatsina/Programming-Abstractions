/******************************************************************************
 * File: Trailblazer.cpp
 *
 * Implementation of the graph algorithms that comprise the Trailblazer
 * assignment.
 */

#include "Trailblazer.h"
#include "TrailblazerGraphics.h"
#include "TrailblazerTypes.h"
#include "TrailblazerPQueue.h"
#include "stack.h"
#include "random.h"
#include "map.h"
#include "foreach.h"
using namespace std;

/* Function: shortestPath
 * 
 * Finds the shortest path between the locations given by start and end in the
 * specified world.	 The cost of moving from one edge to the next is specified
 * by the given cost function.	The resulting path is then returned as a
 * Vector<Loc> containing the locations to visit in the order in which they
 * would be visited.	If no path is found, this function should report an
 * error.
 *
 * In Part Two of this assignment, you will need to add an additional parameter
 * to this function that represents the heuristic to use while performing the
 * search.  Make sure to update both this implementation prototype and the
 * function prototype in Trailblazer.h.
 */




void colorEvryPointGray(Grid<graphPoints>& pointsInfo, Grid<double>& world){
		for (int i =0; i < pointsInfo.nRows; i++){
			for (int j =0; j < pointsInfo.nCols; j++){
				pointsInfo[i][j].color = GRAY;
				Loc curr = makeLoc(i, j);
				colorCell(world, curr, GRAY);
			}
		}
}



void makePointInfo(Loc start, Loc end, Grid<double>& world,  double costFn(Loc from, Loc to, Grid<double>& world), double heuristic(Loc start, Loc end, Grid<double>& world), Grid<graphPoints>& pointsInfo){
	colorEvryPointGray(pointsInfo, world);
	pointsInfo[start.row][start.col].color = YELLOW;
	pointsInfo[start.row][start.col].distance = 0.0;
	colorCell(world, start, YELLOW);
    
	TrailblazerPQueue<Loc> queue;
	queue.enqueue(start, heuristic(start, end, world));//
	
	while (!queue.isEmpty()){
		Loc curr = queue.dequeueMin();
		pointsInfo[curr.row][curr.col].color = GREEN;
		
		colorCell(world, curr, GREEN);
		if (curr == end) return;

		for (int i = -1; i <= 1; i++){
			for (int j = -1; j <= 1; j++){
				if (i == 0 && j == 0) continue;
				Loc neighbour = makeLoc(curr.row+i, curr.col+j);
				if(world.inBounds(neighbour.row, neighbour.col) ){
					
					double possibleDistanceFromStartToNeigh = costFn(curr, neighbour, world) + pointsInfo[curr.row][curr.col].distance;
					bool gray = (pointsInfo[neighbour.row][neighbour.col].color == GRAY);
					bool yellow = (pointsInfo[neighbour.row][neighbour.col].color == YELLOW);
					bool distance = (pointsInfo[neighbour.row][neighbour.col].distance >  possibleDistanceFromStartToNeigh);
					
					if(gray){
						pointsInfo[neighbour.row][neighbour.col].color = YELLOW;
						colorCell(world, neighbour, YELLOW);
						pointsInfo[neighbour.row][neighbour.col].distance =possibleDistanceFromStartToNeigh;
						pointsInfo[neighbour.row][neighbour.col].parent = curr;
						queue.enqueue(neighbour, possibleDistanceFromStartToNeigh+heuristic(neighbour, end, world));//
					}

					if(yellow && distance){
						pointsInfo[neighbour.row][neighbour.col].distance = possibleDistanceFromStartToNeigh;
						pointsInfo[neighbour.row][neighbour.col].parent = curr;
						queue.decreaseKey(neighbour, possibleDistanceFromStartToNeigh+heuristic(neighbour, end, world));//
					}
				} 

			}
		}
	
	}
}


Vector<Loc> shortestPath(Loc start, Loc end, Grid<double>& world,  double costFn(Loc from, Loc to, Grid<double>& world), double heuristic(Loc start, Loc end, Grid<double>& world)) {
	Vector<Loc> result;
	Vector<Loc> reverseResult;
	Grid<graphPoints> pointsInfo(world.nRows, world.nCols);
	makePointInfo(start, end, world, costFn, heuristic, pointsInfo);
	
	while(!(end.col == start.col && end.row == start.row)){
		reverseResult.add(end);
		end = pointsInfo[end.row][end.col].parent;
	}
	reverseResult.add(start);
	for (int i = reverseResult.size()-1; i >= 0;  i--){
		result.add(reverseResult[i]);
	}
    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

void createEdgesAndInsertInQueue(int numRows, int numCols, Set<Edge>& edges, TrailblazerPQueue<Edge>& queue){
	for (int i =0; i < numRows; i++){
		for (int j = 0; j < numCols; j++){
			Loc curr = makeLoc(i,j);
			Loc rightFromCurr = makeLoc(i, j+1);
			Loc dowrnFromCurr = makeLoc(i+1, j);

			if(rightFromCurr.col >= 0 && rightFromCurr.col < numCols && rightFromCurr.row >= 0 && rightFromCurr.row < numRows){
				Edge newEdge = makeEdge(curr, rightFromCurr);
				edges.add(newEdge);
				queue.enqueue(newEdge, randomReal(0,1));
			}
			if(dowrnFromCurr.col >= 0 && dowrnFromCurr.col < numCols && dowrnFromCurr.row >= 0 && dowrnFromCurr.row < numRows){
				Edge newEdge = makeEdge(curr, dowrnFromCurr);
				edges.add(newEdge);
				queue.enqueue(newEdge, randomReal(0,1));
			
			}
		}
	}	

}

void createClusters(int numRows, int numCols, Map<Loc, Set<Loc>>& clusters){
	for (int i = 0; i < numRows; i++){
		for (int j=0; j < numCols; j++){
			Loc curr = makeLoc(i, j);
			Set<Loc> cluster;
			cluster.add(curr);
			clusters.put(curr, cluster);
		}
	}
}

void mergeClusters(Loc start, Loc end, Map<Loc, Set<Loc>>& clusters){
	clusters[start] += clusters[end];
	Set<Loc> newLocs = clusters[end] - end;

	foreach(Loc loc in newLocs){
		clusters[loc].clear();
		clusters[loc].add(start);
	}
	clusters[end].clear();
	clusters[end].add(start);
}

Set<Edge> createMaze(int numRows, int numCols) {
	Set<Edge> mst;
	Set<Edge> edges;
	Map<Loc, Set<Loc>> clusters;
	TrailblazerPQueue<Edge> queue;
	int numOfClusters = numRows*numCols;
	
	createEdgesAndInsertInQueue(numRows, numCols, edges, queue);
	createClusters(numRows, numCols, clusters);
	

	while (numOfClusters > 1){
		Edge curr = queue.dequeueMin();
		bool areFromSameClusters = (clusters.get(curr.start) == clusters.get(curr.start));
		if (!areFromSameClusters){
			numOfClusters--;
			mergeClusters(curr.start, curr.end, clusters);
			mst.add(curr);
		}

	}

    return mst;
}


