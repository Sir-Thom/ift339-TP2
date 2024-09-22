#include <iostream>

#include "deque.h"

#include <vector>

using namespace std;

/*************************
 * Section pour la PARTIE 2
 **************************/

// constantes pour définir l'étendue des priorités - plus propre que de mettre
// des 1 et 10 dans le code
const int MIN_PRIOR = 1;
const int MAX_PRIOR = 10;

enum TypeEvenement { ADD_REQUEST, PROCESS_NEXT };

// Note: dans une struct, tout est public
struct Evenement {
  TypeEvenement type;

  // si type == ADD_REQUEST, id = identifiant de la requête, priorite = doit
  // être entre MIN_PRIOR et MAX_PRIOR
  //                         (vous n'avez pas à vérifier la condition sur
  //                         priorite)
  // si type == PROCESS_NEXT, ces deux variables n'ont pas de valeur définie
  int id;
  int priorite;

  // ci-bas une syntaxe qui initialise les variables membres avec type =
  // PROCESS_NEXT, id = 0, priorite = 0
  Evenement() : type(PROCESS_NEXT), id(0), priorite(0) {}

  Evenement(TypeEvenement type, int id = 0, int p = 0) {
    this->type = type;
    this->id = id;
    this->priorite = p;
  }
};

vector<int> get_histo(vector<Evenement> &events) {

  // Note : vous pouvez tester le type d'événement en le comparant avec l'enum,
  // par exemple Evenement& ev = events[0]; if (ev.type == PROCESS_NEXT)
  //   ...
  // else if (ev.type == ADD_REQUEST)
  //   ...

  vector<int> ordre;
  deque<int> queues[MAX_PRIOR + 1];
  for (const auto &ev : events) {
    if (ev.type == ADD_REQUEST) {
      // ajoute dans la deque [1,2,3,4]
      queues[ev.priorite].push_back(ev.id);
    } else if (ev.type == PROCESS_NEXT) {
      // fait le tours
      for (size_t p = MIN_PRIOR; p <= MAX_PRIOR; p++) {
        if (!queues[p].empty()) {
          // ajoute dans vec  prend le queue[#].front
          ordre.push_back(queues[p].front());
          // supprimer car il est dans l'ordre
          queues[p].pop_front();
          // sans le break retourne ordre =
          break;
        }
      }
    }
  }
  return ordre;
}

void test_histo() {

  // ceci reproduit l'exemple du devoir et appelle votre fonction
  vector<Evenement> events;
  events.push_back(Evenement(ADD_REQUEST, 1, 5));
  events.push_back(Evenement(ADD_REQUEST, 2, 5));
  events.push_back(Evenement(ADD_REQUEST, 3, 1));
  events.push_back(Evenement(PROCESS_NEXT));
  events.push_back(Evenement(ADD_REQUEST, 4, 10));
  events.push_back(Evenement(PROCESS_NEXT));
  events.push_back(Evenement(ADD_REQUEST, 5, 4));
  events.push_back(Evenement(ADD_REQUEST, 6, 2));
  events.push_back(Evenement(ADD_REQUEST, 7, 4));
  events.push_back(Evenement(PROCESS_NEXT));
  events.push_back(Evenement(PROCESS_NEXT));
  events.push_back(Evenement(PROCESS_NEXT));

  vector<int> ordre = get_histo(events);

  cout << "Ordre = ";
  for (auto it = ordre.begin(); it != ordre.end(); ++it) {
    cout << *it << " ";
  }
  cout << endl;
}
/*************************
 * FIN de section pour la PARTIE 2
 **************************/

int main() {

  // quelques tests qui font des push et des pop, et affichent l'état de votre
  // objet
  deque<int> d;

  d.push_back(0);
  cout << endl
       << "------------------------ push_back x 1 ------------------------"
       << endl;
  d.afficher();

  d.push_back(1);
  d.push_back(2);

  d.push_back(3);
  d.push_back(4);

  cout << endl
       << "------------------------ push_back x 4 ------------------------"
       << endl;
  d.afficher();

  d.pop_back();
  cout << endl
       << "------------------------ pop_back x 1 ------------------------"
       << endl;
  d.afficher();

  d.pop_front();
  d.pop_front();
  cout << endl
       << "------------------------ pop_front x 2 ------------------------"
       << endl;
  d.afficher();

  d.push_back(5);
  d.push_back(6);
  d.push_back(7);
  d.push_back(8);
  d.push_back(9);
  d.push_back(10);

  cout << endl
       << "------------------------ push_back x 6 ------------------------"
       << endl;
  d.afficher();

  d.push_back(11);

  cout << endl
       << "------------------------ push_back x 1 ------------------------"
       << endl;
  d.afficher();

  d.resize(2);
  cout << endl
       << "------------------------ push_back x 1 ------------------------"
       << endl;
  d.afficher();

  d.push_front(12);
  cout << endl
       << "------------------------ push_front x 1 ------------------------"
       << endl;
  d.afficher();

  d.reserve(30);
  cout << endl
       << "------------------------ reserve x 1 ------------------------"
       << endl;
  d.afficher();

  d.pop_back();
  d.pop_back();
  d.pop_back();
  cout << endl
       << "------------------------ pop_back x 3 ------------------------"
       << endl;
  d.afficher();
  cout << "NOTE: dans ce dernier cas de test, votre sortie peut differer selon "
          "votre"
       << endl
       << "choix de representation de liste vide (dans mon cas, je supprime "
          "tout quand la liste est vide)"
       << endl;

  cout << endl
       << "------------------------ TEST_HISTO ------------------------"
       << endl;
  test_histo();

  return 0;
}
