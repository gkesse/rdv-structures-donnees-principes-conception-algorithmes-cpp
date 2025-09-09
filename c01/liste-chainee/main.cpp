#include <iostream>
#include <algorithm>

// on peut modéliser un noeud d'une liste chaînée
// par sa donnée (data) et son pointeur de noeud suivant (next)
// de la manière suivante
struct singly_ll_node
{
    int data;
    singly_ll_node *next;
};

// on peut modéliser un itérateur d'une liste chaînée
// par son pointeur de noeud (ptr)
// de la manière suivante
class singly_ll_iterator
{
public:
    using node = singly_ll_node;
    using node_ptr = node *;

public:
    // on peut implémenter le constructeur par pointeur d'un itérateur
    // d'une liste chaînée de la manière suivante
    singly_ll_iterator(node_ptr p)
        : ptr(p)
    {
    }

    // on peut récupérer la donnée d'un itérateur
    // d'une liste chaînée de la manière suivante
    int &operator*()
    {
        return ptr->data;
    }

    // on peut récupérer le pointeur direct d'un itérateur
    // d'une liste chaînée de la manière suivante
    node_ptr get()
    {
        return ptr;
    }

    // on peut pré-incrémenter un itérateur
    // d'une liste chaînée de la manière suivante
    singly_ll_iterator &operator++()
    {
        ptr = ptr->next;
        return *this;
    }

    // on peut post-incrémenter un itérateur
    // d'une liste chaînée de la manière suivante
    singly_ll_iterator operator++(int)
    {
        singly_ll_iterator result = *this;
        ++(*this);
        return result;
    }

    // on peut comparer l'égalité entre deux itérateurs
    // d'une liste chaînée de la manière suivante
    friend bool operator==(
        const singly_ll_iterator &left,
        const singly_ll_iterator &right)
    {
        return left.ptr == right.ptr;
    }

    // on peut comparer la différence entre deux itérateurs
    // d'une liste chaînée de la manière suivante
    friend bool operator!=(
        const singly_ll_iterator &left,
        const singly_ll_iterator &right)
    {
        return left.ptr != right.ptr;
    }

private:
    node_ptr ptr;
};

// on peut modéliser une liste chaînée
// par son pointeur de noeud de départ (head)
// et son pointeur de noeud de fin (m_end)
// de la manière suivante
class singly_ll
{
public:
    using node = singly_ll_node;
    using node_ptr = node *;
    using iterator = singly_ll_iterator;

public:
    // on peut implémenter le constructeur par défaut
    // d'une liste chaînée de la manière suivante
    singly_ll()
    {
        head = new node{0, nullptr};
        m_end = head;
    }

    // on peut implémenter le constructeur par liste
    // d'une liste chaînée de la manière suivante
    singly_ll(const std::initializer_list<int> &ilist)
        : singly_ll()
    {
        for (auto it = std::rbegin(ilist); it != std::rend(ilist); it++)
            push_front(*it);
    }

    // on peut implémenter le constructeur par copie
    // d'une liste chaînée de la manière suivante
    singly_ll(const singly_ll &other)
        : singly_ll()
    {
        for (auto i : other)
        {
            m_end->data = i;
            m_end->next = new node{0, nullptr};
            m_end = m_end->next;
        }
    }

    // on peut implémenter le destructeur
    // d'une liste chaînée de la manière suivante
    ~singly_ll()
    {
        node_ptr node = head;
        while (node)
        {
            node_ptr cur = node;
            node = node->next;
            delete cur;
        }
    }

    // on peut ajouter un élément au début
    // d'une liste chaînée de la manière suivante
    void push_front(int val)
    {
        auto new_node = new node{val, nullptr};
        new_node->next = head;
        head = new_node;
    }

    // on peut supprimer un élément à la fin
    // d'une liste chaînée de la manière suivante
    void pop_front()
    {
        auto first = head;
        if (head->next)
        {
            head = head->next;
            delete first;
        }
        else
            throw "Empty list";
    }

    // on peut récupérer l'itérateur de début
    // d'une liste chaînée de la manière suivante
    singly_ll_iterator begin()
    {
        return singly_ll_iterator(head);
    }

    // on peut récupérer l'itérateur de fin
    // d'une liste chaînée de la manière suivante
    singly_ll_iterator end()
    {
        return singly_ll_iterator(m_end);
    }

    // on peut récupérer l'itérateur constant de début
    // d'une liste chaînée de la manière suivante
    singly_ll_iterator begin() const
    {
        return singly_ll_iterator(head);
    }

    // on peut récupérer l'itérateur constant de fin
    // d'une liste chaînée de la manière suivante
    singly_ll_iterator end() const
    {
        return singly_ll_iterator(m_end);
    }

    // on peut afficher les éléments
    // une liste chaînée de la manière suivante
    friend std::ostream &operator<<(std::ostream &_out, const singly_ll &_list)
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

private:
    node_ptr head;
    node_ptr m_end;
};

// on peut mettre en oeuvre une liste chaînée
// de la manière suivante
int main(int argc, char **argv)
{
    // construction par défaut d'une liste chaînée
    singly_ll sll;

    // ajout de données au début d'une liste chaînée
    sll.push_front(10);
    sll.push_front(20);
    sll.push_front(30);
    sll.push_front(40);
    sll.push_front(50);
    std::cout << "(1): " << sll << std::endl;
    // (1): {50, 40, 30, 20, 10}

    // suppression de données au début d'une liste chaînée
    sll.pop_front();
    sll.pop_front();
    std::cout << "(2): " << sll << std::endl;
    // (2): {30, 20, 10}

    // construction par liste d'une liste chaînée
    singly_ll sll2 = {10, 20, 30, 40, 50};
    sll2.push_front(0);
    sll2.push_front(-10);
    std::cout << "(3): " << sll2 << std::endl;
    // (3): {-10, 0, 10, 20, 30, 40, 50}

    // construction par copie d'une liste chaînée
    auto sll3 = sll2;
    sll3.push_front(-20);
    sll3.push_front(-30);
    std::cout << "(4): " << sll3 << std::endl;
    // (4): {-30, -20, -10, 0, 10, 20, 30, 40, 50}

    // parcours par itération d'une liste chaînée
    std::cout << "(5): {";
    for (singly_ll::iterator it = sll3.begin(); it != sll3.end(); it++)
    {
        if (it != sll3.begin())
        {
            std::cout << ", ";
        }
        std::cout << *it;
    }
    std::cout << "}" << std::endl;
    // (5): {-30, -20, -10, 0, 10, 20, 30, 40, 50}

    return 0;
}
