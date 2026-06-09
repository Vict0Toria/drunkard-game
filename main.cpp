#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

struct Card
{
    int rank;
    int suit;
};

class DurakGame
{
private:
    vector<Card> deck;
    vector<Card> player;
    vector<Card> computer;

    int trumpSuit;

    string rankToString(int rank)
    {
        if(rank <= 10)
            return to_string(rank);

        if(rank == 11)
            return "J";

        if(rank == 12)
            return "Q";

        if(rank == 13)
            return "K";

        return "A";
    }

    string suitToString(int suit)
    {
        if(suit == 0)
            return "♠";

        if(suit == 1)
            return "♥";

        if(suit == 2)
            return "♦";

        return "♣";
    }

    string cardToString(Card c)
    {
        return rankToString(c.rank)
               + suitToString(c.suit);
    }

    bool beats(Card attack, Card defend)
    {
        if(attack.suit == defend.suit)
            return defend.rank > attack.rank;

        if(defend.suit == trumpSuit &&
           attack.suit != trumpSuit)
            return true;

        return false;
    }

    void createDeck()
    {
        deck.clear();
        player.clear();
        computer.clear();

        for(int suit = 0; suit < 4; suit++)
        {
            for(int rank = 6; rank <= 14; rank++)
            {
                deck.push_back({rank, suit});
            }
        }

        random_shuffle(
            deck.begin(),
            deck.end()
        );

        trumpSuit =
            deck.back().suit;
    }

    void dealCards()
    {
        while(player.size() < 6 &&
              !deck.empty())
        {
            player.push_back(
                deck.back()
            );

            deck.pop_back();
        }

        while(computer.size() < 6 &&
              !deck.empty())
        {
            computer.push_back(
                deck.back()
            );

            deck.pop_back();
        }
    }

    void showPlayerCards()
    {
        cout << "\nВаши карты:\n";

        for(size_t i = 0;
            i < player.size();
            i++)
        {
            cout
                << i + 1
                << ") "
                << cardToString(
                       player[i]
                   )
                << "\n";
        }
    }

public:

    void play()
    {
        createDeck();

        dealCards();

        cout
            << "Козырь: "
            << suitToString(
                   trumpSuit
               )
            << "\n";

        while(
            !player.empty() &&
            !computer.empty()
        )
        {
            showPlayerCards();

            int choice;

            while(true)
            {
                cout
                    << "\nВыберите карту для атаки: ";

                if(!(cin >> choice))
                {
                    cout
                        << "Ошибка! Введите число.\n";

                    cin.clear();

                    cin.ignore(
                        10000,
                        '\n'
                    );

                    continue;
                }

                choice--;

                if(choice < 0 ||
                   choice >=
                   (int)player.size())
                {
                    cout
                        << "Такой карты нет.\n";

                    continue;
                }

                break;
            }

            Card attack =
                player[choice];

            player.erase(
                player.begin()
                + choice
            );

            cout
                << "\nВы атаковали "
                << cardToString(
                       attack
                   )
                << "\n";

            int defendIndex = -1;

            for(size_t i = 0;
                i < computer.size();
                i++)
            {
                if(beats(
                       attack,
                       computer[i]
                   ))
                {
                    defendIndex = i;
                    break;
                }
            }

            if(defendIndex == -1)
            {
                cout
                    << "Компьютер не смог отбиться\n";

                computer.push_back(
                    attack
                );
            }
            else
            {
                Card defend =
                    computer[
                        defendIndex
                    ];

                cout
                    << "Компьютер отбился "
                    << cardToString(
                           defend
                       )
                    << "\n";

                computer.erase(
                    computer.begin()
                    + defendIndex
                );
            }

            if(computer.empty())
                break;

            Card computerAttack =
                computer.front();

            computer.erase(
                computer.begin()
            );

            cout
                << "\nКомпьютер атакует "
                << cardToString(
                       computerAttack
                   )
                << "\n";

            showPlayerCards();

            int defendChoice;

            while(true)
            {
                cout
                    << "\nВыберите карту для защиты (0 если взять): ";

                if(!(cin >> defendChoice))
                {
                    cout
                        << "Ошибка! Введите число.\n";

                    cin.clear();

                    cin.ignore(
                        10000,
                        '\n'
                    );

                    continue;
                }

                break;
            }

            if(defendChoice == 0)
            {
                cout
                    << "Вы взяли карту\n";

                player.push_back(
                    computerAttack
                );
            }
            else
            {
                defendChoice--;

                if(defendChoice < 0 ||
                   defendChoice >=
                   (int)player.size())
                {
                    cout
                        << "Такой карты нет.\n";

                    cout
                        << "Вы забираете карту.\n";

                    player.push_back(
                        computerAttack
                    );
                }
                else
                {
                    Card defend =
                        player[
                            defendChoice
                        ];

                    if(beats(
                           computerAttack,
                           defend
                       ))
                    {
                        cout
                            << "Отбились\n";

                        player.erase(
                            player.begin()
                            + defendChoice
                        );
                    }
                    else
                    {
                        cout
                            << "Карта не бьёт.\n";

                        cout
                            << "Вы забираете карту.\n";

                        player.push_back(
                            computerAttack
                        );
                    }
                }
            }

            dealCards();

            cout
                << "\nКарт в колоде: "
                << deck.size()
                << "\n";

            if(deck.empty() &&
               (player.empty() ||
                computer.empty()))
            {
                break;
            }
        }

        cout << "\n===== ИГРА ОКОНЧЕНА =====\n";

        if(player.empty() &&
           computer.empty())
        {
            cout
                << "Ничья!\n";
        }
        else if(player.empty())
        {
            cout
                << "Поздравляем! Вы победили!\n";
        }
        else if(computer.empty())
        {
            cout
                << "Победил компьютер!\n";
        }
        else
        {
            if(player.size() <
               computer.size())
            {
                cout
                    << "Победили Вы!\n";
            }
            else
            {
                cout
                    << "Победил компьютер!\n";
            }
        }
    }
};

int main()
{
    srand(
        static_cast<unsigned>(
            time(nullptr)
        )
    );

    DurakGame game;

    game.play();

    return 0;
}
