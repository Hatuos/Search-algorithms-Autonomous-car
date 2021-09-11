# Search-algorithms-Autonomous-car
## Problem description
The aim of this project is to use search strategies as a proposed solution in the determination of trajectory planning for autonomous cars.

The environment of the autonomous car can be assumed to be rectangular with dimensions M x N and consisting of
by free and occupied cells, where the car can perform movement actions, one at a time, from the current cell to one of the 4 adjacent cells (North, South, East or West) that are not in the current cell.The occupied squares correspond to obstacles. Free squares correspond to cells free of obstacles.

The car has a perception vector, consisting of the state of a proximity sensor (SN, SO, SS, SE) for each direction of movement.
sensor (SN, SO, SS, SE) for each direction of movement, which detects whether the corresponding neighbour is occupied by an obstacle "1".


## Heuristic functions used
Euclidean distance: In such a two-dimensional space problem, the Euclidean distance between the origin point C and the end point X of coordinates (c1, c2) and (x1, x2) is calculated as -> ED = sqrt( (x1-c1)^2 + (x2-c2)^2 )

Rectilinear distance: In a two-dimensional space problem like this one, the rectilinear distance between two points is posed as a series of 90 degree turns joining the two points. Having the origin node C with coordinates (c1, c2) and the end node X with coordinates (x1,x2) , is calculated as -> RD = | x1 - c1 | + | x2 - c2 |
