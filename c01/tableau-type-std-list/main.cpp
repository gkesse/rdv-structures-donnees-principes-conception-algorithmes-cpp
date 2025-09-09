#include <iostream>
#include <list>
#include <vector>

// on peut afficher les éléments
// d'une liste (list) de la manière suivante
template <typename T>
std::ostream &operator<<(std::ostream &_out, std::list<T> _list)
{
    _out << "{";
    bool isSep = false;
    for (const auto &data : _list)
    {
        if (isSep)
        {
            _out << ", ";
        }
        _out << data;
        isSep = true;
    }
    _out << "}";

    return _out;
}

// on peut afficher les éléments
// d'une liste (vector) de la manière suivante
template <typename T>
std::ostream &operator<<(std::ostream &_out, std::vector<T> _list)
{
    _out << "{";
    bool isSep = false;
    for (const auto &data : _list)
    {
        if (isSep)
        {
            _out << ", ";
        }
        _out << data;
        isSep = true;
    }
    _out << "}";

    return _out;
}

// on peut mettre en oeuvre
// une liste (list) de la manière suivante
int main(int argc, char **argv)
{
    // on peut initialiser
    // une liste (list) de la manière suivante
    std::list<int> list1 = {1, 2, 3, 4, 5};
    std::cout << "(01): " << list1 << std::endl;
    // (01): {1, 2, 3, 4, 5}

    // on peut ajouter un élément à la fin
    // d'une liste (list) de la manière suivante
    list1.push_back(6);
    std::cout << "(02): " << list1 << std::endl;
    // (02): {1, 2, 3, 4, 5, 6}

    // on peut insérer un élément après le premier élément
    // d'une liste (list) de la manière suivante
    list1.insert(next(list1.begin()), 0);
    std::cout << "(03): " << list1 << std::endl;
    // (03): {1, 0, 2, 3, 4, 5, 6}

    // on peut insérer un élément à la fin
    // d'une liste (list) de la manière suivante
    list1.insert(list1.end(), 7);
    std::cout << "(04): " << list1 << std::endl;
    // (04): {1, 0, 2, 3, 4, 5, 6, 7}

    // on peut supprimer un élément
    // d'une liste (list) de la manière suivante
    list1.pop_back();
    std::cout << "(05): " << list1 << std::endl;
    // (05): {1, 0, 2, 3, 4, 5, 6}

    // on peut initialiser
    // une liste (vector) de la manière suivante
    std::vector<int> vec = {1, 2, 3, 4, 5};
    std::cout << "(06): " << vec << std::endl;
    // (06): {1, 2, 3, 4, 5}

    // on peut accéder à un élément à l'indice (4)
    // d'une liste (vector) de la manière suivante
    auto it4 = vec.begin() + 4;
    std::cout << "(07): " << *it4 << std::endl;
    // (07): 5

    // on peut insérer un élément à l'indice (2)
    // d'une liste (vector) de la manière suivante
    vec.insert(vec.begin() + 2, 0);
    std::cout << "(08): " << vec << std::endl;
    // (08): {1, 2, 0, 3, 4, 5}

    // on peut initialiser
    // une liste (list) de la manière suivante
    std::list<int> lst = {1, 2, 3, 4, 5};
    std::cout << "(09): " << lst << std::endl;
    // (09): {1, 2, 3, 4, 5}

    // on peut accéder à un élément à l'indice (4)
    // d'une liste (list) de la manière suivante
    auto l_it4 = next(lst.begin(), 4);
    std::cout << "(10): " << *l_it4 << std::endl;
    // (10): 5

    // on peut insérer un élément à l'indice (2)
    // d'une liste (list) de la manière suivante
    lst.insert(next(lst.begin(), 2), 0);
    std::cout << "(11): " << lst << std::endl;
    // (11): {1, 2, 0, 3, 4, 5}

    return 0;
}
