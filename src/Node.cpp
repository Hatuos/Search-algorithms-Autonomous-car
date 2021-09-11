#include "../include/Node.h"


Node::Node(void) : cost_(0), heuristic_(0), f_(0), pos_(), prev_pos_(), prev_mov_(-1), selected_(false)   // Builder
{
}


Node::Node(int cost, Position p) : cost_(cost)         // Constructor overload - Parameters
{
  this->pos_.i = p.i;
  this->pos_.j = p.j;
}


Node::Node(const Node& node)                           // Constructor overload - Copy
{
  cost_ = node.cost_;
  heuristic_ = node.heuristic_;
  f_ = node.f_;
  pos_ = node.pos_;
  prev_pos_ = node.prev_pos_;
  prev_mov_ = node.prev_mov_;
  selected_ = node.selected_;
}


Node::~Node()                                          // Destroyer
{
}

                                                    
int Node::get_cost(void) const                         // Returns the cost                                      
{
  return this->cost_;
}


int Node::get_heuristic(void) const                    // Returns heuristic              
{
  return this->heuristic_;
}


int Node::get_f(void) const                            // Returns total cost
{
  return this->f_;
}


int Node::get_prev_mov(void) const                     // Returns the previous movement
{
  return this->prev_mov_;
}


Position Node::get_pos(void) const                     // Returns position
{
  return this->pos_;
}


Position Node::get_prev_pos(void) const                // Returns parent position
{
  return this->prev_pos_;
}


bool Node::get_selected(void) const                    // Returns selection boolean
{
  return this->selected_;
}                                                      


void Node::set_cost (int cost)                         // Sets cost
{
  this->cost_ = cost;
}


void Node::set_heuristic (int h)                       // Sets heuristic
{
  this->heuristic_ = h;
}


void Node::set_f (int f)                               // Sets total cost
{
  this->f_ = f;
}


void Node::set_prev_mov(int m)                         // Sets previous movement
{
  this->prev_mov_ = m;
}


void Node::set_pos(Position x)                         // Sets position
{
  this->pos_.i = x.i;
  this->pos_.j = x.j;
}


void Node::set_prev_pos(Position x)                    // Sets previous position
{
  this->prev_pos_.i = x.i;
  this->prev_pos_.j = x.j;
}


void Node::set_selected(bool s)                        // Sets selection boolean
{
  this->selected_ = s;
}


void Node::clean (void)                                // Resets the node values
{
  Position aux;
  aux.i = -1;
  aux.j = -1;

  this->cost_ = 0;
  this->heuristic_ = 0;
  this->f_ = 0;
  this->pos_ = aux;
  this->prev_pos_ = aux;
  this->prev_mov_ = -1;
  this->selected_ = false;
}


Node& Node::operator= (const Node& aux)                // Operator overload "="
{
  this->cost_ = aux.get_cost();
  this->heuristic_ = aux.get_heuristic();
  this->f_ = aux.get_f();
  this->pos_ = aux.get_pos();
  this->prev_pos_ = aux.get_prev_pos();
  this->selected_ = aux.get_selected();
  this->prev_mov_ = aux.prev_mov_;
  return (*this);
}


bool Node::operator== (const Node& aux) const          // Operator overload "==" - Comparisons
{
  if ((this->pos_.i == aux.get_pos().i) && (this->pos_.j == aux.get_pos().j))
    return 1;
  else
    return 0;
}


ostream& operator<< (ostream& os, const Node& node)     // Shows the node and its parent node
{
  os << "Node: [" << node.get_pos().i << ", " << node.get_pos().j << "]";
 //os << " with " << node.get_cost() << " + " << node.get_heuristic() << " = " << node.get_f();
 //os << " -> Nodo padre: [" << node.get_prev_pos().i << ", " << node.get_prev_pos().j << "]\n";
  os << " -> Previous move: " << node.get_prev_mov() << endl;

  return os;
}
