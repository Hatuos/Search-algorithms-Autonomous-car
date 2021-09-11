#include "../include/Board.h"


Board::Board(void) : obs_percent_(0.0)   // Builder
{
}


Board::Board(int M, int N)               // Constructor overload - Parameters
{
  this->map_.clear();
  this->map_.resize(M);
  for (int i = 0; i < M; i++)
  {
    this->map_[i].clear();
    this->map_[i].resize(N);
  }
}


Board::Board(const Board& board) : car_(board.car_)    // Constructor overload - Copy
{
  map_ = board.map_;
  car_initial_position_ = board.car_initial_position_;
  car_final_position_ = board.car_final_position_;
  obs_percent_ = board.obs_percent_;
}


Board::~Board()                                        // Destroyer
{
}


int Board::get_row(void) const                         // Returns number of rows           
{
  return (this->map_.size());
}


int Board::get_col(void) const                         // Returns number of columns       
{
  return (this->map_[0].size());
}


char Board::get_board_symbol(int i, int j) const       // Returns board symbol
{
  return (this->map_[i][j]);
}


Car Board::get_car(void) const                         // Returns car object
{
  return (this->car_);
}


float Board::get_obs_percent(void) const               // Returns the percentage of targets on the board
{
  return (this->obs_percent_);
}


void Board::set_row(int n)                             // Set number of rows 
{
 this->map_.resize(n);
}

                                                       
void Board::set_col(int m)                             // Set number of columns 
{
  for (int i = 0; i < this->get_row(); i++)
    this->map_[i].resize(m);
}


void Board::set_board_symbol(int i, int j, char x)     // Sets a board symbol 
{
  this->map_[i][j] = x;
}


void Board::set_obs_percent(float p)                   // Sets the percentage of obstacles on the board
{
  this->obs_percent_ = p;
}


void Board::resize(void)                               // Resize board
{
  char option;
  do 
  { 
    cout << endl << " Default board dimensions: " << this->get_row() << " x " << this->get_col() << endl;
    cout << " Do you want to resize it? (y/n): ";
    cin >> option;
    cin.get();

    switch (option) 
    {
      case 'y': 
      {
        int n = 0, m = 0;
        cout << " Nº of rows: ";
        cin >> n;
        cin.get();
        cout << " Nº of columns: ";
        cin >> m; 
        cin.get();

        this->set_row(n);
        this->set_col(m);
        break;
      }
      
      case 'n':
      {
        break;
      }
     
      default:
      {
        cout << endl << " Invalid option! " << endl;
        break;
      }
    }
  } while ( (option!='y') && (option!='n') );

  for (int i = 0; i < this->get_row(); i++)
  {
    for (int j = 0; j < this->get_col(); j++) 
    {
      this->map_[i][j] = ' ';
    }
  }

}
                                                          
                                                        
void Board::place_car(void)                            // Position car on board
{
  char option;

  do 
  {
    cout << endl << " Dimensions of the board: " << this->get_row() << " x " << this->get_col() << endl;
    cout << " Do you want to enter the car position manually or randomly? (m/r): ";
    cin >> option;
    cin.get();

    switch (option) 
    {
      case 'm':
      {
        int i, j;
        bool correcto = true;

        do 
        {
          correcto = true;
          cout << endl << " Initial coordinate i [0, " << this->get_row()-1 << "]: ";
          cin >> i;
          cin.get();
          cout << endl << " Initial coordinate j [0, " << this->get_col()-1 << "]: ";
          cin >> j;
          cin.get();

          if ( (i < 0) || (i > this->get_row()-1) || (j < 0) || (j > this->get_col()-1) ) 
          {
            cout << endl << " Invalid coordinates! " << endl; 
            correcto = false;
          }

        } while (!correcto);

        this->car_.set_pos(i, j);
        this->set_initial_pos(i, j);
        this->set_board_symbol(i, j, this->car_.get_symbol());
    
        do 
        {
          correcto = true;
          cout << endl << " Final coordinate i [0, " << this->get_row()-1 << "]: ";
          cin >> i;
          cin.get();
          cout << endl << " Final coordinate j [0, " << this->get_col()-1 << "]: ";
          cin >> j;
          cin.get();

          if ( (i < 0) || (i > this->get_row()-1) || (j < 0) || (j > this->get_col()-1) ) 
          {
            cout << endl << " Invalid coordinates! " << endl; 
            correcto = false;
          }

        } while (!correcto);

        this->set_final_pos(i, j);
        break;
      }

      case 'r':
      {

        int i, j;
 
        srand(time(NULL));

        i = rand() % this->get_row();
        j = rand() % this->get_col();

        this->car_.set_pos(i, j);
        this->set_initial_pos(i, j);
        this->set_board_symbol(i, j, this->car_.get_symbol());

        srand(time(NULL)*i);

        i = rand() % this->get_row();
        j = rand() % this->get_col();

        this->set_final_pos(i, j);
        break;
      }
      default:
      {
        cout << " Invalid option! " << endl;
        break;
      }
    }
  } while( (option!='m') && (option!='r') );
}
                                                                        
                                                                                                    
void Board::set_initial_pos(int x, int y)              // Sets initial position on the board
{
  this->car_initial_position_.i = x;
  this->car_initial_position_.j = y;
  this->car_.set_initial_pos(car_initial_position_);
}


void Board::set_final_pos(int x, int y)                // Sets final position on the board
{
  this->car_final_position_.i = x;
  this->car_final_position_.j = y;
  this->set_board_symbol(x, y, 'X');
  this->car_.set_final_pos(car_final_position_);
}


Position Board::get_initial_pos(void) const            // Gets initial position from the board
{
  return this->car_initial_position_;
}


Position Board::get_final_pos(void) const              //  Gets final position from the board
{
  return this->car_final_position_;
}


void Board::place_obstacles(void)                      // Position obstacles on the board
{
  char option;
  char p;
  float percent = 0.0;

  do 
  {
    cout << endl << " Default percentage of board items: 0.3";
    cout << endl << " Do you want to change this percentage? (y/n) ";
    cin >> p;
    cin.get();

    switch (p) 
    {
      case 'y':
      {
        cout << endl << " Percentage of obstacles: ";
        cin >> percent; 
        cin.get();
        this->set_obs_percent(percent);
        break;
      }
       
      case 'n':
      {
        this->set_obs_percent(0.3);
        break;
      }
      
      default:
      {
        cout << " Invalid option! " << endl;
        break;
      }
    }
  } while ( (p !='y') && (p!='n') );
  
  do
  {
    int total_obs = ( (this->get_row()*this->get_col()) * this->get_obs_percent() );

    cout << endl << " The board will create a total of " << total_obs << " obstacles in the random option " << endl;
    cout << " Do you want to enter the objects manually or randomly? (m/r): ";
    cin >> option; 
    cin.get();

    switch (option) 
    {
      case 'm':
      {
        char option_2;
        do 
        {
          cout << endl << "Do you want to enter the obstacles by keyboard or file? (k/f): ";
          cin >> option_2;
          cin.get();

          switch (option_2) 
          {
            case 'f': 
            {
              string fich_entrada = "../data/obs_data.txt";
              ifstream fich;
              fich.open(fich_entrada.c_str());

              if (fich.is_open()) 
              {
                fich >> total_obs;
                
                for (int i = 0; i < total_obs; i++) 
                {
                  int x = 0, y = 0;

                  fich >> x >> y;
                  
                  if ( (this->get_board_symbol(x, y) != 'C') && (this->get_board_symbol(x, y) != 'X') )
                    this->set_board_symbol(x, y, '1');
                }
                fich.close();
              }
              else 
              {
              cerr << endl << "Error opening the file" << endl;
              }
              percent = (float) total_obs / (float) (this->get_row()*this->get_col());
              this->set_obs_percent(percent);
              break;
            }

            case 'k': 
            {
              cout << endl << " Number of obstacles: ";
              cin >> total_obs; 
              cin.get();

              int x = 0, y = 0;

              cout << " Enter the coordinate [i, j] within the interval [0," << this->get_col()-1 << "]" << endl;
              for (int i = 0; i < total_obs; i++)
              {
                cout << "i > ";
                cin >> x;
                cout << "j > ";
                cin >> y;
                cin.get();

                if ( (this->get_board_symbol(x, y) != 'C') && (this->get_board_symbol(x, y) != 'X') )
                  this->set_board_symbol(x, y, '1');
              }
              percent = (float) total_obs / (float) (this->get_row()*this->get_col());
              this->set_obs_percent(percent);
              break;
            }
            
            default:
            {
              cout << " Invalid option! " << '\n';
              break;
            }
          } 
        } while((option_2!='f') && (option_2!='k'));
        break; 
      }
       
      case 'r':
      {
        int x, y, counter = 0;

        for (int i = 0; i < total_obs; i++) 
        {
          srand(time(NULL)+counter);
          x = rand() % this->get_row();
          y = rand() % this->get_col();

          if (this->get_board_symbol(x, y) == '1')
            i--;
          else if (this->get_board_symbol(x, y) == 'C') 
            i--;
          else if ((this->get_initial_pos().i == x) && (this->get_initial_pos().j == y))
            i--;
          else if ((this->get_final_pos().i == x) && (this->get_final_pos().j == y)) 
            i--;
          else 
            this->set_board_symbol(x, y, '1');
          
          counter++;
        }
        break;
      }
      
      default:
      {
        cout << " Invalid option! " << '\n';
        break;
      }
    }
  } while ( (option!='m') && (option!='r'));
}


void Board::find_way(int heure)                        // Car -> Router -> Find optimal path
{
  this->car_.calculate_route(this->map_, this->car_initial_position_, this->car_final_position_, heure);
}


void Board::move_car(int direction)                    // Move car on dash
{
  this->car_.move(this->map_, direction);
}


ostream& operator<< (ostream& os, const Board& map)    // Show dashboard on screen
{
  os << endl << " ";
  for (int i = 0; i < map.get_col(); i++)
  {
    if (i == 0)	
      os << "---";

    os << "--";
  }

  for (int i = 0; i < map.get_row(); i++)
  {
    os << endl << "  |";
    for (int j = 0; j < map.get_col(); j++) 
    {
      switch ( map.get_board_symbol(i,j) ) 
      {
        case '1':
          os << "\033[0;91m" << map.get_board_symbol(i,j) <<"\033[0m";
          break;

        case 'C':
          os << "\033[1m\033[33m" << map.get_board_symbol(i,j) <<"\033[0m";
          break;

        case 'X':
          os << "\033[1m\033[33m" << map.get_board_symbol(i,j) <<"\033[0m";
          break;
        
        case '*':
          os << "\033[1m\033[33m" << map.get_board_symbol(i,j) <<"\033[0m";
          break;
        
        default: 
          os << "\033[0;97m" << map.get_board_symbol(i,j) <<"\033[0m";
          break;
      }
      os << "│";
    }
    os << endl << " ";
    for (int i = 0; i < map.get_col(); i++)
    {
      if (i == 0)	
        os << "---";

      os << "--";
    }
  }

  os << endl << "  Starting point: [" << map.get_initial_pos().i << ", " << map.get_initial_pos().j << "]";
  os << endl << "  Target point: [" << map.get_final_pos().i << ", " << map.get_final_pos().j << "]";
  return os; 
}


ostream& Board::show_simu_info(ostream &os)    // Shows simulation information
{
  os << "  Starting point: [" << this->get_initial_pos().i << ", " << this->get_initial_pos().j << "]" << endl;
  os << "  Target point: [" <<  this->get_final_pos().i << ", " <<  this->get_final_pos().j << "]" << endl;
  os << "  Dimension: " << this->get_row() << " x " << this->get_col() << endl;
  os << "  Percentage of obstacles: " << this->get_obs_percent()*100 << "%" << endl;
  os << "  Nodes generated: " << this->get_car().get_total_nodes() << endl;
  os << "  Optimum path length: " << this->get_car().get_moves().size() << endl;
}
