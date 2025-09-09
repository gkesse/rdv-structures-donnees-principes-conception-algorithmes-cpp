#include <iostream>
#include <vector>
#include <array>
#include <sstream>
#include <algorithm>
#include <random>
#include <chrono>

// on peut modéliser une carte d'un jeu de cartes
// par son numéro (number) et sa couleur (suit)
// de la manière suivante
struct card
{
    // on peut énumérer les couleurs d'une carte
    // d'un jeu de cartes de la manière suivante
    enum suit
    {
        HEART,  // coeur
        SPADE,  // pique
        CLUB,   // trèfle
        DIAMOND // carreau
    };

    // on peut afficher les informations sur une carte
    // d'un jeu de cartes de la manière suivante
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

    int number;
    suit suit;
};

// on peut modéliser un jeu de cartes
// par des cartes (deck) et des joueurs (player1, player2, player3, player4)
// de la manière suivante
class game
{
public:
    // on peut construire les cartes
    // d'un jeu de cartes de la manière suivante
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

    // on peut distribuer les cartes aux joueurs
    // d'un jeu de cartes de la manière suivante
    void dealCards()
    {
        // mélange des cartes
        unsigned seed = (unsigned)std::chrono::system_clock::now()
                            .time_since_epoch()
                            .count();
        std::shuffle(deck.begin(), deck.end(), std::default_random_engine(seed));

        // distribution des cartes
        player1 = {deck.begin() + 0 * 13, deck.begin() + 1 * 13};
        player2 = {deck.begin() + 1 * 13, deck.begin() + 2 * 13};
        player3 = {deck.begin() + 2 * 13, deck.begin() + 3 * 13};
        player4 = {deck.begin() + 3 * 13, deck.end()};
    }

    // on peut démarrer un jeu de cartes
    // de la manière suivante
    void playGame()
    {
        while (!isGameComplete())
        {
            playOneRound();
        }
    }

    // on peut déterminer le vainqueur
    // d'un jeu de cartes de la manière suivante
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

private:
    // on peut déterminer la fin de la partie
    // d'un jeu de cartes de la manière suivante
    bool isGameComplete() const
    {
        return player1.empty() || player2.empty() ||
               player3.empty() || player4.empty();
    }

    // on peut jouer une partie
    // d'un jeu de cartes de la manière suivante
    void playOneRound()
    {
        // comparaison et suppression des cartes entre deux joueurs
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

        // mélange des cartes des joueurs
        unsigned seed = (unsigned)std::chrono::system_clock::now()
                            .time_since_epoch()
                            .count();
        std::shuffle(player1.begin(), player1.end(), std::default_random_engine(seed));
        std::shuffle(player2.begin(), player2.end(), std::default_random_engine(seed));
        std::shuffle(player3.begin(), player3.end(), std::default_random_engine(seed));
        std::shuffle(player4.begin(), player4.end(), std::default_random_engine(seed));
    }

    // on peut comparer et supprimer les cartes de deux joueurs
    // d'un jeu de cartes de la manière suivante
    bool compareAndRemove(std::vector<card> &p1, std::vector<card> &p2)
    {
        // dernière cartes identiques
        if (p1.back().number == p2.back().number)
        {
            // suppression des cartes
            p1.pop_back();
            p2.pop_back();
            return true;
        }
        return false;
    }

private:
    std::array<card, 52> deck;
    std::vector<card> player1, player2, player3, player4;
};

// on peut mettre en oeuvre
// un jeu de cartes de la manière suivante
int main(int argc, char **argv)
{
    // construction du jeu de cartes
    game newGame;

    // construction des cartes
    newGame.buildDeck();
    newGame.dealCards();
    newGame.playGame();

    // affichage du vainqueur
    auto winner = newGame.getWinner();
    std::cout << "(1): Player " << winner << " won the game." << std::endl;
    // (1): Player N won the game.

    return 0;
}
