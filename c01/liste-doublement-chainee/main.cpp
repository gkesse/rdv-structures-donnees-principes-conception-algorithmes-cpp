#include <iostream>
#include <vector>
#include <array>
#include <sstream>
#include <algorithm>
#include <random>
#include <chrono>

// on peut modéliser un noeud
// d'une liste doublement chaînée de la manière suivante
template <typename T>
struct cir_list_node
{
    ~cir_list_node()
    {
        delete data;
    }

    // on peut modéliser un noeud d'une liste doublement chaînée
    // par sa donnée (data), son pointeur de noeud suivant (next)
    // et son pointeur de noeud précédent (prev)
    // de la manière suivante
    T *data;
    cir_list_node *next, *prev;
};

// on peut modéliser un itérateur
// d'une liste doublement chaînée de la manière suivante
template <typename T>
struct cir_list_it
{
public:
    using node = cir_list_node<T>;
    using node_ptr = node *;

public:
    // on peut implémenter le constructeur par pointeur d'un itérateur
    // d'une liste doublement chaînée de la manière suivante
    cir_list_it(node_ptr p)
        : ptr(p)
    {
    }

    // on peut récupérer le contenu de la donnée d'un itérateur
    // d'une liste doublement chaînée de la manière suivante
    T &operator*()
    {
        return *(ptr->data);
    }

    // on peut récupérer le pointeur de noeud d'un itérateur
    // d'une liste doublement chaînée de la manière suivante
    node_ptr get()
    {
        return ptr;
    }

    // on peut pré-incrémenter un itérateur
    // d'une liste doublement chaînée de la manière suivante
    cir_list_it &operator++()
    {
        ptr = ptr->next;
        return *this;
    }

    // on peut post-incrémenter un itérateur
    // d'une liste doublement chaînée de la manière suivante
    cir_list_it operator++(int)
    {
        cir_list_it it = *this;
        ++(*this);
        return it;
    }

    // on peut pré-déccrémenter un itérateur
    // d'une liste doublement chaînée de la manière suivante
    cir_list_it &operator--()
    {
        ptr = ptr->prev;
        return *this;
    }

    // on peut post-déccrémenter un itérateur
    // d'une liste doublement chaînée de la manière suivante
    cir_list_it operator--(int)
    {
        cir_list_it it = *this;
        --(*this);
        return it;
    }

    // on peut comparer l'égalité entre deux itérateurs
    // d'une liste doublement chaînée de la manière suivante
    friend bool operator==(
        const cir_list_it &it1, const cir_list_it &it2)
    {
        return it1.ptr == it2.ptr;
    }

    // on peut comparer la différence entre deux itérateurs
    // d'une liste doublement chaînée de la manière suivante
    friend bool operator!=(
        const cir_list_it &it1, const cir_list_it &it2)
    {
        return it1.ptr != it2.ptr;
    }

private:
    // on peut modéliser un itérateur d'une liste doublement chaînée
    // par son pointeur de noeud (ptr)
    // de la manière suivante
    node_ptr ptr;
};

// on peut modéliser
// une liste doublement chaînée de la manière suivante
template <typename T>
class cir_list
{
public:
    using node = cir_list_node<T>;
    using node_ptr = node *;
    using iterator = cir_list_it<T>;

public:
    // on peut implémenter le constructeur par défaut
    // d'une liste doublement chaînée de la manière suivante
    cir_list()
        : n(0)
    {
        head = new node{nullptr, nullptr, nullptr};
        head->next = head;
        head->prev = head;
    }

    // on peut implémenter le constructeur par liste
    // d'une liste doublement chaînée de la manière suivante
    cir_list(const std::initializer_list<T> &il)
        : cir_list()
    {
        for (const auto &i : il)
            insert(i);
    }

    // on peut implémenter le constructeur par copie
    // d'une liste doublement chaînée de la manière suivante
    cir_list(const cir_list<T> &other)
        : cir_list()
    {
        for (const auto &i : other)
            insert(i);
    }

    // on peut implémenter le destructeur
    // d'une liste doublement chaînée de la manière suivante
    ~cir_list()
    {
        while (size())
        {
            erase(*(head->data));
        }
    }

    // on peut récupérer la taille
    // d'une liste doublement chaînée de la manière suivante
    size_t size() const
    {
        return n;
    }

    // on peut insérer un élément au début
    // d'une liste doublement chaînée de la manière suivante
    void insert(const T &value)
    {
        node_ptr newNode = new node{new T(value), nullptr, nullptr};
        n++;

        auto dummy = head->prev;
        dummy->next = newNode;
        newNode->prev = dummy;

        if (head == dummy)
        {
            dummy->prev = newNode;
            newNode->next = dummy;
            head = newNode;
            return;
        }

        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }

    // on peut supprimer un élément au début
    // d'une liste doublement chaînée de la manière suivante
    void erase(const T &value)
    {
        auto cur = head, dummy = head->prev;
        while (cur != dummy)
        {
            if (*(cur->data) == value)
            {
                cur->prev->next = cur->next;
                cur->next->prev = cur->prev;
                if (cur == head)
                {
                    head = head->next;
                }
                delete cur;
                n--;
                return;
            }
            cur = cur->next;
        }
    }

    // on peut implémenter l'itérateur de début
    // d'une liste doublement chaînée de la manière suivante
    cir_list_it<T> begin()
    {
        return cir_list_it<T>{head};
    }

    // on peut implémenter l'itérateur de début constant
    // d'une liste doublement chaînée de la manière suivante
    cir_list_it<T> begin() const
    {
        return cir_list_it<T>{head};
    }

    // on peut implémenter l'itérateur de fin
    // d'une liste doublement chaînée de la manière suivante
    cir_list_it<T> end()
    {
        return cir_list_it<T>{head->prev};
    }

    // on peut implémenter l'itérateur de fin constant
    // d'une liste doublement chaînée de la manière suivante
    cir_list_it<T> end() const
    {
        return cir_list_it<T>{head->prev};
    }

    // on peut afficher
    // une liste doublement chaînée de la manière suivante
    friend std::ostream &operator<<(std::ostream &_out, const cir_list<T> &_list)
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

private:
    // on peut modéliser une liste doublement chaînée
    // par son noeud de départ (head) et sa taille (n)
    // de la manière suivante
    node_ptr head;
    size_t n;
};

// on peut mettre en oeuvre
// une liste doublement châinée de la manière suivante
int main(int argc, char **argv)
{
    // on peut insérer un élément
    // dans une liste doublement châinée de la manière suivante
    cir_list<int> pl;
    pl.insert(10);
    pl.insert(20);
    pl.insert(30);
    pl.insert(40);
    pl.insert(50);
    std::cout << "(1): " << pl << std::endl;
    // (1): {50, 40, 30, 20, 10}

    // on peut supprimer un élément
    // d'une liste doublement châinée de la manière suivante
    pl.erase(30);
    std::cout << "(2): " << pl << std::endl;
    // (2): {50, 40, 20, 10}

    // on peut construire par liste
    // une liste doublement châinée de la manière suivante
    cir_list<int> pl2 = {11, 21, 31, 41, 51};
    std::cout << "(3): " << pl2 << std::endl;
    // (3): {51, 41, 31, 21, 11}

    // on peut construire par copie
    // une liste doublement châinée de la manière suivante
    auto pl3 = pl2;
    std::cout << "(4): " << pl3 << std::endl;
    // (4): {51, 41, 31, 21, 11}

    // on peut parcourir par itération
    // une liste doublement châinée de la manière suivante
    std::cout << "(5): {";
    for (cir_list<int>::iterator it = pl3.begin();
         it != pl3.end(); ++it)
    {
        if (it != pl3.begin())
        {
            std::cout << ", ";
        }
        std::cout << *it;
    }
    std::cout << "}" << std::endl;
    // (5): {11, 21, 31, 41, 51}

    return 0;
}
