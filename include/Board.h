/* 

Date: 21/10/2020
Board.h: Contains the definition of the board class    
                    
*/

#ifndef BOARD
#define BOARD

#include <iostream>
#include <vector>
#include <fstream>
#include "Car.h"


using namespace std;


class Board 
{
  private:
    vector<vector<char>> map_;          // Matrix that makes up the board
    Car car_;                           // Car object to move on the board
    Position car_initial_position_;     // Car start position
    Position car_final_position_;       // Car target position
    float obs_percent_;                 // Percentage of obstacles on the board - Default: Random Distr.

  public:
    Board();                            // Builder
    Board(int, int);                    // Constructor overload - Parameters
    Board(const Board&);                // Constructor overload - Copy
    ~Board();                           // Destroyer

    Position get_initial_pos() const;
    Position get_final_pos() const;
    char get_board_symbol(int, int) const;
    Car get_car() const;                       // Getters
    int get_row() const;
    int get_col() const;
    float get_obs_percent() const;
 
    void set_initial_pos(int, int);
    void set_final_pos(int, int);
    void set_board_symbol(int, int, char);     // Setters
    void set_row(int);
    void set_col(int);
    void set_obs_percent(float);
    
    void resize();                             // Resize board
    void place_car();                          // Position car on board
    void place_obstacles();                    // Position obstacles on the board
    void find_way(int);                        // Car -> Router -> Find optimal path
    void move_car(int);                        // Move car on dash
    
    friend ostream& operator<<(ostream&, const Board&);   // Show dashboard on screen
    ostream& show_simu_info(ostream&);                    // Shows simulation information
};

#endif
