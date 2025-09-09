#include <iostream>
#include <array>
#include <type_traits>

// on peut implémenter la construction
// d'un tableau polyvalent de la manière suivante
template <typename... Args>
auto build_array(Args &&...args)
    -> std::array<typename std::common_type<Args...>::type, sizeof...(args)>
{
    using commonType = typename std::common_type<Args...>::type;
    return {std::forward<commonType>((float)args)...};
}

// on peut afficher les éléments
// d'un tableau polyvalent de la manière suivante
template <size_t N>
std::ostream &operator<<(std::ostream &_out, const std::array<float, N> &_list)
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

// on peut mettre en oeuvre la construction
// d'un tableau polyvalent de la manière suivante
int main(int argc, char **argv)
{
    // construction et affichage d'un tableau polyvalent
    auto data = build_array(10, 20u, 'a', 30.5f, false);
    std::cout << "(1): " << data << std::endl;
    auto data2 = build_array(11, 21u, 'b', 31.5f, true, 12, 22u, 'c');
    std::cout << "(2): " << data2 << std::endl;
    //(1): {10, 20, 97, 30.5, 0}
    //(2): {11, 21, 98, 31.5, 1, 12, 22, 99}

    // erreur à la compilation
    // lorsque tous les arguments du constructeur de tableau polyvalent
    // ne peuvent pas être convertis en un seul type
    // auto data3 = build_array(1, "String", 2.0);

    return 0;
}
