#include <iostream>
#include <sstream>

// on peut modéliser un noeud d'un arbre de recherche binaire
// par sa donnée (data), son pointeur de noeud de gauche (left)
// et son pointeur de noeud de droite (right)
// de la manière suivante
struct node
{
    int data;
    node *left, *right;
};

// on peut modéliser un arbre de recherche binaire
// par son pointeur de noeud racine (root)
// de la manière suivante
class bst
{
public:
    // on peut implémenter un constructeur par défaut
    // d'un arbre de recherche binaire de la manière suivante
    bst() : root(nullptr)
    {
    }

    // on peut insérer un élément
    // dans un arbre de recherche binaire de la manière suivante
    void insert(int value)
    {
        if (!root)
            root = new node{value, nullptr, nullptr};
        else
            insert_impl(root, value);
    }

    // on peut supprimer un élément
    // d'un arbre de recherche binaire de la manière suivante
    void deleteValue(int value)
    {
        root = delete_impl(root, value);
    }

    // on peut rechercher un élément
    // dans un arbre de recherche binaire de la manière suivante
    node *find(int value)
    {
        return find_impl(root, value);
    }

    // on peut rechercher le successeur de droite d'un élément
    // dans un arbre de recherche binaire de la manière suivante
    node *successor(node *start)
    {
        auto current = start->right;
        while (current && current->left)
            current = current->left;
        return current;
    }

    // on peut afficher dans l'ordre décroissant les éléments
    // d'un arbre de recherche binaire de la manière suivante
    std::string inorder_desc() const
    {
        bool isSep = false;
        std::ostringstream _out;
        _out << "{";
        inorder_desc_impl(_out, root, isSep);
        _out << "}";
        return _out.str();
    }

    // on peut afficher dans l'ordre croissant les éléments
    // d'un arbre de recherche binaire de la manière suivante
    friend std::ostream &operator<<(std::ostream &_out, const bst &_bst)
    {
        bool isSep = false;
        _out << "{";
        _bst.inorder_impl(_out, isSep);
        _out << "}";
        return _out;
    }

private:
    // on peut insérer un élément à gauche ou à droite
    // dans un arbre de recherche binaire de la manière suivante
    void insert_impl(node *current, int value)
    {
        if (value < current->data)
        {
            if (!current->left)
                current->left = new node{value, NULL, NULL};
            else
                insert_impl(current->left, value);
        }
        else
        {
            if (!current->right)
                current->right = new node{value, NULL, NULL};
            else
                insert_impl(current->right, value);
        }
    }

    // on peut afficher dans l'ordre croissant les éléments
    // d'un arbre de recherche binaire de la manière suivante
    void inorder_impl(std::ostream &_out, bool &_isSep) const
    {
        inorder_impl(_out, root, _isSep);
    }

    // on peut afficher les éléments de la gauche vers la droite
    // d'un arbre de recherche binaire de la manière suivante
    void inorder_impl(std::ostream &_out, node *start, bool &_isSep) const
    {
        if (!start)
            return;

        inorder_impl(_out, start->left, _isSep); // Visiter les noeuds de gauche
        if (_isSep)
        {
            _out << ", "; // Afficher le séparateur
        }
        _out << start->data; // Afficher le noeud courant
        _isSep = true;
        inorder_impl(_out, start->right, _isSep); // Visiter les noeuds de droite
    }

    // on peut afficher les éléments de la droite vers la gauche
    // d'un arbre de recherche binaire de la manière suivante
    void inorder_desc_impl(std::ostringstream &_out, node *start, bool &_isSep) const
    {
        if (!start)
            return;

        inorder_desc_impl(_out, start->right, _isSep); // Visiter les noeuds de droite
        if (_isSep)
        {
            _out << ", "; // Afficher le séparateur
        }
        _out << start->data; // Afficher le noeud courant
        _isSep = true;
        inorder_desc_impl(_out, start->left, _isSep); // Visiter les noeuds de gauche
    }

    // on peut supprimer un élément
    // d'un arbre de recherche binaire de la manière suivante
    node *delete_impl(node *start, int value)
    {
        if (!start)
            return nullptr;
        if (value < start->data)
            start->left = delete_impl(start->left, value);
        else if (value > start->data)
            start->right = delete_impl(start->right, value);
        else
        {
            // Soit les deux enfants sont absents,
            // soit seul l'enfant gauche est absent
            if (!start->left)
            {
                auto tmp = start->right;
                delete start;
                return tmp;
            }
            // Seul l'enfant de droite est absent
            if (!start->right)
            {
                auto tmp = start->left;
                delete start;
                return tmp;
            }

            auto succNode = successor(start);
            start->data = succNode->data;
            // Supprimez le successeur du sous-arbre de droite,
            // car il sera toujours dans le sous-arbre de droite
            start->right = delete_impl(start->right, succNode->data);
        }
        return start;
    }

    // on peut rechercher un élément
    // dans un arbre de recherche binaire de la manière suivante
    node *find_impl(node *current, int value)
    {
        if (!current)
        {
            std::cout << std::endl;
            return nullptr;
        }
        if (current->data == value)
        {
            std::cout << "(3): Found " << value << std::endl;
            return current;
        }
        // La valeur sera dans le sous-arbre de gauche
        if (value < current->data)
        {
            std::cout << "(4): Going left from " << current->data << ", ";
            return find_impl(current->left, value);
        }
        // La valeur sera dans le sous-arbre de droite
        std::cout << "(5): Going right from " << current->data << ", ";
        return find_impl(current->right, value);
    }

private:
    node *root;
};

// on peut mettre en oeuvre un arbre de recherche binaire
// de la manière suivante
int main(int argc, char **argv)
{
    // on peut construire un arbre de recherche binaire
    // de la manière suivante
    bst tree;

    // on peut insérer des éléments
    // dans un arbre de recherche binaire de la manière suivante
    tree.insert(12);
    tree.insert(10);
    tree.insert(20);
    tree.insert(8);
    tree.insert(11);
    tree.insert(15);
    tree.insert(28);
    tree.insert(4);
    tree.insert(2);

    // on peut afficher dans l'ordre croissant les éléments
    // d'un arbre de recherche binaire de la manière suivante
    std::cout << "(1): Inorder: " << tree << std::endl;
    // (1): Inorder: {2, 4, 8, 10, 11, 12, 15, 20, 28}

    // on peut supprimer un élément
    // d'un arbre de recherche binaire de la manière suivante
    tree.deleteValue(12);
    std::cout << "(2): Inorder after deleting 12: " << tree << std::endl;
    // (2): Inorder after deleting 12: {2, 4, 8, 10, 11, 15, 20, 28}

    // on peut rechercher un élément
    // dans un arbre de recherche binaire de la manière suivante
    if (tree.find(12))
        std::cout << "(6): Element 12 is present in the tree" << std::endl;
    else
        std::cout << "(7): Element 12 is NOT present in the tree" << std::endl;
    // (4): Going left from 15, (5): Going right from 10, (5): Going right from 11,
    // (7): Element 12 is NOT present in the tree

    // on peut afficher dans l'ordre décroissant les éléments
    // d'un arbre de recherche binaire de la manière suivante
    std::cout << "(8): " << tree.inorder_desc() << std::endl;

    return 0;
}
