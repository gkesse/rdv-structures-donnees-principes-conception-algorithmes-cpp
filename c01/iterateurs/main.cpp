#include <iostream>
#include <forward_list>
#include <vector>

// on peut afficher une liste (vector)
// de la manière suivante
std::ostream &operator<<(
    std::ostream &_out, const std::vector<std::string> &_list)
{
    bool isSep = false;
    _out << "{";
    for (const auto &item : _list)
    {
        if (isSep)
        {
            _out << ", ";
        }
        _out << item;
        isSep = true;
    }
    _out << "}";
    return _out;
}

// on peut afficher une liste (forward_list)
// de la manière suivante
std::ostream &operator<<(
    std::ostream &_out, const std::forward_list<std::string> &_list)
{
    bool isSep = false;
    _out << "{";
    for (const auto &song : _list)
    {
        if (isSep)
        {
            _out << ", ";
        }
        _out << song;
        isSep = true;
    }
    _out << "}";
    return _out;
}

// on peut mettre en oeuvre l'utilisation des itérateurs
// de la manière suivante
int main(int argc, char **argv)
{
    // création d'une liste (vector)
    std::vector<std::string> vec = {
        "Lewis Hamilton",
        "Lewis Hamilton",
        "Nico Roseberg ",
        "Sebastian Vettel",
        "Lewis Hamilton",
        "Sebastian Vettel",
        "Sebastian Vettel",
        "Sebastian Vettel",
        "Fernando Alonso",
    };
    std::cout << "(1): " << vec << std::endl;
    // (1): {Lewis Hamilton, Lewis Hamilton, Nico Roseberg ,
    //       Sebastian Vettel, Lewis Hamilton, Sebastian Vettel,
    //       Sebastian Vettel, Sebastian Vettel, Fernando Alonso}

    // récupération du premier élément d'une liste (vector)
    auto it = vec.begin(); // Temps constant
    std::cout << "(2): " << *it << std::endl;
    // (2): Lewis Hamilton

    // Auto-addion d'un itérateur d'une liste (vector)
    it += 8; // Temps constant
    std::cout << "(3): " << *it << std::endl;
    // (3): Fernando Alonso

    // déplacement en arrière d'un itérateur d'une liste (vector)
    advance(it, -3); // Temps constant
    std::cout << "(4): " << *it << std::endl;
    // (4): Sebastian Vettel

    // copie d'une liste (vector) vers une liste (forward_list)
    std::forward_list<std::string> fwd(vec.begin(), vec.end());
    std::cout << "(5): " << fwd << std::endl;
    // (5): {Lewis Hamilton, Lewis Hamilton, Nico Roseberg ,
    // Sebastian Vettel, Lewis Hamilton, Sebastian Vettel,
    // Sebastian Vettel, Sebastian Vettel, Fernando Alonso}

    // récupération du premier élément d'une liste (forward_list)
    auto it1 = fwd.begin();
    std::cout << "(6): " << *it << std::endl;
    // (6): Sebastian Vettel

    // déplacement en avant d'un itérateur d'une liste (forward_list)
    advance(it1, 5); // Temps proportionnel au nombre d'éléments
    std::cout << "(7): " << *it << std::endl;
    // (7): Sebastian Vettel

    // erreur à l'exécution
    // lors du déplacement en arrière d'un itérateur d'une liste (forward_list)
    // advance(it1, -2); // Runtime error

    // erreur à la compilation
    // lors de l'auto-addition d'un itérateur d'une liste (forward_list)
    // it1 += 2; // Compiler error

    return 0;
}
