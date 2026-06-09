#include "game.h"
#include <iostream>
#include <algorithm>
#include <ctime>

using namespace std;

string DurakGame::rankToString(int rank) {
    if (rank >= 6 && rank <= 10) return to_string(rank);
    if (rank == 11) return "J";
    if (rank == 12) return "Q";
    if (rank == 13) return "K";
    return "A";
}

string DurakGame::suitToString(int suit) {
    if (suit == 0) return "♠";
    if (suit == 1) return "♥";
    if (suit == 2) return "♦";
    return "♣";
}

string DurakGame::cardToString(Card card) {
    return rankToString(card.rank) + suitToString(card.suit);
}

int DurakGame::getNumber() {
    int value;

    while (!(cin >> value)) {
        cout << "Ошибка ввода. Введите число: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    return value;
}

void DurakGame::createDeck() {
    deck.clear();
    player.clear();
    computer.clear();

    for (int suit = 0; suit < 4; suit++) {
        for (int rank = 6; rank <= 14; rank++) {
            deck.push_back({rank, suit});
        }
    }

    random_shuffle(deck.begin(), deck.end());
    trumpSuit = deck.back().suit;
}

void DurakGame::dealCards() {
    while (player.size() < 6 && !deck.empty()) {
        player.push_back(deck.back());
        deck.pop_back();
    }

    while (computer.size() < 6 && !deck.empty()) {
        computer.push_back(deck.back());
        deck.pop_back();
    }
}

bool DurakGame::beats(Card attack, Card defend) {
    if (attack.suit == defend.suit)
        return defend.rank > attack.rank;

    if (defend.suit == trumpSuit && attack.suit != trumpSuit)
        return true;

    return false;
}

void DurakGame::showPlayerCards() {
    cout << "\nВаши карты:\n";

    for (int i = 0; i < (int)player.size(); i++) {
        cout << i + 1 << ") " << cardToString(player[i]) << "\n";
    }
}

void DurakGame::play() {
    createDeck();
    dealCards();

    cout << "Козырь: " << suitToString(trumpSuit) << "\n";

    while (!player.empty() && !computer.empty()) {

        showPlayerCards();

        int choice;

        while (true) {
            cout << "\nВыберите карту для атаки: ";
            choice = getNumber() - 1;

            if (choice >= 0 && choice < (int)player.size())
                break;

            cout << "Такой карты нет.\n";
        }

        Card attack = player[choice];
        player.erase(player.begin() + choice);

        cout << "\nВы атаковали " << cardToString(attack) << "\n";

        int defendIndex = -1;

        for (int i = 0; i < (int)computer.size(); i++) {
            if (beats(attack, computer[i])) {
                defendIndex = i;
                break;
            }
        }

        if (defendIndex == -1) {
            cout << "Компьютер не смог отбиться\n";
            computer.push_back(attack);
        } else {
            cout << "Компьютер отбился " << cardToString(computer[defendIndex]) << "\n";
            computer.erase(computer.begin() + defendIndex);
        }

        if (computer.empty()) break;

        Card compAttack = computer.front();
        computer.erase(computer.begin());

        cout << "\nКомпьютер атакует " << cardToString(compAttack) << "\n";

        showPlayerCards();

        cout << "\n(0 - взять карту): ";
        int defendChoice = getNumber();

        if (defendChoice == 0) {
            cout << "Вы взяли карту\n";
            player.push_back(compAttack);
        } else {
            defendChoice--;

            if (defendChoice < 0 || defendChoice >= (int)player.size()) {
                cout << "Такой карты нет. Вы забираете карту.\n";
                player.push_back(compAttack);
            } else {
                Card defend = player[defendChoice];

                if (beats(compAttack, defend)) {
                    cout << "Отбились\n";
                    player.erase(player.begin() + defendChoice);
                } else {
                    cout << "Карта не бьёт. Вы забираете карту\n";
                    player.push_back(compAttack);
                }
            }
        }

        dealCards();

        cout << "\nКарт в колоде: " << deck.size() << "\n";
    }

    cout << "\n===== ИГРА ОКОНЧЕНА =====\n";

    if (player.empty()) cout << "Вы победили!\n";
    else if (computer.empty()) cout << "Победил компьютер!\n";
    else cout << "Ничья!\n";
}
