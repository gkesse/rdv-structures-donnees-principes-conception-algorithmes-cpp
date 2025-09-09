#include <iostream>
#include <queue>
#include <vector>

// on peut modéliser un tas de recherche de médiane
// par ses données maximales (maxHeap)
// et ses données minimales (minHeap)
// de la manière suivante
class median
{
public:
    // on peut insérer un élément
    // dans un tas de recherche de médiane de la manière suivante
    void insert(int data)
    {
        if (maxHeap.size() == 0)
        {
            maxHeap.push(data);
            return;
        }

        if (maxHeap.size() == minHeap.size())
        {
            if (data <= get())
                maxHeap.push(data);
            else
                minHeap.push(data);
            return;
        }
        if (maxHeap.size() < minHeap.size())
        {
            if (data > get())
            {
                maxHeap.push(minHeap.top());
                minHeap.pop();
                minHeap.push(data);
            }
            else
                maxHeap.push(data);
            return;
        }
        if (data < get())
        {
            minHeap.push(maxHeap.top());
            maxHeap.pop();
            maxHeap.push(data);
        }
        else
            minHeap.push(data);
    }

    // on peut récupérer la valeur de médiane
    // dans un tas de recherche de médiane de la manière suivante
    double get()
    {
        if (maxHeap.size() == minHeap.size())
            return (maxHeap.top() + minHeap.top()) / 2.0;
        if (maxHeap.size() < minHeap.size())
            return minHeap.top();
        return maxHeap.top();
    }

    // on peut afficher les éléments
    // d'un tas de recherche de médiane de la manière suivante
    friend std::ostream &operator<<(std::ostream &_out, const median &_med)
    {
        auto maxHead_ = _med.maxHeap;
        auto minHead_ = _med.minHeap;

        bool isSep = false;
        _out << "{{";

        while (!maxHead_.empty())
        {
            if (isSep)
            {
                _out << ", ";
            }
            _out << maxHead_.top();
            maxHead_.pop();
            isSep = true;
        }

        _out << "}, {";
        isSep = false;

        while (!minHead_.empty())
        {
            if (isSep)
            {
                _out << ", ";
            }
            _out << minHead_.top();
            minHead_.pop();
            isSep = true;
        }

        _out << "}}";
        return _out;
    }

private:
    std::priority_queue<int> maxHeap;
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;
};

// on peut mettre en oeuvre une recherche de médiane
// en continu de la manière suivante
int main(int argc, char **argv)
{
    // on peut construire un tas de recherche de médiane
    // de la manière suivante
    median med;

    // on peut insérer des éléments
    // dans un tas de recherche de médiane de la manière suivante
    med.insert(1);
    std::cout << "(01): Median after insert 1: " << med.get() << std::endl;
    std::cout << "(02): " << med << std::endl;
    // (01): Median after insert 1: 1
    // (02): {{1}, {}}

    med.insert(5);
    std::cout << "(03): Median after insert 5: " << med.get() << std::endl;
    std::cout << "(04): " << med << std::endl;
    // (03): Median after insert 5: 3
    // (04): {{1}, {5}}

    med.insert(2);
    std::cout << "(05): Median after insert 2: " << med.get() << std::endl;
    std::cout << "(06): " << med << std::endl;
    // (05): Median after insert 2: 2
    // (06): {{2, 1}, {5}}

    med.insert(10);
    std::cout << "(07): Median after insert 10: " << med.get() << std::endl;
    std::cout << "(08): " << med << std::endl;
    // (07): Median after insert 10: 3.5
    // (08): {{2, 1}, {5, 10}}

    med.insert(40);
    std::cout << "(09): Median after insert 40: " << med.get() << std::endl;
    std::cout << "(10): " << med << std::endl;
    // (09): Median after insert 40: 5
    // (10): {{2, 1}, {5, 10, 40}}

    return 0;
}
