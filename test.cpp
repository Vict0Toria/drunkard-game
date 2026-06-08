#include <cassert>
#include <queue>
#include <vector>
#include "../main.cpp"    

using namespace std;

//
// ПЬЯНИЦА
//

void testZeroBeatsNine()
{
    DrunkardGame game;

    assert(game.firstWinsRound(0, 9));
}

void testNineLosesToZero()
{
    DrunkardGame game;

    assert(!game.firstWinsRound(9, 0));
}

void testHigherCardWins()
{
    DrunkardGame game;

    assert(game.firstWinsRound(8, 3));
}

void testLowerCardLoses()
{
    DrunkardGame game;

    assert(!game.firstWinsRound(2, 7));
}

void testFirstPlayerWinsGame()
{
    queue<int> p1;
    queue<int> p2;

    p1.push(9);
    p1.push(8);
    p1.push(7);
    p1.push(6);
    p1.push(5);

    p2.push(1);
    p2.push(2);
    p2.push(3);
    p2.push(4);
    p2.push(0);

    DrunkardGame game;

    string result = game.play(p1, p2);

    assert(result.find("first") != string::npos);
}

void testSecondPlayerWinsGame()
{
    queue<int> p1;
    queue<int> p2;

    p1.push(1);
    p1.push(2);
    p1.push(3);
    p1.push(4);
    p1.push(5);

    p2.push(9);
    p2.push(8);
    p2.push(7);
    p2.push(6);
    p2.push(0);

    DrunkardGame game;

    string result = game.play(p1, p2);

    assert(result.find("second") != string::npos);
}

//
// ДУРАК
//

void testDeckContains36Cards()
{
    DurakGame game;

    vector<Card> deck = game.createDeck();

    assert(deck.size() == 36);
}

void testDealCards()
{
    DurakGame game;

    vector<Card> deck = game.createDeck();

    vector<Card> p1;
    vector<Card> p2;

    game.dealCards(deck, p1, p2);

    assert(p1.size() == 6);
    assert(p2.size() == 6);
}

void testDeckAfterDeal()
{
    DurakGame game;

    vector<Card> deck = game.createDeck();

    vector<Card> p1;
    vector<Card> p2;

    game.dealCards(deck, p1, p2);

    assert(deck.size() == 24);
}

void testAceBeatsKing()
{
    DurakGame game;

    Card ace  = {14, 0};
    Card king = {13, 0};

    assert(game.beats(king, ace, 3));
}

void testTrumpBeatsNonTrump()
{
    DurakGame game;

    Card sixHearts  = {6, 0};
    Card sixSpades  = {6, 3};

    int trumpSuit = 3;

    assert(
        game.beats(
            sixHearts,
            sixSpades,
            trumpSuit
        )
    );
}

void testSameSuitHigherCardWins()
{
    DurakGame game;

    Card eight = {8, 1};
    Card ten   = {10, 1};

    assert(
        game.beats(
            eight,
            ten,
            3
        )
    );
}

int main()
{
    //
    // ПЬЯНИЦА
    //

    testZeroBeatsNine();
    testNineLosesToZero();
    testHigherCardWins();
    testLowerCardLoses();
    testFirstPlayerWinsGame();
    testSecondPlayerWinsGame();

    //
    // ДУРАК
    //

    testDeckContains36Cards();
    testDealCards();
    testDeckAfterDeal();
    testAceBeatsKing();
    testTrumpBeatsNonTrump();
    testSameSuitHigherCardWins();

    return 0;
}
