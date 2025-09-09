#include <iostream>
#include <queue>

// on peut modéliser une tâche
// par son identifiant (id), l'auteur de la tâche (user),
// la date de la demande (time) et un compteur (count)
// de la manière suivante
class Job
{
public:
    // on peut construire une tâche de l'imprimante
    // de la manière suivante
    Job(const std::string &u, int t)
        : user(u),
          time(t),
          id(++count)
    {
    }

    // on peut afficher une tâche de l'imprimante
    // de la manière suivante
    friend std::ostream &operator<<(std::ostream &os, const Job &j)
    {
        os << "{" << j.id << ", " << j.user << ", " << j.time << "}";
        return os;
    }

private:
    int id;
    std::string user;
    int time;
    static int count;
};

int Job::count = 0;

// on peut modéliser une imprimante
// par ses tâches (jobs)
// de la manière suivante
template <size_t N>
class Printer
{
public:
    // on peut ajouter une tâche à la fin
    // de la liste des tâches de l'imprimante
    // de la manière suivante
    bool addNewJob(const Job &job)
    {
        if (jobs.size() == N)
        {
            return false;
        }
        std::cout << "(1): adding: " << job << std::endl;
        jobs.push(job);
        return true;
    }

    // on peut supprimer une tâche au début
    // de la liste des tâches de l'imprimante
    // de la manière suivante
    void startPrinting()
    {
        while (!jobs.empty())
        {
            std::cout << "(3): processing: " << jobs.front() << std::endl;
            jobs.pop();
        }
    }

private:
    std::queue<Job> jobs;
};

// on peut mettre en oeuvre une file d'attente
// d'une imprimante de la manière suivante
int main(int argc, char **argv)
{
    // on peut créer une imprimante avec une capacité
    // de cinq tâches de la manière suivante
    Printer<5> printer;

    // on peut créer les tâches
    // de la manière suivante
    Job j1("John", 10);
    Job j2("Jerry", 4);
    Job j3("Jimmy", 5);
    Job j4("George", 7);
    Job j5("Bill", 8);
    Job j6("Kenny", 10);

    // on peut ajouter les tâches
    // de la manière suivante
    printer.addNewJob(j1);
    printer.addNewJob(j2);
    printer.addNewJob(j3);
    printer.addNewJob(j4);
    printer.addNewJob(j5);

    // on peut vérifier qu'on obtient un message d'erreur
    // lorsqu'on essaye d'ajouter une tâche à l'imprimante
    // au-delà de la capacité maximale de la manière suivante
    if (!printer.addNewJob(j6))
    {
        std::cout << "(2): Couldn't add 6th job" << std::endl;
    }

    // on peut exécuter les tâches de l'imprimante
    // de la manière suivante
    printer.startPrinting();

    // on peut ajouter et exécuter la sixième tâche
    // de l'imprimante de la manière suivante
    printer.addNewJob(j6);
    printer.startPrinting();
    return 0;
}
