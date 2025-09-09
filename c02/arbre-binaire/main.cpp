#include <iostream>
#include <queue>

// on peut modéliser un noeud d'un arbre binaire
// par sa donnée (position),
// son pointeur de premier noeud (first),
// et son pointeur de deuxième noeud (second)
// de la manière suivante
struct node
{
    std::string position;
    node *first, *second;
};

// on peut modéliser un arbre binaire
// par son pointeur de noeud racine (root)
// de la manière suivante
class org_tree
{
public:
    // on peut implémenter un constructeur par donnée
    // d'un arbre binaire de la manière suivante
    org_tree(const std::string &pos)
    {
        root = new node{pos, nullptr, nullptr};
    }

    // on peut ajouter un subordonné
    // dans un arbre binaire de la manière suivante
    bool addSubordinate(const std::string &manager, const std::string &subordinate)
    {
        auto managerNode = org_tree::find(root, manager);
        if (!managerNode)
        {
            std::cout << "(01): No position named " << manager << std::endl;
            return false;
        }
        if (managerNode->first && managerNode->second)
        {
            std::cout << "(02): " << manager << " already has 2 subordinates." << std::endl;
            return false;
        }
        if (!managerNode->first)
            managerNode->first = new node{subordinate, nullptr, nullptr};
        else
            managerNode->second = new node{subordinate, nullptr, nullptr};
        return true;
    }

    // on peut afficher les éléments
    // d'un arbre binaire de la manière suivante
    friend std::ostream &operator<<(std::ostream &_out, const org_tree &_tree)
    {
        _out << "{";
        org_tree::levelOrder(_out, _tree.root);
        _out << "}";
        return _out;
    }

private:
    // on peut rechercher un noeud
    // dans un arbre binaire de la manière suivante
    static node *find(node *root, const std::string &value)
    {
        if (root == nullptr)
            return nullptr;
        if (root->position == value)
            return root;
        auto firstFound = org_tree::find(root->first, value);
        if (firstFound != nullptr)
            return firstFound;
        return org_tree::find(root->second, value);
    }

    // on peut parcourir les éléments
    // d'un arbre binaire de la manière suivante
    static void levelOrder(std::ostream &_out, node *start)
    {
        if (!start)
            return;

        std::queue<node *> q;
        q.push(start);

        while (!q.empty())
        {
            size_t size = q.size();
            for (size_t i = 0; i < size; i++)
            {
                auto current = q.front();
                q.pop();

                if (i != 0)
                {
                    _out << ", ";
                }

                _out << current->position;
                if (current->first)
                    q.push(current->first);
                if (current->second)
                    q.push(current->second);
            }

            if (!q.empty())
            {
                _out << ", " << std::endl;
            }
        }
    }

private:
    node *root;
};

// on peut mettre en oeuvre un arbre binaire
// de la manière suivante
int main(int argc, char **argv)
{

    // on peut construire un arbre binaire
    // de la manière suivante
    org_tree tree("CEO");

    // on peut alimenter un arbre binaire
    // de la manière suivante
    if (tree.addSubordinate("CEO", "Deputy Director"))
        std::cout << "(03): Added Deputy Director in the tree." << std::endl;
    else
        std::cout << "(04): Couldn't add Deputy Director in the tree" << std::endl;
    // (03): Added Deputy Director in the tree.

    if (tree.addSubordinate("Deputy Director", "IT Head"))
        std::cout << "(05): Added IT Head in the tree." << std::endl;
    else
        std::cout << "(06): Couldn't add IT Head in the tree" << std::endl;
    // (05): Added IT Head in the tree.

    if (tree.addSubordinate("Deputy Director", "Marketing Head"))
        std::cout << "(07): Added Marketing Head in the tree." << std::endl;
    else
        std::cout << "(08): Couldn't add Marketing Head in the tree" << std::endl;
    // (07): Added Marketing Head in the tree.

    if (tree.addSubordinate("IT Head", "Security Head"))
        std::cout << "(09): Added Security Head in the tree." << std::endl;
    else
        std::cout << "(10): Couldn't add Security Head in the tree" << std::endl;
    // (09): Added Security Head in the tree.

    if (tree.addSubordinate("IT Head", "App Development Head"))
        std::cout << "(11): Added App Development Head in the tree." << std::endl;
    else
        std::cout << "(12): Couldn't add App Development Head in the tree" << std::endl;
    //(11): Added App Development Head in the tree.

    if (tree.addSubordinate("Marketing Head", "Logistics Head"))
        std::cout << "(13): Added Logistics Head in the tree." << std::endl;
    else
        std::cout << "(14): Couldn't add Logistics Head in the tree" << std::endl;
    //(13): Added Logistics Head in the tree.

    if (tree.addSubordinate("Marketing Head", "Public Relations Head"))
        std::cout << "(15): Added Public Relations Head in the tree." << std::endl;
    else
        std::cout << "(16): Couldn't add Public Relations Head in the tree" << std::endl;
    // (15): Added Public Relations Head in the tree.

    if (tree.addSubordinate("Deputy Director", "Finance Head"))
        std::cout << "(17): Added Finance Head in the tree." << std::endl;
    else
        std::cout << "(18): Couldn't add Finance Head in the tree" << std::endl;
    // (02): Deputy Director already has 2 subordinates.
    // (18): Couldn't add Finance Head in the tree

    // on peut afficher un arbre binaire
    // de la manière suivante
    std::cout << "(19): " << tree << std::endl;
    // (19): {CEO,
    // Deputy Director,
    // IT Head, Marketing Head,
    // Security Head, App Development Head, Logistics Head, Public Relations Head}

    return 0;
}
