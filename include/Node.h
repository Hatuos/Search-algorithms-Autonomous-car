/* 
Date: 21/10/2020
Node.h: Contains the definition of the node class                   
*/

#ifndef NODE
#define NODE

#include <iostream>
#include <vector>


using namespace std;


struct Position                      // Structure to represent positions
{
  int i;
  int j;
};


class Node 
{
  private:
    int cost_;                       // Node cost
    int heuristic_;                  // Heuristic value of the node
    int f_;                          // Total cost (cost_ + heuristic_)
    Position pos_;                   // Node position
    Position prev_pos_;              // Parent node
    int prev_mov_;                   // Movement to reach the node
    bool selected_;                  // Boolean for node selection
    
  
  public:
    Node();                          // Builder
    Node(int, Position);             // Constructor overload - Parameters
    Node(const Node&);               // Constructor overload - Copy
    ~Node();                         // Destroyer

    int get_cost() const;
    int get_heuristic() const;
    int get_f() const;
    Position get_pos() const;        // Getters
    Position get_prev_pos() const;
    int get_prev_mov() const;
    bool get_selected() const;

    void set_cost(int);
    void set_heuristic(int);
    void set_f(int);
    void set_pos(Position);          // Setters
    void set_prev_pos(Position);
    void set_prev_mov(int);
    void set_selected(bool);

    void clean();                    // Reset the node values

    Node& operator=(const Node&);                          // Operator overload "="
    bool operator==(const Node&) const;                    // Operator overload "==" - Comparisons
    friend ostream& operator<< (ostream&, const Node&);    // Show the node and its parent node
};

#endif
