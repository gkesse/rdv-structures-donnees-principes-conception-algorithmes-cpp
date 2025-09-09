#include <iostream>
#include <forward_list>

// on peut modéliser un citoyen
// par nom (name) et son âge (age)
// de la manière suivante
struct citizen
{
    std::string name;
    int age;
};

// on peut afficher un citoyen
// de la manière suivante
std::ostream &operator<<(std::ostream &_out, const citizen &_citizen)
{
    return (_out << "{" << _citizen.name << ", " << _citizen.age << "}");
}

// on peut afficher une liste de citoyens
// de la manière suivante
template <typename T>
std::ostream &operator<<(std::ostream &_out, const std::forward_list<T> &_list)
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

// on peut mettre en oeuvre la suppression des éléments d'une liste
// de la manière suivante
int main(int argc, char **argv)
{
    // on peut créer une liste de citoyens
    // de la manière suivante
    std::forward_list<citizen> citizens =
        {
            {"Raj", 22},
            {"Rohit", 25},
            {"Rohan", 17},
            {"Sachin", 16},
        };
    std::cout << "(1): " << citizens << std::endl;
    // (1): {{Raj, 22}, {Rohit, 25}, {Rohan, 17}, {Sachin, 16}}

    // on peut supprimer tous les citoyens tels que (age < 18)
    // de la manière suivante
    auto citizens_copy = citizens;
    citizens.remove_if(
        [](const citizen &c)
        {
            return (c.age < 18);
        });
    std::cout << "(2): " << citizens << std::endl;
    // (2): {{Raj, 22}, {Rohit, 25}}

    // on peut supprimer tous les citoyens tels que (age != 17)
    // de la manière suivante
    citizens_copy.remove_if(
        [](const citizen &c)
        {
            return (c.age != 17);
        });
    std::cout << "(3): " << citizens_copy << std::endl;
    // (3): {{Rohan, 17}}

    return 0;
}
