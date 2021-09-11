/* 

Date: 21/10/2020
Car.h: Contains the definition of the car class    
       
*/


#ifndef CAR
#define CAR

#include <iostream>
#include <vector>
#include "Router.h"


using namespace std;


class Car
{
  private:
    char car_symbol_;                  // Symbol to differentiate the object on the board
    int i_;                            // Position i
    int j_;                            // Position j
    Position initial_position_;        // Starting position of the car
    Position final_position_;          // Final position of the car
    Router path_;                      // Router for path calculation 

  public:
    Car();                             // Builder
    Car(const Car&);                   // Builder overload - Copy
    ~Car();                            // Destroyer
  
    char get_symbol() const;
    int get_i() const;
    int get_j() const;                 // Getters
    vector<int> get_moves() const;
    int get_total_nodes () const; 

    void set_pos(int, int);
    void set_initial_pos(Position);    // Setters
    void set_final_pos(Position);
 
    void calculate_route(vector<vector<char>>, Position, Position, int);    // Invoke router for optimal path calculation.
    void move(vector<vector<char>>&, int);                                  // Move the car on the board 
    friend ostream& operator<< (ostream&, const Car&);                      // Shows the car symbol
};

#endif
