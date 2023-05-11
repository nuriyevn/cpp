// +2:30
// +1:50
// +2:00
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <windows.h> // This is windows specific library. It's extensively used for development under windows.
// There are hundreds of library headers for windows, but this one is the most used and common library for windows development
// Other libraries are built on top of this library.
#include <time.h>

#define BOARD_WIDTH  8 // Board width in characters
#define BOARD_HEIGHT 8 // Board height in characters
#define B_SIZE 4        // Board size in elements. Show be even
#define MOVE_LEFT   VK_LEFT - 37
#define MOVE_UP     VK_UP - 37
#define MOVE_RIGHT  VK_RIGHT - 37
#define MOVE_DOWN   VK_DOWN - 37
#define WHITE_COLOR FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY
using namespace std;

// Function prototypes
//
void DrawCell(int x, int y, int number = 2);

long long int g_score = 0;
int g_tile = 2;
bool move_failed[4];

HANDLE hStdout;

bool isGameOver(void)
{
    return (move_failed[0] && move_failed[1] && move_failed[2] && move_failed[3]);
}

// Checking whether two matrixes has any difference.
// We must generate number number only if there is something
// has been reduced.
int hasDiff(int c[B_SIZE][B_SIZE], int cc[B_SIZE][B_SIZE])
{
    int result = 0;
    for (int i = 0; i < B_SIZE; i++)
        for (int j = 0; j < B_SIZE; j++)
            if (c[i][j] != cc[i][j])
            {
                result = 1;
                return result;
            }

    return result;
}

// Sliding a single row, vector.
// Sliding occurs from left to right.
// If we need to slide from right to left, we simple reverse and array in higher lever function - reduceBoard()
void slideRow(int a[B_SIZE])
{
    int i = B_SIZE - 1;

    int iter = B_SIZE / 2;
    if (B_SIZE % 2 == 1)
        iter++;

    while (iter--)
    {
        // find first invalid.
        int first_invalid = -1; // initially we assume that there is no invalid.

        for (int j = i; j >= 0; j--)
            if (a[j] == -1)
            {
                //printf("first invalid index = %d\n", j);
                first_invalid = j;
                break;
            }

        if (first_invalid == -1)
            return; // nothing to slide.

        int first_valid = max(first_invalid - 1, 0);

        // find first valid
        while (first_valid >= 0)
        {
            if (a[first_valid] != -1)
                break;
            first_valid--;
        }

        first_valid = max(first_valid, 0);

        // shift
        int shift_size = first_invalid - first_valid;
        for (int j = first_valid; j >=0; j--)
            a[j + shift_size] = a[j];

        // filling unused
        for (int j = 0; j< shift_size; j++)
            a[j] = -1;
    }
}

// Reducing single row, represented as an array.
// It's not depending on direction
// Direction dependence decision has been taken in a higher level function
// reduceBoard()
void reduceRow(int a[B_SIZE])
{
    int i = B_SIZE - 1;

    for (i = B_SIZE - 1; i >= 0; i-- )
    {
        if (a[i] == a[i-1] && a[i] != -1)
        {
            a[i] = a[i] * 2;
            g_score += a[i];
            if (a[i] > g_tile)
                g_tile = a[i];

            a[i-1] = -1;

        }
    }
    slideRow(a);
}

// Debug informatino
void DebugPrint(int c[B_SIZE][B_SIZE])
{
    COORD pos = {0, 40};
    SetConsoleCursorPosition(hStdout, pos);

    for (int i = 0; i < B_SIZE; i++)
    {
        for (int j = 0; j < B_SIZE; j++)
            printf("%d ", c[i][j]);
        printf("\n");
    }
    /*for (int i = 0; i < B_SIZE; i++)
        printf("%d ", c[row][i]);*/
}

// Drawing all elements. functions slideBoard and reduceBoard make calculation.
// This function updates the table.
void updateBoard(int c[B_SIZE][B_SIZE])
{
    for (int i = 0; i < B_SIZE; i++)
    {
        for (int j = 0; j < B_SIZE; j++)
            DrawCell(j, i, c[i][j]);
    }

    //DebugPrint(c);
}


// Just sliding elements to the corresponding directions
void slideBoard(int c[B_SIZE][B_SIZE], int direction)
{
    // do stuff
    int row = 0;
    for (row = 0; row < B_SIZE; row++)
    {
        int vect[B_SIZE];
        if (direction == VK_RIGHT)
        {
            slideRow(c[row]);
        }
        else if (direction == VK_LEFT)
        {
            for (int i = 0; i < B_SIZE; i++)
                vect[i] = c[row][B_SIZE - i - 1];

            slideRow(vect);

            for (int i = 0; i < B_SIZE; i++)
                c[row][i] = vect[B_SIZE - i - 1];
        }
        else if (direction == VK_DOWN)
        {
            for (int i = 0; i < B_SIZE; i++)
                vect[i] = c[i][row];
            slideRow(vect);

            for (int i = 0; i < B_SIZE; i++)
                c[i][row] = vect[i];
        }
        else if (direction == VK_UP)
        {
            for (int i = 0; i < B_SIZE; i++)
                vect[B_SIZE - i - 1] = c[i][row];
            slideRow(vect);

            for (int i = 0; i < B_SIZE; i++)
                c[i][row] = vect[B_SIZE - i - 1];
        }
    }

}

// Will reduce board instead of 2 and 2 will give 4 is corresponding position.
// There can be few reducings.
void reduceBoard(int c[B_SIZE][B_SIZE], int direction)
{
    // do stuff
    int row = 0;
    for (row = 0; row < B_SIZE; row++)
    {
        int vect[B_SIZE];
        if (direction == VK_RIGHT)
        {
            reduceRow(c[row]);
        }
        else if (direction == VK_LEFT)
        {
            for (int i = 0; i < B_SIZE; i++)
                vect[i] = c[row][B_SIZE - i - 1];

            reduceRow(vect);

            for (int i = 0; i < B_SIZE; i++)
                c[row][i] = vect[B_SIZE - i - 1];
        }
        else if (direction == VK_DOWN)
        {
            for (int i = 0; i < B_SIZE; i++)
                vect[i] = c[i][row];
            reduceRow(vect);

            for (int i = 0; i < B_SIZE; i++)
                c[i][row] = vect[i];
        }
        else if (direction == VK_UP)
        {
            for (int i = 0; i < B_SIZE; i++)
                vect[B_SIZE - i - 1] = c[i][row];
            reduceRow(vect);

            for (int i = 0; i < B_SIZE; i++)
                c[i][row] = vect[B_SIZE - i - 1];
        }
    }
}

// Generate new random position
// if there is no place to put (board is full) then return false;

bool putNewNumber(int c[B_SIZE][B_SIZE], int *x, int *y)
{
    bool result = false; //

    // This will generate random number from [0 to B_SIZE * B_SIZE - 1]
    // In our case from [0 to 15]
    int position = rand() % (B_SIZE * B_SIZE);

    int i, j;
    int empty_count = 0;

    for (i = 0; i < B_SIZE; i++)
        for (j = 0; j < B_SIZE ; j++)
            if (c[i][j] == -1)
                empty_count++;


    if (empty_count == 0)
        return false;

    position = position % empty_count;

    for (i = 0; i < B_SIZE && position > -1 ; i++)
    {
        for (j = 0; j < B_SIZE && position > -1; j++ )
        {
            if (c[i][j] == -1)
                position--;
            if (position == -1)
            {
                *x = i;
                *y = j;
                return true;
            }
        }
    }
}

void DrawCell(int x, int y, int number)
{

    if ((unsigned int)number & ((unsigned int)number - 1) == 0)
    {
        printf("Unexpected error: specified number is not a power of 2.\n");
        return;
    }

    int i,j ;
    //Sleep(5);
    COORD pos = {0};
    pos.X = 1+BOARD_WIDTH*x;
    pos.Y = 2+BOARD_WIDTH*y/2;

    SetConsoleCursorPosition(hStdout, pos);

    if (number == -1) // just for space;
    {
        pos.X = BOARD_WIDTH*x + 1;
        SetConsoleCursorPosition(hStdout, pos);
        for (int i = 0; i < BOARD_WIDTH - 1; i++)
            cout << ' ';
    }
    else
    {
        //SetConsoleTextAttribute()

        int n2 = number;
        int degree = 0;
        while (n2 != 1)
        {
            n2 /= 2;
            degree++;
        }
        SetConsoleTextAttribute(hStdout, degree);
        printf("%6d", number); // make it with cout.
    }
}

void writeScore(void)
{
    COORD pos = {0, 18};
    SetConsoleCursorPosition(hStdout, pos);
    SetConsoleTextAttribute(hStdout, WHITE_COLOR); // White color
    cout << "Score : " << g_score << endl
         << "Tile: "   << g_tile  << endl;
}

void putnumberBoard(int cells[B_SIZE][B_SIZE], int number=2)
{
    COORD pos = {0, 0};
    SetConsoleCursorPosition(hStdout, pos);

    int x, y;
    if (putNewNumber(cells, &x, &y) == true)
    {
        int r = number;//1 << (rand() % 2);
        cells[x][y] = r;
        DrawCell(y, x, cells[x][y]);
    }
    else
    {
        //pos.Y = 35;
        pos.Y = 22;
        SetConsoleTextAttribute(hStdout, WHITE_COLOR); // White color
        SetConsoleCursorPosition(hStdout, pos);
        cout << "Board is Full" << endl;
    }

    updateBoard(cells);
    pos.Y = 21;
    SetConsoleTextAttribute(hStdout, WHITE_COLOR); // White color
    SetConsoleCursorPosition(hStdout, pos);
}

void drawBorders(void)
{
    COORD pos = {0, 0};
    SetConsoleCursorPosition(hStdout, pos);
    SetConsoleTextAttribute(hStdout, WHITE_COLOR);

    for (int i=0 ; i<=16 ; i++)
    {
        if ( i % 4 ==0)
        {
            for (int j = 0; j < 16; j++)
            cout << "__";
            cout << endl;
        }
        else
        {
            for ( int j=0; j<= 32 ;j++)
                if (j % 8 == 0)
                    cout<< '|';
                else
                    cout<< ' ';
            cout << endl;
        }
    }
}
void copyCells(int c[B_SIZE][B_SIZE], int cc[B_SIZE][B_SIZE])
{
    int i, j ;
    for (i = 0 ; i < B_SIZE; i++)
        for (j = 0; j < B_SIZE; j++)
            cc[i][j] = c[i][j];
}


void initGameData(int cells[B_SIZE][B_SIZE])
{
    move_failed[0] = false;
    move_failed[1] = false;
    move_failed[2] = false;
    move_failed[3] = false;
    memset(cells, -1, sizeof(int) * B_SIZE * B_SIZE);
    memset(move_failed, 0, sizeof(move_failed));

    putnumberBoard(cells);
    int r = rand() % 2;
    putnumberBoard(cells, 2 << r);
    g_tile = max(2, r);
    g_score = 0;

    system("cls");
    drawBorders();
    updateBoard(cells);
}

int main ()
{
    int i,j ;
    int cells[B_SIZE][B_SIZE] = {-1};
    COORD pos = {0, 0};

    srand(time(NULL));
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    // initializing board
    // distinct function which initializes the all game data.
    initGameData(cells);

    while (1)
    {
        //Sleep(1);
        pos.X = 0;
        pos.Y = 0;
        SetConsoleCursorPosition(hStdout, pos);
        // GetAsyncKeyState() retuns the short value (short - is the 2-byte integer)
        // We can read from documentation that if its highest bit is set then. VK_ESCAPE is pressed.
        // How we can get whether highest bit of short value is set?
        // if (result & 100000000000000 != 0)
        // or:
        // if (result & 0x8000 != 0)
        // Have you remember task "Bit value" from e-olimp?
        // Problem 5317
        int cells_copy[B_SIZE][B_SIZE];
        if (isGameOver())
        {
            COORD pos = {0,8};
            SetConsoleTextAttribute(hStdout, 15);
            SetConsoleCursorPosition(hStdout, pos);
            for (int i =  0; i < 11; i++)
                putchar(' ');
            cout << "Game Over!";
            for (int i =  0; i < 12; i++)
                putchar(' ');

            pos.X = 0;
            pos.Y = 23;
            SetConsoleTextAttribute(hStdout, 15);
            SetConsoleCursorPosition(hStdout, pos);
            cout << "Press N for new game or Q for exit.\n";
            char userAnswer = 0;
            cin >> userAnswer;

            if (userAnswer == 'n' or userAnswer == 'N')
            {
                // init structures
                initGameData(cells);
            }
            else if (userAnswer == 'q' or userAnswer == 'Q')
                return 0;
            else
            {
                cout << "Option is not recognized. Exiting.\n";
                return -1;
            }
        }

        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000 != 0)
            return 0;
        // Task: make proper bahavior for VK_UP, VK_LEFT, VK_RIGHT
        else if (GetAsyncKeyState(VK_LEFT) & 0x8000 != 0)
        {
            copyCells(cells, cells_copy);
            slideBoard(cells, VK_LEFT);
            updateBoard(cells);
            reduceBoard(cells, VK_LEFT);
            updateBoard(cells);
            if (hasDiff(cells, cells_copy))
            {
                putnumberBoard(cells);
                memset(move_failed, 0, sizeof(move_failed));
            }
            else
                move_failed[MOVE_LEFT] = true;

            writeScore();
        }
        else if (GetAsyncKeyState(VK_UP) & 0x8000 != 0)
        {
            copyCells(cells, cells_copy);
            slideBoard(cells, VK_UP);
            updateBoard(cells);
            reduceBoard(cells, VK_UP);
            updateBoard(cells);
            if (hasDiff(cells, cells_copy))
            {
                putnumberBoard(cells);
                memset(move_failed, 0, sizeof(move_failed));
            }
            else
                move_failed[MOVE_UP] = true;
            writeScore();
        }
        else if (GetAsyncKeyState(VK_RIGHT) & 0x8000 != 0)
        {
            copyCells(cells, cells_copy);
            slideBoard(cells, VK_RIGHT);
            updateBoard(cells);
            reduceBoard(cells, VK_RIGHT);
            updateBoard(cells);

            if (hasDiff(cells, cells_copy))
            {
                putnumberBoard(cells);
                memset(move_failed, 0, sizeof(move_failed));
            }
            else
                move_failed[MOVE_RIGHT] = true;
            writeScore();
        }
        else if (GetAsyncKeyState(VK_DOWN) & 0x8000 != 0)
        {
            copyCells(cells, cells_copy);
            slideBoard(cells, VK_DOWN);
            updateBoard(cells);
            reduceBoard(cells, VK_DOWN);
            updateBoard(cells);
            if (hasDiff(cells, cells_copy))
            {
                putnumberBoard(cells);
                memset(move_failed, 0, sizeof(move_failed));
            }
            else
                move_failed[MOVE_DOWN] = true;
            writeScore();
        }
        else if (GetAsyncKeyState(VK_SPACE) & 0x8000 != 0)
        {
            COORD pos = {0,8};
            SetConsoleTextAttribute(hStdout, 15);
            SetConsoleCursorPosition(hStdout, pos);
            for (int i =  0; i < 11; i++)
                putchar(' ');
            cout << "Game Over!";
            for (int i =  0; i < 12; i++)
                putchar(' ');
        }

        //reduceBoard(cells);
        //updateBoard(cells);
    }

    system("PAUSE");
}
