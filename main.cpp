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
        for(int suit = 0;
            suit < 4;
            suit++)
        {
            for(int rank = 6;
                rank <= 14;
                rank++)
            {
                deck.push_back(
                    {rank, suit}
                );
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

            cout
                << "\nВыберите карту для атаки: ";

            int choice;
            cin >> choice;

            choice--;

            if(choice < 0 ||
               choice >=
               (int)player.size())
            {
                cout
                    << "Неверный выбор\n";

                continue;
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

            cout
                << "\nВыберите карту для защиты (0 если взять): ";

            int defendChoice;
            cin >> defendChoice;

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
                            << "Карта не бьёт\n";

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
        }

        if(player.empty())
        {
            cout
                << "\nПоздравляем! Вы победили!\n";
        }
        else
        {
            cout
                << "\nПобедил компьютер!\n";
        }
    }
};

int main()
{
    srand(time(nullptr));

    DurakGame game;

    game.play();

    return 0;
}
