#include "../include/Car.h"


Car::Car(void) : car_symbol_('C'), i_(0), j_(0), initial_position_(), final_position_(), path_()    // Builder
{
}


Car::Car(const Car& car) : path_(car.path_)           // Builder overload - Copy
{
  car_symbol_ = car.car_symbol_;
  i_ = car.i_;
  j_ = car.j_;
  initial_position_ = car.initial_position_;
  final_position_ = car.final_position_;
}


Car::~Car()                                           // Destroyer
{
}


char Car::get_symbol(void) const                      // Returns the car symbol
{
  return this->car_symbol_;
}


int Car::get_i(void) const                            // Returns position i
{
  return this->i_;
}


int Car::get_j (void) const                           // Returns position j
{
  return this->j_;
}


vector<int> Car::get_moves(void) const                // Returns the vector of movements of the optimal path
{
  return this->path_.get_movements();
}


int Car::get_total_nodes () const                     // Returns the number of analysed nodes
{
  return this->path_.get_nodes_number();
}


void Car::set_pos(int i, int j)                       // Sets position i,j of the car
{
  this->i_ = i;
  this->j_ = j;
}


void Car::set_initial_pos (Position x)                // Sets initial position of the car
{
  this->initial_position_.i = x.i;
  this->initial_position_.j = x.j;
}


void Car::set_final_pos(Position x)                   // Sets final position of the car
{
  this->final_position_.i = x.i;
  this->final_position_.j = x.j;
}


void Car::calculate_route(vector<vector<char>> map, Position ini, Position fin, int heuri)   // Calculation of optimal path - A*
{
  this->path_.clean();
  this->path_.calculate(map, ini, fin, heuri);
  cout << endl << "   Press enter to display the optimal path";
}


void Car::move(vector<vector<char>>& map, int direction)       // Move the car on the board 
{
  bool completed = false;
  do 
  {
    int mov = direction;
    switch (mov) 
    {
      case 0:    // Up
      {
        if (this->get_i()-1 >= 0) 
        {
          if (map[this->get_i()-1][this->get_j()] != '1') 
          {
            map[this->get_i()-1][this->get_j()] = 'C';
            map[this->get_i()][this->get_j()] = '*';
            this->set_pos( this->get_i()-1, this->get_j() );
            completed = true;
          }
        }
        break;
      }

      case 1:    // Down
      {
        if (this->get_i()+1 < map.size()) 
        {
          if (map[this->get_i()+1][this->get_j()] != '1') 
          {
            map[this->get_i()+1][this->get_j()] = 'C';
            map[this->get_i()][this->get_j()] = '*';
            this->set_pos( this->get_i()+1, this->get_j() );
            completed = true;
          }
        }
        break;
      }
   
      case 2:    // Left
      {
        if (this->get_j()-1 >= 0) 
        {
          if (map[this->get_i()][this->get_j()-1] != '1') 
          {
            map[this->get_i()][this->get_j()-1] = 'C';
            map[this->get_i()][this->get_j()] = '*';
            this->set_pos(this->get_i(), this->get_j()-1);
            completed = true;
          }
        }
        break;
      }
      
      case 3:    // Right
      {
        if (this->get_j()+1 < map[0].size()) 
        {
          if (map[this->get_i()][this->get_j()+1] != '1') 
          {
            map[this->get_i()][this->get_j()+1] = 'C';
            map[this->get_i()][this->get_j()] = '*';
            this->set_pos(this->get_i(), this->get_j()+1);
            completed = true;
          }
        }
        break;
      }
    }
  }while (!completed);
}


ostream& operator<< (ostream& os, const Car& car)             // Shows the car symbol
{
  os << car.get_symbol();
  return os;
}
