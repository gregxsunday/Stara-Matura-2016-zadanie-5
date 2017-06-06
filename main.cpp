#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Field
{
    bool alive[12][20];

Field()
{
    fstream file;
    string line;
    int rowc = 0;
    file.open("gra.txt", ios::in);

    while(getline(file, line))
    {
        int colc = 0;
        for(char c : line)
        {
            if (c == '.')
                alive[rowc][colc] = 0;
            else if (c == 'X')
                alive[rowc][colc] = 1;

            colc++;
        }
    rowc++;
    }

    file.close();
}


void show_field()
{
    for(int row = 0; row < 12; row++)
    {
        for (int col = 0; col < 20; col++)
        {
            cout << alive[row][col];//[i][j];
        }
        cout << endl;
    }

    cout << "\n\n";
}

int round_row (int row)
{
    if (row < 0)
        return 11;
    else if(row > 11)
        return 0;
    else
        return row;
}

int round_column(int col)
{
    if (col < 0)
        return 19;
    else if(col > 19)
        return 0;
    else
        return col;
}

int count_neighbours(int row, int col)
{
    int neighs = 0;

    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            int currentrow = round_row(row + i);
            int currentcol = round_column(col + j);

            if (alive[currentrow][currentcol] && (currentrow != row || currentcol != col))
                neighs++;
        }
    }

    return neighs;
}

bool still_alive(int row, int col)
{
    int neighs = count_neighbours(row, col);

    if(alive[row][col] && (neighs == 2 || neighs == 3))
        return 1;
    else if
        (!(alive[row][col]) && neighs == 3)
        return 1;
    else return 0;
}

void next_gen(Field f)
{
    Field *previousgen = &f;

    for (int row = 0; row < 12; row++)
    {
        for (int col = 0; col < 20; col++)
        {
            alive[row][col] = previousgen->still_alive(row, col);
        }
    }
}

int countalive()
{
    int stayinalive = 0;
    for(int row = 0; row < 12; row++)
    {
        for (int col = 0; col < 20; col++)
        {
            if(alive[row][col])
                stayinalive++;
        }
    }

    return stayinalive;
}

};

int main()
{
    Field game;
    vector<Field> thegame;
    thegame.push_back(game);

    for (int i = 0; i < 36; i++)
    {
        Field newgen;
        newgen.next_gen(thegame.at(i));
        thegame.push_back(newgen);
    }

    Field *after = &thegame.back();
    after->show_field();
    cout << "A) \nW 37. pokoleniu liczba zywych siasiadow dla komorki w 2. wierszu i 19 kolumnie wynosi: " << after->count_neighbours(1, 18) << endl;

    Field game_b;
    game_b.next_gen(game_b);
    cout << "\nB)\nW 2. pokoleniu liczba zywych komorek wynosi: " << game_b.countalive() << endl;

    Field game_c;
    int ans_c;
    vector<Field> thegame_c;
    thegame_c.push_back(game_c);

    for(int i = 0; i < 100; i++)
    {
        int currentgen = i + 2;
        bool ans_c = 1;

        Field newgen, prevgen;
        prevgen = thegame_c.at(i);
        newgen.next_gen(thegame_c.at(i));

        for(int row = 0; row < 12; row++)
        {
            for (int col = 0; col < 20; col++)
            {
                if(newgen.alive[row][col] != prevgen.alive[row][col])
                    ans_c = 0;
            }
        }

        if(ans_c)
        {
            cout << "\nC)\nUklad ustali sie w: " << currentgen << " pokoleniu\n";
            cout << "Liczba zywych komorek bedzie wynosic: " << newgen.countalive() << endl;
            break;
        }
        thegame_c.push_back(newgen);
    }
    return 0;
}
