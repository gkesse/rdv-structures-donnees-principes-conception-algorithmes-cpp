#include <iostream>
#include <vector>
#include <array>
#include <sstream>
#include <algorithm>
#include <random>
#include <chrono>

// on peut modéliser une carte (card)
// d'un jeu de cartes (game) de la manière suivante
struct card
{
    // on peut énumérer les couleurs d'une carte (card)
    // de la manière suivante
    enum suit
    {
        HEART,  // coeur
        SPADE,  // pique
        CLUB,   // trèfle
        DIAMOND // carreau
    };

    // on peut convertir une carte (card) en chaîne de caractères
    // de la manière suivante
    std::string to_string() const
    {
        std::ostringstream os;
        if (number > 0 && number <= 10)
            os << number;
        else
        {
            switch (number)
            {
            case 1:
                os << "Ace"; // As
                break;
            case 11:
                os << "Jack"; // Valet
                break;
            case 12:
                os << "Queen"; // Reine
                break;
            case 13:
                os << "King"; // Roi
                break;
            default:
                return "Invalid card"; // Carte invalide
            }
        }

        os << " of ";
        switch (suit)
        {
        case HEART:
            os << "hearts"; // coeurs
            break;
        case SPADE:
            os << "spades"; // piques
            break;
        case CLUB:
            os << "clubs"; // trèfles
            break;
        case DIAMOND:
            os << "diamonds"; // carreaux
            break;
        }

        return os.str();
    }

    // on peut modéliser une carte (card)
    // par son numéro (number) et sa couleur (suit)
    // de la manière suivante
    int number;
    suit suit;
};

// on peut modéliser un jeu de cartes (game)
// de la manière suivante
struct game
{
    // on peut construire les cartes (desk)
    // d'un jeu de cartes (game) de la manière suivante
    void buildDeck()
    {
        for (int i = 0; i < 13; i++)
            deck[i + 0 * 13] = card{i + 1, card::HEART};
        for (int i = 0; i < 13; i++)
            deck[i + 1 * 13] = card{i + 1, card::SPADE};
        for (int i = 0; i < 13; i++)
            deck[i + 2 * 13] = card{i + 1, card::CLUB};
        for (int i = 0; i < 13; i++)
            deck[i + 3 * 13] = card{i + 1, card::DIAMOND};
    }

    // on peut distribuer les cartes (desk) aux joueurs
    // (player1, player2, player3, player4)
    // d'un jeu de cartes (game) de la manière suivante
    void dealCards()
    {
        // on peut mélanger les cartes (desk)
        // d'un jeu de cartes (game) de la manière suivante
        unsigned seed = (unsigned)std::chrono::system_clock::now()
                            .time_since_epoch()
                            .count();
        std::shuffle(deck.begin(), deck.end(), std::default_random_engine(seed));

        // on peut distribuer les cartes (desk)
        // d'un jeu de cartes (game) de la manière suivante
        player1 = {deck.begin() + 0 * 13, deck.begin() + 1 * 13};
        player2 = {deck.begin() + 1 * 13, deck.begin() + 2 * 13};
        player3 = {deck.begin() + 2 * 13, deck.begin() + 3 * 13};
        player4 = {deck.begin() + 3 * 13, deck.end()};
    }

    // on peut démarrer un jeu de cartes (game)
    // de la manière suivante
    void playGame()
    {
        while (!isGameComplete())
        {
            playOneRound();
        }
    }

    // on peut déterminer le vainqueur
    // d'un jeu de cartes (game) de la manière suivante
    int getWinner() const
    {
        if (player1.empty())
            return 1;
        if (player2.empty())
            return 2;
        if (player3.empty())
            return 3;
        if (player4.empty())
            return 4;
        return 0;
    }

    // on peut déterminer la fin de la partie
    // d'un jeu de cartes (game) de la manière suivante
    bool isGameComplete() const
    {
        return player1.empty() || player2.empty() ||
               player3.empty() || player4.empty();
    }

    // on peut jouer une partie
    // d'un jeu de cartes (game) de la manière suivante
    void playOneRound()
    {
        // on peut comparer et supprimer les cartes des joueurs
        // d'un jeu de cartes (game) de la manière suivante
        if (compareAndRemove(player1, player2))
        {
            compareAndRemove(player3, player4);
            return;
        }
        else if (compareAndRemove(player1, player3))
        {
            compareAndRemove(player2, player4);
            return;
        }
        else if (compareAndRemove(player1, player4))
        {
            compareAndRemove(player2, player3);
            return;
        }
        else if (compareAndRemove(player2, player3))
        {
            return;
        }
        else if (compareAndRemove(player2, player4))
        {
            return;
        }
        else if (compareAndRemove(player3, player4))
        {
            return;
        }

        // on peut mélanger les cartes des joueurs
        // d'un jeu de cartes (game) de la manière suivante
        unsigned seed = (unsigned)std::chrono::system_clock::now()
                            .time_since_epoch()
                            .count();
        std::shuffle(player1.begin(), player1.end(), std::default_random_engine(seed));
        std::shuffle(player2.begin(), player2.end(), std::default_random_engine(seed));
        std::shuffle(player3.begin(), player3.end(), std::default_random_engine(seed));
        std::shuffle(player4.begin(), player4.end(), std::default_random_engine(seed));
    }

    // on peut comparer et supprimer les cartes de deux joueurs
    // d'un jeu de cartes (game) de la manière suivante
    bool compareAndRemove(std::vector<card> &p1, std::vector<card> &p2)
    {
        if (p1.back().number == p2.back().number)
        {
            p1.pop_back();
            p2.pop_back();
            return true;
        }
        return false;
    }

    // on peut modéliser un jeu de cartes (game)
    // par ses cartes (deck) et ses joueurs (player1, player2, player3, player4)
    // de la manière suivante
    std::array<card, 52> deck;
    std::vector<card> player1, player2, player3, player4;
};

// on peut mettre en oeuvre
// un jeu de cartes (game) de la manière suivante
int main(int argc, char **argv)
{
    game newGame;
    newGame.buildDeck();
    newGame.dealCards();
    newGame.playGame();

    auto winner = newGame.getWinner();
    std::cout << "Player " << winner << " won the game." << std::endl;

    return 0;
}
