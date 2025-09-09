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
    singly_ll_iterator(node_ptr p)
        : ptr(p)
    {
    }

    int &operator*()
    {
        return ptr->data;
    }

    node_ptr get()
    {
        return ptr;
    }

    singly_ll_iterator &operator++() // pre-increment
    {
        ptr = ptr->next;
        return *this;
    }

    singly_ll_iterator operator++(int) // post-increment
    {
        singly_ll_iterator result = *this;
        ++(*this);
        return result;
    }

    friend bool operator==(
        const singly_ll_iterator &left,
        const singly_ll_iterator &right)
    {
        return left.ptr == right.ptr;
    }

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
    singly_ll()
    {
        head = new node{0, nullptr};
        m_end = head;
    }

    singly_ll(const std::initializer_list<int> &ilist)
        : singly_ll()
    {
        for (auto it = std::rbegin(ilist); it != std::rend(ilist); it++)
            push_front(*it);
    }

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

    void push_front(int val)
    {
        auto new_node = new node{val, nullptr};
        new_node->next = head;
        head = new_node;
    }

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

    singly_ll_iterator begin()
    {
        return singly_ll_iterator(head);
    }

    singly_ll_iterator end()
    {
        return singly_ll_iterator(m_end);
    }

    singly_ll_iterator begin() const
    {
        return singly_ll_iterator(head);
    }

    singly_ll_iterator end() const
    {
        return singly_ll_iterator(m_end);
    }

    // on peut afficher
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
    // on peut ajouter un élément au début
    // d'une liste chaînée de la manière suivante
    singly_ll sll;
    sll.push_front(10);
    sll.push_front(20);
    sll.push_front(30);
    sll.push_front(40);
    sll.push_front(50);
    std::cout << "(1): " << sll << std::endl;
    // (1): {50, 40, 30, 20, 10}

    // on peut supprimer un élément au début
    // d'une liste chaînée de la manière suivante
    sll.pop_front();
    sll.pop_front();
    std::cout << "(2): " << sll << std::endl;
    // (2): {30, 20, 10}

    // on peut construire par liste
    // une liste chaînée de la manière suivante
    singly_ll sll2 = {10, 20, 30, 40, 50};
    sll2.push_front(0);
    sll2.push_front(-10);
    std::cout << "(3): " << sll2 << std::endl;
    // (3): {-10, 0, 10, 20, 30, 40, 50}

    // on peut construire par copie
    // une liste chaînée de la manière suivante
    auto sll3 = sll2;
    sll3.push_front(-20);
    sll3.push_front(-30);
    std::cout << "(4): " << sll3 << std::endl;
    // (4): {-30, -20, -10, 0, 10, 20, 30, 40, 50}

    // on peut parcourir par itération
    // une liste chaînée de la manière suivante
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
