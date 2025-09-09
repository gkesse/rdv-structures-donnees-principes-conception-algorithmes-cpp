#include <iostream>
#include <sstream>
#include <algorithm>

// on peut modéliser un tableau dynamique
// par sa donnée (data) et sa taille (n)
// de la manière suivante
template <typename T>
class dynamic_array
{
public:
    // on peut implémenter le constructeur par taille
    // d'un tableau dynamique de la manière suivante
    dynamic_array(size_t n)
    {
        this->n = n;
        data = new T[n];
    }

    // on peut implémenter le constructeur par copie
    // d'un tableau dynamique de la manière suivante
    dynamic_array(const dynamic_array<T> &other)
    {
        n = other.n;
        data = new T[n];
        for (int i = 0; i < n; i++)
            data[i] = other[i];
    }

    // on peut implémenter le destructeur
    // d'un tableau dynamique de la manière suivante
    ~dynamic_array()
    {
        delete[] data;
    }

    // on peut récupérer un élément à un indice donné
    // d'un tableau dynamique de la manière suivante
    T &operator[](int index)
    {
        return data[index];
    }

    // on peut récupérer un élément constant à un indice donné
    // d'un tableau dynamique de la manière suivante
    const T &operator[](int index) const
    {
        return data[index];
    }

    // on peut récupérer un élément à un indice donné
    // d'un tableau dynamique de la manière suivante
    T &at(int index)
    {
        if (index < n)
            return data[index];
        throw "Index out of range";
    }

    // on peut récupérer la taille
    // d'un tableau dynamique de la manière suivante
    size_t size() const
    {
        return n;
    }

    // on peut récupérer l'itérateur de début
    // d'un tableau dynamique de la manière suivante
    T *begin()
    {
        return data;
    }

    // on peut récupérer l'itérateur de début constant
    // d'un tableau dynamique de la manière suivante
    const T *begin() const
    {
        return data;
    }

    // on peut récupérer l'itérateur de fin
    // d'un tableau dynamique de la manière suivante
    T *end()
    {
        return data + n;
    }

    // on peut récupérer l'itérateur de fin constant
    // d'un tableau dynamique de la manière suivante
    const T *end() const
    {
        return data + n;
    }

    // on peut fusionner deux tableaux dynamiques
    // de la manière suivante
    friend dynamic_array<T> operator+(
        const dynamic_array<T> &arr1,
        const dynamic_array<T> &arr2)
    {
        dynamic_array<T> result(arr1.size() + arr2.size());
        std::copy(arr1.begin(), arr1.end(), result.begin());
        std::copy(arr2.begin(), arr2.end(), result.begin() + arr1.size());
        return result;
    }

    // on peut afficher un tableau dynamique
    // de la manière suivante
    friend std::ostream &operator<<(std::ostream &_out, const dynamic_array<T> &_arr)
    {
        _out << "{";
        bool isSep = false;
        for (const auto &item : _arr)
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

private:
    T *data;
    size_t n;
};

// on peut modéliser un étudiant
// par son nom (name) et son niveau (standard)
// de la manière suivante
struct student
{
    std::string name;
    int standard;
};

// on peut afficher un étudiant
// de la manière suivante
std::ostream &operator<<(std::ostream &os, const student &s)
{
    return (os << "{" << s.name << ", " << s.standard << "}");
}

// on peut mettre en oeuvre un tableau dynamique
// de la manière suivante
int main(int argc, char **argv)
{
    // construction d'un tableau dynamique
    dynamic_array<student> class1(2);
    class1[0] = {"Name1", 1};
    class1[1] = {"Name2", 2};
    std::cout << "(1): " << class1 << std::endl;
    //(1): {{Name1, 1}, {Name2, 2}}

    // construction par copie d'un tableau dynamique
    auto class2 = class1;
    std::cout << "(2): " << class2 << std::endl;
    //(2): {{Name1, 1}, {Name2, 2}}

    // fusion de deux tableaux dynamiques
    auto class3 = class1 + class2;
    std::cout << "(3): " << class3 << std::endl;
    //(3): {{Name1, 1}, {Name2, 2}, {Name1, 1}, {Name2, 2}}

    return 0;
}
