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
    // on peut initialiser une liste (vector)
    // de la manière suivante
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
    // Sebastian Vettel, Lewis Hamilton, Sebastian Vettel,
    // Sebastian Vettel, Sebastian Vettel, Fernando Alonso}

    // on peut récupérer le premier élément
    // d'une liste (vector) de la manière suivante
    auto it = vec.begin(); // Temps constant
    std::cout << "(2): " << *it << std::endl;
    // (2): Lewis Hamilton

    // on peut auto-addionner un itérateur
    // d'une liste (vector) de la manière suivante
    it += 8; // Temps constant
    std::cout << "(3): " << *it << std::endl;
    // (3): Fernando Alonso

    // on peut faire avancer en arrière un itérateur
    // d'une liste (vector) de la manière suivante
    advance(it, -3); // Temps constant
    std::cout << "(4): " << *it << std::endl;
    // (4): Sebastian Vettel

    // on peut copier une liste (vector) vers une liste (forward_list)
    // de la manière suivante
    std::forward_list<std::string> fwd(vec.begin(), vec.end());
    std::cout << "(5): " << fwd << std::endl;
    // (5): {Lewis Hamilton, Lewis Hamilton, Nico Roseberg ,
    // Sebastian Vettel, Lewis Hamilton, Sebastian Vettel,
    // Sebastian Vettel, Sebastian Vettel, Fernando Alonso}

    // on peut récupérer le premier élément
    // d'une liste (forward_list) de la manière suivante
    auto it1 = fwd.begin();
    std::cout << "(6): " << *it << std::endl;
    // (6): Sebastian Vettel

    // on peut faire avancer en avant un itérateur
    // d'une liste (forward_list) de la manière suivante
    advance(it1, 5); // Temps proportionnel au nombre d'éléments
    std::cout << "(7): " << *it << std::endl;
    // (7): Sebastian Vettel

    // on peut vérifier qu'on obtient une erreur à l'exécution
    // lorsqu'on fait avancer en arrière un itérateur
    // d'une liste (forward_list) de la manière suivante
    // advance(it1, -2); // Runtime error

    // on peut vérifier qu'on obtient une erreur à la compilation
    // lorsqu'on fait auto-additionner un itérateur
    // d'une liste (forward_list) de la manière suivante
    // it1 += 2; // Compiler error

    return 0;
}
