#include <cassert>
#include <vector>

using namespace std;

struct Card
{
    int rank;
    int suit;
};

bool beats(Card attack,
           Card defend,
           int trumpSuit)
{
    if (attack.suit == defend.suit)
        return defend.rank > attack.rank;

    if (defend.suit == trumpSuit &&
        attack.suit != trumpSuit)
        return true;

    return false;
}

void testDeckSize()
{
    vector<Card> deck;

    for (int suit = 0; suit < 4; suit++)
    {
        for (int rank = 6; rank <= 14; rank++)
        {
            deck.push_back({rank, suit});
        }
    }

    assert(deck.size() == 36);
}

void testTrumpBeatsRegularCard()
{
    Card attack{10, 0};   // 10 пики
    Card defend{6, 1};    // 6 червы

    assert(
        beats(
            attack,
            defend,
            1
        )
    );
}

void testHigherCardSameSuit()
{
    Card attack{8, 0};
    Card defend{10, 0};

    assert(
        beats(
            attack,
            defend,
            1
        )
    );
}

void testLowerCardSameSuit()
{
    Card attack{10, 0};
    Card defend{8, 0};

    assert(
        !beats(
            attack,
            defend,
            1
        )
    );
}

void testWrongSuitCannotBeat()
{
    Card attack{10, 0};
    Card defend{14, 2};

    assert(
        !beats(
            attack,
            defend,
            1
        )
    );
}

void testTrumpVsTrump()
{
    Card attack{8, 1};
    Card defend{10, 1};

    assert(
        beats(
            attack,
            defend,
            1
        )
    );
}

void testAceBeatsKing()
{
    Card attack{13, 0};
    Card defend{14, 0};

    assert(
        beats(
            attack,
            defend,
            1
        )
    );
}

void testSameCards()
{
    Card attack{10, 0};
    Card defend{10, 0};

    assert(
        !beats(
            attack,
            defend,
            1
        )
    );
}

void testCardCountAfterDeal()
{
    vector<Card> deck;

    for (int suit = 0; suit < 4; suit++)
    {
        for (int rank = 6; rank <= 14; rank++)
        {
            deck.push_back({rank, suit});
        }
    }

    vector<Card> player;
    vector<Card> computer;

    for (int i = 0; i < 6; i++)
    {
        player.push_back(deck.back());
        deck.pop_back();

        computer.push_back(deck.back());
        deck.pop_back();
    }

    assert(player.size() == 6);
    assert(computer.size() == 6);
    assert(deck.size() == 24);
}

int main()
{
    testDeckSize();

    testTrumpBeatsRegularCard();

    testHigherCardSameSuit();

    testLowerCardSameSuit();

    testWrongSuitCannotBeat();

    testTrumpVsTrump();

    testAceBeatsKing();

    testSameCards();

    testCardCountAfterDeal();

    return 0;
}
