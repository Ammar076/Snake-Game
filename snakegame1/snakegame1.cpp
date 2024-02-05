// Author: Ammar Abdulrahman
// Purpose: A C++ replica of nokia snake game
// credit to Ertjan Arapi for the tutorial https://www.youtube.com/watch?v=gWq0tJLsjRs
 
#include <iostream>
#include <conio.h>   //used for console input output (has some extra features which can be seen below)
#include <windows.h> //used to access the Win32 API functions (https://en.wikipedia.org/wiki/Windows_API)
#include <stdio.h>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

bool GameOver;

int Snake_Speed;                               // variable to determine difficulty (faster snake) 
int Game_Mode;                                 // variable to determine mode                       

const int height = 20;                         // the height of the gameboard
const int width = 20;                          // the width of the game board

string name;
fstream Score_Saver;

int x, y, 
    fruitX, fruitY, 
    score, High_Score1, 
    wallX, wallX_1, 
    wallX_2, wallX_3, 
    wallX_4, wallX_5;

int wallY, wallY_1, 
    wallY_2, wallY_3, 
    wallY_4, wallY_5;

int tailX[100], 
    tailY[100], 
    nTail;         // variables for tail postion and length 

enum eDirection { STOP, UP, DOWN, LEFT, RIGHT, ESC, PLAY };     // constants to represent the direction the snake is going in
eDirection dir;                                                


void Setup() 
{
    GameOver = false;
    
    score = 0;
    nTail = 0;
    
    dir = STOP;
    
    x = width / 2;                               // determines the horizontal position of the snake
    y = height / 2;                              // determines the vertical postion of the snake
    
    fruitX = rand() % width + 1;           // randomised fruit position for x axis
    fruitY = rand() % height + 1;              // randomised fruit position for x axis

    Score_Saver.open("Score.txt", ios_base::in);        // stream for previous highscore
    
    if (!Score_Saver.is_open())
    {                  
        cout << "Open file failed" << endl;
        return;
    }
    Score_Saver >> High_Score1 >> name;
    
    Score_Saver.close();
    
    if (Score_Saver.is_open()) 
    {
        cout << "Stream could not close!" << endl;
        return;
    }
}

void Mode_0() 
{
    system("CLS");                                  // Updates the screen
    
    cout << setw(70) << "WELCOME TO SNAKE GAME!!!" << endl;

    for (int i = 0; i <= width + 1; i++)             // draws beginning of board
    {           
        cout << "#";
    }
    cout << endl;

    for (int i = 1; i <= height; i++) 
    {                
        for (int j = 1; j <= width + 2; j++) 
        {             
            if (j == 1 || j == width + 2)           // prints left and right wall
            {           
                cout << "#";
            }
            else if (i == y && j == x)              // prints the Head of the snake on the board
            {                       
                cout << "O";
            }
            else if (i == fruitY && j == fruitX)    // prints the fruit on the board
            {  
                cout << "*";
            }
            else                                    // prints the rest of the board
            {                            
                bool print = false;
                
                for (int k = 0; k < nTail; k++) 
                {
                    if (i == tailY[k] && j == tailX[k]) // prints the tail of the snake
                    {  
                        cout << "o";
                        print = true;
                    }
                }
                if (!print) 
                {
                    cout << " ";
                }
            }
        }
        cout << endl;
    }

    for (int i = 0; i <= width; i++) // draws end of board
    {               
        cout << "#";
    }
    cout << endl << endl;

    cout << setw(50) << "Score: " << score << endl;

    cout << setw(45) << "Highscore: " << High_Score1 << endl << endl;
}

void Mode_1() {                                // Same as the above but prints random walls for mode 1 
    wallX = rand() % width + 1;                // randomized wall location
    wallY = rand() % height + 1;
    
    wallX_1 = rand() % width + 1;
    wallY_1 = rand() % height + 1;
   
    wallX_2 = rand() % width + 1;
    wallY_2 = rand() % height + 1;
    
    wallX_3 = rand() % width + 1;
    wallY_3 = rand() % height + 1;
   
    wallX_4 = rand() % width + 1;
    wallY_4 = rand() % height + 1;
   
    wallX_5 = rand() % width + 1;
    wallY_5 = rand() % height + 1;
    
    system("CLS");                             

    for (int i = 0; i <= width +1; i++)            
    {           
        cout << "#";
    }
    cout << endl;

    for (int i = 1; i <= height; i++) 
    {               
        for (int j = 1; j <= width + 2; j++)            // +2 to make actual playable board 20*20
        {         
            if (j == 1 || j == width + 2)               // prints left and right wall CHECK THIS NOW
            {             
                cout <<  "#";
            }
            else if (i == y && j == x)                  
            {                          
                cout << "O";
            }
            else if (i == fruitY && j == fruitX)       
            {      
                cout << "*";
            }
            else if (i == wallY && j == wallX) 
            {
                cout << "#";
            }
            else if (i == wallY_1 && j == wallX_1)       // prints the random walls on the board
            {    
                cout << "#";
            }
            else if (i == wallY_2 && j == wallX_2) 
            { 
                cout << "#";
            }
            else if (i == wallY_3 && j == wallX_3) 
            { 
                cout << "#";
            }
            else if (i == wallY_4 && j == wallX_4) 
            { 
                cout << "#";
            }
            else if (i == wallY_5 && j == wallX_5)
            { 
                cout << "#";
            }
            else                                        
            {                           
                bool print = false;
                
                for (int k = 0; k < nTail; k++) 
                {
                    if (i == tailY[k] && j == tailX[k])         
                    {  
                        cout << "o";
                        
                        print = true;
                    }
                }
                if (!print) 
                {
                    cout << " ";
                }
            }
        }
        cout << endl;
    }

    for (int i = 0; i <= width +1; i++) 
    {
        cout << "#";
    }
    cout << endl << endl; 
    
    cout << setw(50) << "Score: " << score << endl;

    cout << setw(45) << "Highscore: " << High_Score1 << endl << endl;
}

void Input() {
    if (_kbhit())               //part of conio.h - takes in the input from keyboard and moves the snake (kbhit [determines if a key has been pressed or not])
    {            
        switch (_getch())       //part of conio.h - Gets a character from the console without echo(without displaying the key pressed).
        {    
            case 'w':
                dir = UP;
                break;
            
            case 'a':
                dir = LEFT;
                break;
            
            case 's':
                dir = DOWN;
                break;
            
            case 'd':
                dir = RIGHT;
                break;
            
            case 72:
                dir = UP;
                break;
            
            case 75:
                dir = LEFT;
                break;
            
            case 80:
                dir = DOWN;
                break;
            
            case 77:
                dir = RIGHT;
                break;
            
            case 27:
                cout << "press any key to continue" << endl;
                cin.get();
                break;
            
            case 'x':
                exit(0);
                break;
            
            default:
                break;
        }
    }
}
void Logic() {

    int prevX = tailX[0];                     // for cycle 
    int prevY = tailY[0];                     // for cycle 
    
    tailX[0] = x;                             // initiates the cycle for the tail follow the head
    tailY[0] = y;                             // initiates the cycle for the tail follow the head
    
    int prev2X, prev2Y;

    for (int i = 1; i < nTail; i++)           // makes tail follow the head  
    {         
        prev2X = tailX[i];
        prev2Y = tailY[i];
        
        tailX[i] = prevX;
        tailY[i] = prevY;
        
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir) 
    {                              // based on input changes the movement of snake 
        case UP:
            y--;
            break;
    
        case DOWN:
            y++;
            break;
    
        case LEFT:
            x--;
            break;
    
        case RIGHT:
            x++;
            break;
    
        default:
            break;
    }

    if (x <= 1 || x > width + 1 || y <= 0 || y > height) // ends game if snake hits borders
    {    
        cout << "\t\tGame Over\n";
        cout << "\t    You hit the wall!" << endl;
        
        GameOver = true;
    }
    for (int i = 0; i < nTail; i++) {               // ends game if snake hits its tail
        if (tailX[i] == x && tailY[i] == y) 
        {
            cout << "\t\tGame Over\n";
            cout << "\t    You hit your tail!" << endl;
            
            GameOver = true;
        }
    }
    if (x == wallX && y == wallY)                   // ends game if snake hits borders
    {    
        cout << "\t\tGame Over\n";
        cout << "\t    You hit the wall!" << endl;
        
        GameOver = true;
    }
    if (x == wallX_1 && y == wallY_1) 
    {    
        cout << "\t\tGame Over\n";
        cout << "\t    You hit the wall!" << endl;
        
        GameOver = true;
    }
    if (x == wallX_2 && y == wallY_2) 
    {   
        cout << "\t\tGame Over\n";
        cout << "\t    You hit the wall!" << endl;
        
        GameOver = true;
    }
    if (x == wallX_3 && y == wallY_3) 
    {    
        cout << "\t\tGame Over\n";
        cout << "\t    You hit the wall!" << endl;
        
        GameOver = true;
    }
    if (x == wallX_4 && y == wallY_4) 
    {    
        cout << "\t\tGame Over\n";
        cout << "\t    You hit the wall!" << endl;
        
        GameOver = true;
    }
    if (x == wallX_5 && y == wallY_5) 
    {    
        cout << "\t\tGame Over\n";
        cout << "\t    You hit the wall!" << endl;
        
        GameOver = true;
    }
    if (x == fruitX && y == fruitY)                  // makes snake eat fruit
    {               
        
        score += 10;
        nTail++;                                    // determines the length of the tail 
        
        fruitX = rand() % width + 1;                //spawn another fruit, both this an line below 
        fruitY = rand() % height + 1;
    }
}
void High_Score() 
{
    Score_Saver.open("Score.txt", ios_base::out);         // opens an output stream
    
    if (!Score_Saver.is_open())                           // checks if stream was opened successfuly  
    {                        
        cout << "File could not be opened!" << endl;
        
        return;
    }
    cout << "Please enter your name: ";
    cin >> name;
  
    if (High_Score1 <= score)                             // checks if score is more than highscore
    {                          
        High_Score1 = score;
        
        Score_Saver << High_Score1;
    }
    Score_Saver.close();                                 // checks if stream was closed successfuly
    
    if (Score_Saver.is_open()) 
    {
        cout << "Stream could not close!" << endl;
        return;
    }

}

int main()
{

    while (!GameOver) 
    {        
        system("COLOR 80");

        srand(time(NULL));
        
        cout << "Press w, a, s, d for up, left, down and right respectively. (You can also use arrow keys!)\n";

        cout << "Press esc to pause the game.\n";

        cout << "Press x to end the game!\n";

        cout << "choose a difficulty from 1 to 4(hardest):";    // determines the speed of loop through speed function
        cin >> Snake_Speed;
        
        cout << endl << "1 for random spawning walls, 2 for normal version:";   //determines mode
        cin >> Game_Mode;
        
        cout << "Press w, a, s, d for up, left, down and right respectively. (You can also use arrow keys!)\n\n";

        cout << "Press esc to pause the game.\n\n";

        cout << "Press x to end the game!\n\n";
        
        Setup();
        
        while (!GameOver) 
        {
            if (Game_Mode == 1) 
            {
                Mode_1();                        // mode 1 with random walls
            }
            else 
            {
                Mode_0();                        // mode 0 without random walls
            }
            Input();
            
            Logic();
            
            switch (Snake_Speed) 
            {
                case 1:
                    Sleep(200);                              // determines the time it takes to loop
                    break;
                case 2:
                    Sleep(150);
                    break;
                case 3:
                    Sleep(70);
                    break;
                case 4:
                    Sleep(20);
                    break;
                default:
                    Sleep(200);
                    break;
            }
        }
        High_Score();                              // to save highscore
        
        if (GameOver) 
        {
            Sleep(1000);
            
            GameOver = false;                      // loops game
        }
    }
    return 0;
}
