
#include <iostream>
#include <string>

// System makro
#ifdef MEF_WIN
    #define clear() system("cls")
#else
    #define clear() system("clear")
#endif  

// globals
const char compSym = 'O';
std::string lestring = "";

void resetMap(short map[], const short length)
{
    for (int i = 0; i < length; i++)
    {
        map[i] = 32; // O
    }
}

void printMap(short map[])
{
    using namespace std;

    cout << "  " << (char)map[0] << "  |  " << (char)map[1] << "  |  " << (char)map[2] << "  \n";
    cout << "------------------\n";
    cout << "  " << (char)map[3] << "  |  " << (char)map[4] << "  |  " << (char)map[5] << "  \n";
    cout << "------------------\n";
    cout << "  " << (char)map[6] << "  |  " << (char)map[7] << "  |  " << (char)map[8] << "  \n";
}

short convertCharToShort(char c)
{
    return c - 48;
}

short* input(short map[])
{
    while (true)
    {
        std::string input;
        std::cout << "Input: ";
        std::cin >> input;


        if (input.length() > 1 || !((short)input[0] > 48 && (short)input[0] < 58))
            std::cout << "Enter a Number between 1 - 9!\n";
        else if (map[convertCharToShort(input[0])-1] != ' ')
            std::cout << "Cell has already been taken!\n";
        else if ((short)input[0] > 48 && (short)input[0] < 58)
        {
            if (lestring.length() < 4)
                lestring+=input[0];
            map[convertCharToShort(input[0])-1] = 'X';
            break;
        }
    }

    std::cout << "\n";

    return map;
}


bool checkVictory(char sym, short map[])
{
    // vertical
    for (int i = 0; i < 9; i+=3)
    {
        if (map[i] == (short)sym && map[i+1] == (short)sym && map[i+2] == (short)sym)
        {
            return true;
        }
    }

    // vertical
    for (int i = 0; i < 3; i++)
    {
        if (map[i] == (short)sym && map[i+3] == (short)sym && map[i+6] == (short)sym)
        {
            return true;
        }
    }

    //diagonal
    if (map[0] == (short)sym && map[4] == (short)sym && map[8] == (short)sym)
        return true;
    else if (map[2] == (short)sym && map[4] == (short)sym && map[6] == (short)sym)
        return true;

    return false;
}

bool checkDraw(short map[])
{
    int c = 0;
    for (int i = 0; i < 9; i++)
    {
        if ((char)map[i] == ' ')
            c++;
    }
    if (c > 0)
        return false;
    return true;
}

void computerTurn(short map[])
{
    short* dummyMap = map;

    // check if can win
    for (int i = 0; i < 9; i++)
    {
        if (dummyMap[i] == ' ')
        {
            dummyMap[i] = compSym;
            if (checkVictory(compSym, dummyMap))
            {
                // make computerTurn
                map[i] = compSym;
                return;
            }
            else {
                dummyMap = map;
                dummyMap[i] = ' ';
            }
        }
    }
    
    // check if enemy can win
    for (int i = 0; i < 9; i++)
    {
        if (dummyMap[i] == ' ')
        {

            dummyMap[i] = 'X';
            if (checkVictory('X', map))
            {
                map[i] = compSym;
                return;
            }
            else {
                dummyMap[i] = ' ';
            }   
 
        }
   }

    // Try place in the middle
    if (map[4] == ' ')
    {
        map[4] = compSym;
        return;
    }

    std::cout << "\nComputer is thinking...\n";

    // else random turn 
    while (true)
    {
        srand(time(nullptr));
        short turn = rand() % 9;
        if (map[turn] == ' ')
        {
            map[turn] = compSym;
            break;
        }
    }
}

int main()
{
    // Map
    const short mapSize = 9;
    short* map = new short[mapSize];

    resetMap(map, mapSize);

    // Game Loop
    while (true)
    {
        clear();
        printMap(map);

        map = input(map);
        if (lestring == "187")
        {
            clear();
            std::cout << "Warum gehst du auf 187 du L Mensch!\n";
            break;
        }

        if (checkVictory('X', map))
        {
            clear();
            printMap(map);
            std::cout << "won\n";
            break;
        }

        if (checkDraw(map))
        {
            clear();
            printMap(map);
            std::cout << "Draw!\n";
            break;
        }
        computerTurn(map);
        if (checkVictory(compSym, map))
        {
            clear();
            printMap(map);
            std::cout << "game over\n";
            break;
        }

        if (checkDraw(map))
        {
            clear();
            printMap(map);
            std::cout << "Draw!\n";
            break;
        }
    }



    delete[] map; 

    return 0;
}
