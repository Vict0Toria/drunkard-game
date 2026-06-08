#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

class DrunkardGame
{
public:
    void play()
    {
        queue<int> p1;
        queue<int> p2;

        cout << "Введите 5 карт первого игрока:\n";

        for(int i = 0; i < 5; i++)
        {
            int x;
            cin >> x;
            p1.push(x);
        }

        cout << "Введите 5 карт второго игрока:\n";

        for(int i = 0; i < 5; i++)
        {
            int x;
            cin >> x;
            p2.push(x);
        }

        int moves = 0;

        while(!p1.empty() &&
              !p2.empty() &&
              moves < 1000000)
        {
            int a = p1.front();
            int b = p2.front();

            p1.pop();
            p2.pop();

            bool firstWins;

            if(a == 0 && b == 9)
                firstWins = true;
            else if(a == 9 && b == 0)
                firstWins = false;
            else
                firstWins = a > b;

            if(firstWins)
            {
                p1.push(a);
                p1.push(b);
            }
            else
            {
                p2.push(a);
                p2.push(b);
            }

            moves++;
        }

        if(moves >= 1000000)
        {
            cout << "botva\n";
        }
        else if(p1.empty())
        {
            cout << "second " << moves << "\n";
        }
        else
        {
            cout << "first " << moves << "\n";
        }
    }
};

struct Card
{
    int value;
};

class DurakGame
{
public:
    void play()
    {
        vector<Card> deck;

        for(int i = 6; i <= 14; i++)
        {
            for(int j = 0; j < 4; j++)
            {
                deck.push_back({i});
            }
        }

        srand(time(nullptr));
        random_shuffle(deck.begin(), deck.end());

        vector<Card> player1;
        vector<Card> player2;

        for(int i = 0; i < 6; i++)
        {
            player1.push_back(deck.back());
            deck.pop_back();

            player2.push_back(deck.back());
            deck.pop_back();
        }

        cout << "\nКарты первого игрока:\n";

        for(auto card : player1)
        {
            cout << card.value << " ";
        }

        cout << "\n";

        cout << "\nКарты второго игрока:\n";

        for(auto card : player2)
        {
            cout << card.value << " ";
        }

        cout << "\n";

        int sum1 = 0;
        int sum2 = 0;

        for(auto c : player1)
            sum1 += c.value;

        for(auto c : player2)
            sum2 += c.value;

        cout << "\nУпрощённый режим Дурака\n";

        if(sum1 > sum2)
            cout << "Победил игрок 1\n";
        else if(sum2 > sum1)
            cout << "Победил игрок 2\n";
        else
            cout << "Ничья\n";
    }
};

int main()
{
    while(true)
    {
        cout << "\n===== CARD GAMES =====\n";
        cout << "1. Пьяница\n";
        cout << "2. Дурак\n";
        cout << "0. Выход\n";
        cout << "Ваш выбор: ";

        int choice;
        cin >> choice;

        if(choice == 0)
            break;

        if(choice == 1)
        {
            DrunkardGame game;
            game.play();
        }
        else if(choice == 2)
        {
            DurakGame game;
            game.play();
        }
        else
        {
            cout << "Неверный выбор\n";
        }
    }

    return 0;
}
