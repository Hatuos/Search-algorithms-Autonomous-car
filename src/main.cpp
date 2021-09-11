#include <iostream>
#include "Board.h"
#include <ctime>

using namespace std;

void euclidean_simulation(Board& board)
{
  unsigned t0, t1;
  double time;
  
  cout << "  Initial state of the board - Euclidean distance: " << endl;
  cout << board << endl;

  t0 = clock();
  board.find_way(1);  // Euclidean distance
  t1 = clock();
  time = (double(t1-t0)/CLOCKS_PER_SEC);
  cin.get();

  for (int i = 1; i < board.get_car().get_moves().size(); i++) 
  {
    board.move_car(board.get_car().get_moves()[i]);
  }

  cout << endl << endl;
  cout << board << endl << endl << endl;
  cout << "  Simulation data - Euclidean distance heuristic " << endl;
  board.show_simu_info(cout);
  cout << "  Execution time: " << time << endl;
  cout << "  Press enter to continue with the next heuristic test";
  cin.get();
  
  return;
}


void straight_line_simulation(Board& board)
{
  unsigned t0, t1;
  double time;
  
  cout << "  Initial state of the board - Straight line distance: " << endl;
  cout << board << endl;

  t0 = clock();
  board.find_way(2); // Straight line distance
  t1 = clock();
  time = (double(t1-t0)/CLOCKS_PER_SEC);
  cin.get();

  for (int i = 1; i < board.get_car().get_moves().size(); i++) 
  {
    board.move_car(board.get_car().get_moves()[i]);
  }
  
  cout << endl << endl;
  cout << board << endl << endl << endl;
  cout << "  Simulation data - Heuristic straight distance " << endl;
  board.show_simu_info(cout);
  cout << "  Execution time: " << time << endl;
  cout << "  Press enter to continue with the next heuristic test";
  cin.get();
  
  return;
}

int main() 
{
  cout << endl << endl;
  cout << "  Autonomous car simulation" << endl;
  cout << "  Press enter to start testing";
  cin.get();


  Board board_1(50, 50);
  board_1.resize();
  board_1.place_car();
  board_1.place_obstacles();
  Board board_2(board_1);

  cout << endl << endl << endl;
  euclidean_simulation(board_1);
  
  cout << endl << endl << endl;
  straight_line_simulation(board_2);
 

  return 0;
}
