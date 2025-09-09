#include <iostream>
#include <vector>

// on peut énumérer les villes
// d'un graphe de réseau de villes de la manière suivante
enum class city : int
{
    LONDON,
    MOSCOW,
    ISTANBUL,
    DUBAI,
    MUMBAI,
    SEATTLE,
    SINGAPORE
};

// on peut récupérer le nom d'une ville
// d'un graphe de réseau de villes de la manière suivante
std::ostream &operator<<(std::ostream &os, const city c)
{
    switch (c)
    {
    case city::LONDON:
        os << "LONDON";
        return os;
    case city::MOSCOW:
        os << "MOSCOW";
        return os;
    case city::ISTANBUL:
        os << "ISTANBUL";
        return os;
    case city::DUBAI:
        os << "DUBAI";
        return os;
    case city::MUMBAI:
        os << "MUMBAI";
        return os;
    case city::SEATTLE:
        os << "SEATTLE";
        return os;
    case city::SINGAPORE:
        os << "SINGAPORE";
        return os;
    default:
        return os;
    }
}

// on peut modéliser un graphe de réseau de villes
// par ses données (data)
// de la manière suivante
class graph
{
public:
    // on peut implémenter le constructeur par capacité
    // d'un graphe de réseau de villes de la manière suivante
    graph(int n)
    {
        data.reserve(n);
        std::vector<int> row(n);
        std::fill(row.begin(), row.end(), -1);
        for (int i = 0; i < n; i++)
        {
            data.push_back(row);
        }
    }

    // on peut ajouter une direction entre deux villes
    // d'un graphe de réseau de villes de la manière suivante
    void addEdge(const city c1, const city c2, int dis)
    {
        std::cout << "(2): ADD: " << c1 << "-" << c2 << "=" << dis << std::endl;

        auto n1 = static_cast<int>(c1);
        auto n2 = static_cast<int>(c2);
        data[n1][n2] = dis;
        data[n2][n1] = dis;
    }

    // on peut supprimer une direction
    // d'un graphe de réseau de villes de la manière suivante
    void removeEdge(const city c1, const city c2)
    {
        std::cout << "(7): REMOVE: " << c1 << "-" << c2 << std::endl;

        auto n1 = static_cast<int>(c1);
        auto n2 = static_cast<int>(c2);
        data[n1][n2] = -1;
        data[n2][n1] = -1;
    }

    // on peut afficher les éléments
    // d'un graphe de réseau de villes de la manière suivante
    friend std::ostream &operator<<(std::ostream &_out, const graph &_graph)
    {
        _out << "{";
        bool isCitySep = false;

        for (const auto &city : _graph.data)
        {
            if (isCitySep)
            {
                _out << ", ";
            }

            _out << "{";
            bool isEdgeSep = false;

            for (const auto &edge : city)
            {
                if (isEdgeSep)
                {
                    _out << ", ";
                }

                _out << edge;
                isEdgeSep = true;
            }

            _out << "}";
            isCitySep = true;
        }
        _out << "}";
        return _out;
    }

private:
    std::vector<std::vector<int>> data;
};

// on peut mettre en oeuvre un graphe de réseau de villes
// de la manière suivante
int main(int argc, char **argv)
{
    // on peut construire un graphe de réseau de villes
    // de la manière suivante
    graph g(7);
    std::cout << "(1): " << g << std::endl;
    // (1): {{-1, -1, -1, -1, -1, -1, -1}, {-1, -1, -1, -1, -1, -1, -1},
    //       {-1, -1, -1, -1, -1, -1, -1}, {-1, -1, -1, -1, -1, -1, -1},
    //       {-1, -1, -1, -1, -1, -1, -1}, {-1, -1, -1, -1, -1, -1, -1},
    //       {-1, -1, -1, -1, -1, -1, -1}}

    // on peut alimenter les directions
    // d'un graphe de réseau de villes de la manière suivante
    g.addEdge(city::LONDON, city::MOSCOW, 900);
    g.addEdge(city::LONDON, city::ISTANBUL, 500);
    g.addEdge(city::LONDON, city::DUBAI, 1000);
    g.addEdge(city::ISTANBUL, city::MOSCOW, 1000);
    g.addEdge(city::ISTANBUL, city::DUBAI, 500);
    g.addEdge(city::DUBAI, city::MUMBAI, 200);
    g.addEdge(city::ISTANBUL, city::SEATTLE, 1500);
    g.addEdge(city::DUBAI, city::SINGAPORE, 500);
    g.addEdge(city::MOSCOW, city::SEATTLE, 1000);
    g.addEdge(city::MUMBAI, city::SINGAPORE, 300);
    g.addEdge(city::SEATTLE, city::SINGAPORE, 700);
    std::cout << "(3): " << g << std::endl;
    // (3): {{-1, 900, 500, 1000, -1, -1, -1}, {900, -1, 1000, -1, -1, 1000, -1},
    //       {500, 1000, -1, 500, -1, 1500, -1}, {1000, -1, 500, -1, 200, -1, 500},
    //       {-1, -1, -1, 200, -1, -1, 300}, {-1, 1000, 1500, -1, -1, -1, 700},
    //       {-1, -1, -1, 500, 300, 700, -1}}

    // on peut supprimer une direction
    // d'un graphe de réseau de villes de la manière suivante
    g.addEdge(city::SEATTLE, city::LONDON, 1800);
    std::cout << "(4): " << g << std::endl;
    g.removeEdge(city::SEATTLE, city::LONDON);
    std::cout << "(5): " << g << std::endl;
    // (4): {{-1, 900, 500, 1000, -1, 1800, -1}, {900, -1, 1000, -1, -1, 1000, -1},
    //       {500, 1000, -1, 500, -1, 1500, -1}, {1000, -1, 500, -1, 200, -1, 500},
    //       {-1, -1, -1, 200, -1, -1, 300}, {1800, 1000, 1500, -1, -1, -1, 700},
    //       {-1, -1, -1, 500, 300, 700, -1}}
    // (7): REMOVE: SEATTLE-LONDON
    // (5): {{-1, 900, 500, 1000, -1, -1, -1}, {900, -1, 1000, -1, -1, 1000, -1},
    //       {500, 1000, -1, 500, -1, 1500, -1}, {1000, -1, 500, -1, 200, -1, 500},
    //       {-1, -1, -1, 200, -1, -1, 300}, {-1, 1000, 1500, -1, -1, -1, 700},
    //       {-1, -1, -1, 500, 300, 700, -1}}
    return 0;
}
