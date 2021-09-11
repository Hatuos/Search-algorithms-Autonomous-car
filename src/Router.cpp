#include "../include/Router.h"


Router::Router(void) : analysis_vector_(), optimal_path_(), movements_()      // Builder
{
}


Router::Router(const Router& router)                    // Builder overload - Copy  
{
  analysis_vector_ = router.analysis_vector_;
  optimal_path_ = router.optimal_path_;
  movements_ = router.movements_;
}


Router::~Router()                                       // Destroyer
{
}


void Router::heuristic_1(Position final, Node& act)     // Sets heuristic 1 - Euclidean distance
{
  int pos_i = act.get_pos().i;
  int pos_j = act.get_pos().j;
  int distance = sqrt( ((final.i - pos_i) * (final.i - pos_i)) + ((final.j - pos_j) * (final.j - pos_j)) );

  act.set_heuristic(distance);
}


void Router::heuristic_2(Position final, Node& act)     // Sets heuristic 2 - Rectilinear distance
{

  int pos_i = act.get_pos().i;
  int pos_j = act.get_pos().j;
  int distance = abs(final.i - pos_i) + abs(final.j - pos_j);

  act.set_heuristic(distance);
}


Node Router::evaluate_position(Position fin)            // Evaluate node-accessible positions and choose one
{
  int aux = INT_MAX;
  int index = 0;

  for (int i = 0; i < this->analysis_vector_.size(); i++) 
  {
    if (this->analysis_vector_[i].get_selected() == false) 
    {
      if (aux >= this->analysis_vector_[i].get_f()) 
      {
        aux = this->analysis_vector_[i].get_f();
        index = i;
      }
    }
  }
  
  this->analysis_vector_[index].set_selected(true);
  Node aux_node(this->analysis_vector_[index]);
  return aux_node;
}


void Router::calculate(vector<vector<char>> map, Position ini, Position fin, int heuri)     // Calculate optimal route on board
{
  if ( !((ini.i==fin.i) && (ini.j==fin.j) )) 
  {
    Position actual_pos;
    actual_pos.i = ini.i;
    actual_pos.j = ini.j;
    
    Node aux_node;
    Position aux_pos;
    int aux_cost = 0;
    bool stop = false;
    
    Node chosen_node;
    vector<Node> chosen_vector;
   
    aux_node.clean();
    chosen_node.clean();
                                              // We record the initial position
    aux_node.set_cost(0);
    aux_node.set_pos(ini);
    aux_node.set_prev_pos(ini);
    aux_node.set_selected(true);
    if (heuri == 1)
      this->heuristic_1(fin, aux_node);
    if (heuri == 2)
      this->heuristic_2(fin, aux_node);

    aux_node.set_f(aux_node.get_cost() + aux_node.get_heuristic());

    this->analysis_vector_.push_back(aux_node);
    chosen_vector.push_back(aux_node);
    aux_node.clean();

                                               // We analyse the first 4 positions

    if ((actual_pos.i-1 >= 0) && ((map[actual_pos.i-1][actual_pos.j] == ' ') || (map[actual_pos.i-1][actual_pos.j] == 'X'))) 
    {
      aux_pos.i = actual_pos.i-1;
      aux_pos.j = actual_pos.j;

      aux_cost = 1;
      aux_node.set_cost(aux_cost);
      aux_node.set_prev_mov(0);                // Up
      aux_node.set_pos(aux_pos);
      aux_node.set_prev_pos(this->analysis_vector_[0].get_pos());
      aux_node.set_selected(false);
                          
      if (heuri == 1)
        this->heuristic_1(fin, aux_node);
      if (heuri == 2)
        this->heuristic_2(fin, aux_node);

      aux_node.set_f(aux_node.get_cost() + aux_node.get_heuristic());

      int i = 0;
      bool insert = true;
      while (i < this->analysis_vector_.size()) 
      {
        if (this->analysis_vector_[i] == aux_node)
          insert = false;
        i++;
      }
      if (insert)
        this->analysis_vector_.push_back(aux_node);
      aux_node.clean();
    }

    if ((actual_pos.i+1 < map.size()) && ((map[actual_pos.i+1][actual_pos.j] == ' ') || (map[actual_pos.i+1][actual_pos.j] == 'X'))) 
    {
      aux_pos.i = actual_pos.i+1;
      aux_pos.j = actual_pos.j;

      aux_cost = 1;
      aux_node.set_cost(aux_cost);
      aux_node.set_prev_mov(1);                // Down
      aux_node.set_pos(aux_pos);
      aux_node.set_prev_pos(this->analysis_vector_[0].get_pos());
      aux_node.set_selected(false);

      if (heuri == 1)
        this->heuristic_1(fin, aux_node);
      if (heuri == 2)
        this->heuristic_2(fin, aux_node);

      aux_node.set_f(aux_node.get_cost() + aux_node.get_heuristic());

      int i = 0;
      bool insert = true;
      while (i < this->analysis_vector_.size()) 
      {
        if (this->analysis_vector_[i] == aux_node)
          insert = false;
        i++;
      }
      if (insert)
        this->analysis_vector_.push_back(aux_node);
      aux_node.clean();
    }

    if ((actual_pos.j-1 >= 0) && ((map[actual_pos.i][actual_pos.j-1] == ' ') || (map[actual_pos.i][actual_pos.j-1] == 'X'))) 
    {
      aux_pos.i = actual_pos.i;
      aux_pos.j = actual_pos.j-1;

      aux_cost = 1;
      aux_node.set_cost(aux_cost);
      aux_node.set_prev_mov(2);                // Left
      aux_node.set_pos(aux_pos);
      aux_node.set_prev_pos(this->analysis_vector_[0].get_pos());
      aux_node.set_selected(false);

      if (heuri == 1)
        this->heuristic_1(fin, aux_node);
      if (heuri == 2)
        this->heuristic_2(fin, aux_node);

      aux_node.set_f(aux_node.get_cost() + aux_node.get_heuristic());

      int i = 0;
      bool insert = true;
      while (i < this->analysis_vector_.size()) 
      {
        if (this->analysis_vector_[i] == aux_node)
          insert = false;
        i++;
      }
      if (insert)
        this->analysis_vector_.push_back(aux_node);
      aux_node.clean();
    }

    if ((actual_pos.j+1 < map[0].size()) && ((map[actual_pos.i][actual_pos.j+1] == ' ') || (map[actual_pos.i][actual_pos.j+1] == 'X'))) 
    {
      aux_pos.i = actual_pos.i;
      aux_pos.j = actual_pos.j+1;
     
      aux_cost = 1;
      aux_node.set_cost(aux_cost);
      aux_node.set_prev_mov(3);                // Right
      aux_node.set_pos(aux_pos);
      aux_node.set_prev_pos(this->analysis_vector_[0].get_pos());
      aux_node.set_selected(false);

      if (heuri == 1)
        this->heuristic_1(fin, aux_node);
      if (heuri == 2)
        this->heuristic_2(fin, aux_node);

      aux_node.set_f(aux_node.get_cost() + aux_node.get_heuristic());

      int i = 0;
      bool insert = true;
      while (i < this->analysis_vector_.size()) 
      {
        if (this->analysis_vector_[i] == aux_node)
          insert = false;
        i++;
      }
      if (insert)
        this->analysis_vector_.push_back(aux_node);
      aux_node.clean();
    }

    chosen_node.clean();
    chosen_node = this->evaluate_position(fin);
    chosen_vector.push_back(chosen_node);

    actual_pos.i = chosen_node.get_pos().i;
    actual_pos.j = chosen_node.get_pos().j;


   if ( (actual_pos.i == fin.i) && (actual_pos.j == fin.j) )
     stop = true;
   else
     stop = false;

   if ( (actual_pos.i == ini.i) && (actual_pos.j == ini.j) )
   {
     cout << endl;
     cout << "\033[1m\033[33m" << " The car cannot move out of the starting position " << "\033[0m" << endl; 
     this->optimal_path_.push_back(chosen_vector[0]);
     this->movements_.push_back(this->optimal_path_[0].get_prev_mov());
     return;
   }
     
   while (!stop) 
   {
      // I analyse from the current position and avoid analysing the previous position.

      if ((actual_pos.i-1 >= 0) && ((map[actual_pos.i-1][actual_pos.j] == ' ') || (map[actual_pos.i-1][actual_pos.j] == 'X'))) 
      {
        if (!((actual_pos.i-1 == chosen_node.get_prev_pos().i) && (actual_pos.j == chosen_node.get_prev_pos().j))) 
        {
          aux_pos.i = actual_pos.i-1;
          aux_pos.j = actual_pos.j;

          aux_cost = 1 + chosen_node.get_cost();
          aux_node.set_cost(aux_cost);
          aux_node.set_prev_mov(0);                // Up
          aux_node.set_pos(aux_pos);
          aux_node.set_prev_pos(chosen_node.get_pos());
          aux_node.set_selected(false);
                          
          if (heuri == 1)
            this->heuristic_1(fin, aux_node);
          if (heuri == 2)
            this->heuristic_2(fin, aux_node);

          aux_node.set_f(aux_node.get_cost() + aux_node.get_heuristic());

          int i = 0;
          bool insert = true;
          while (i < this->analysis_vector_.size()) 
          {
            if (this->analysis_vector_[i] == aux_node)
              insert = false;
            i++;
          }
          if (insert)
            this->analysis_vector_.push_back(aux_node);
          aux_node.clean();
        }
      }

      if ((actual_pos.i+1 < map.size()) && ((map[actual_pos.i+1][actual_pos.j] == ' ') || (map[actual_pos.i+1][actual_pos.j] == 'X')))
      {
        if (!((actual_pos.i+1 == chosen_node.get_prev_pos().i) && (actual_pos.j == chosen_node.get_prev_pos().j))) 
        {       
          aux_pos.i = actual_pos.i+1;
          aux_pos.j = actual_pos.j;

          aux_cost = 1 + chosen_node.get_cost();
          aux_node.set_cost(aux_cost);
          aux_node.set_prev_mov(1);                // Down
          aux_node.set_pos(aux_pos);
          aux_node.set_prev_pos(chosen_node.get_pos());
          aux_node.set_selected(false);
                          
          if (heuri == 1)
            this->heuristic_1(fin, aux_node);
          if (heuri == 2)
            this->heuristic_2(fin, aux_node);

          aux_node.set_f(aux_node.get_cost() + aux_node.get_heuristic());

          int i = 0;
          bool insert = true;
          while (i < this->analysis_vector_.size()) 
          {
            if (this->analysis_vector_[i] == aux_node)
              insert = false;
            i++;
          }
          if (insert)
            this->analysis_vector_.push_back(aux_node);
          aux_node.clean();
        }
      }

      if ((actual_pos.j-1 >= 0) && ((map[actual_pos.i][actual_pos.j-1] == ' ') || (map[actual_pos.i][actual_pos.j-1] == 'X')))  
      {
        if (!((actual_pos.i == chosen_node.get_prev_pos().i) && (actual_pos.j-1 == chosen_node.get_prev_pos().j))) 
        { 
          aux_pos.i = actual_pos.i;
          aux_pos.j = actual_pos.j-1;

          aux_cost = 1 + chosen_node.get_cost();
          aux_node.set_cost(aux_cost);
          aux_node.set_prev_mov(2);                // Left
          aux_node.set_pos(aux_pos);
          aux_node.set_prev_pos(chosen_node.get_pos());
          aux_node.set_selected(false);
                          
          if (heuri == 1)
            this->heuristic_1(fin, aux_node);
          if (heuri == 2)
            this->heuristic_2(fin, aux_node);

          aux_node.set_f(aux_node.get_cost() + aux_node.get_heuristic());

          int i = 0;
          bool insert = true;
          while (i < this->analysis_vector_.size()) 
          {
            if (this->analysis_vector_[i] == aux_node)
              insert = false;
            i++;
          }
          if (insert)
            this->analysis_vector_.push_back(aux_node);
          aux_node.clean();
        }
      }

      if ((actual_pos.j+1 < map[0].size()) && ((map[actual_pos.i][actual_pos.j+1] == ' ') || (map[actual_pos.i][actual_pos.j+1] == 'X'))) 
      {
        if (!((actual_pos.i == chosen_node.get_prev_pos().i) && (actual_pos.j+1 == chosen_node.get_prev_pos().j))) 
        {
          aux_pos.i = actual_pos.i;
          aux_pos.j = actual_pos.j+1;

          aux_cost = 1 + chosen_node.get_cost();
          aux_node.set_cost(aux_cost);
          aux_node.set_prev_mov(3);                // Right
          aux_node.set_pos(aux_pos);
          aux_node.set_prev_pos(chosen_node.get_pos());
          aux_node.set_selected(false);
                          
          if (heuri == 1)
            this->heuristic_1(fin, aux_node);
          if (heuri == 2)
            this->heuristic_2(fin, aux_node);

          aux_node.set_f(aux_node.get_cost() + aux_node.get_heuristic());

          int i = 0;
          bool insert = true;
          while (i < this->analysis_vector_.size()) 
          {
            if (this->analysis_vector_[i] == aux_node)
              insert = false;
            i++;
          }
          if (insert)
            this->analysis_vector_.push_back(aux_node);
          aux_node.clean();
        }
      }
      chosen_node.clean();
      chosen_node = this->evaluate_position(fin);
      chosen_vector.push_back(chosen_node);

      actual_pos.i = chosen_node.get_pos().i;
      actual_pos.j = chosen_node.get_pos().j;

      if ( (actual_pos.i == fin.i) && (actual_pos.j == fin.j) )
        stop = true;
      else
        stop = false;

      if( (actual_pos.i == ini.i) && (actual_pos.j == ini.j) )
      {
        cout << endl;
        cout << "\033[1m\033[33m" <<" There is no possible way to reach the goal. " << "\033[0m"<< endl; 
        this->optimal_path_.push_back(chosen_vector[0]);
        this->movements_.push_back(this->optimal_path_[0].get_prev_mov());
        return;
      }
    }

    int end = chosen_vector.size()-1;
    bool finalized = false;
    this->optimal_path_.push_back(chosen_vector.back());      // We discard the extra select nodes

    while (!finalized) 
    {
      for (int k = end; k>=0; k--) 
      {
        if ((chosen_vector[k].get_pos().i == this->optimal_path_.back().get_prev_pos().i) && 
        (chosen_vector[k].get_pos().j == this->optimal_path_.back().get_prev_pos().j)) 
        {
          this->optimal_path_.push_back(chosen_vector[k]);
          end = k;
        }
      }
      if (end == 0)
        finalized = true;
    }
    //cout << endl << "  Ordered end nodes:" << endl;     // Optimal path from X to C, we turn it around.
    for (int k = this->optimal_path_.size()-1; k>=0 ; k--) 
    {
      //cout << "  ->" << this->optimal_path_[k];
      this->movements_.push_back(this->optimal_path_[k].get_prev_mov());
    }
  }
  else 
    cout << endl << " Start and end positions are the same. " << endl;
}


void Router::clean(void)                                // Clean up vectors - Attributes
{
  this->analysis_vector_.clear();
  this->optimal_path_.clear();
  this->movements_.clear();
}


int Router::get_nodes_number(void) const                // Returns number of nodes generated      
{
  return this->analysis_vector_.size();
}


vector<int> Router::get_movements(void) const           // Returns the movements vector
{
  return this->movements_;
}
