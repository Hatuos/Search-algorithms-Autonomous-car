/* 

Date: 21/10/2020
Router.h: Contains the definition of the router class      
     
*/

#ifndef ROUTER
#define ROUTER

#include <iostream>
#include <vector>
#include <limits.h>
#include <math.h>
#include "Node.h"


using namespace std;


class Router 
{
  private:
    vector<Node> analysis_vector_;            // Vector with all analysed nodes
    vector<Node> optimal_path_;               // Optimal path vector                                                 
    vector<int> movements_;                   // Movements to be made within the optimal pathway

  public:
    Router();                                 // Builder
    Router(const Router&);                    // Builder overload - Copy
    ~Router();                                // Destroyer

    void heuristic_1(Position, Node&);        // Sets heuristic 1 - Euclidean distance
    void heuristic_2(Position, Node&);        // Sets heuristic 2 - Rectilinear distance

    Node evaluate_position (Position);                               // Position assessment 
    void calculate(vector<vector<char>>, Position, Position, int);   // Calculate optimal route on board
    void clean();                                                    // Clean up vectors - Attributes

    vector<int> get_movements() const;        // Returns the movements vector
    int get_nodes_number() const;             // Returns number of nodes generated      
};

#endif
