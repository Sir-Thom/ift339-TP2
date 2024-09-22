#ifndef TP2_DEQUE_H
#define TP2_DEQUE_H

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <ostream>
#include <stdexcept>

/**
 * \ brief Classe deque
 */

template <typename TYPE> class deque {
private:
  // vous ne pouvez pas ajouter d'autres variables membres, mais vous pouvez
  // ajoute des fonctions privÃ©es
  TYPE *debut_cap;  // pointeur vers le tableau de stockage
  TYPE *fin_cap;    // pointeur vers le dernier element du tableau de stockage
  TYPE *debut_elem; // pointeur vers le 1er element de l'utilisateur
  TYPE *fin_elem;   // pointeur vers le dernier element

public:
  // NOTE: si vous ne le saviez pas dÃ©jÃ , les dÃ©clarations de fonctions en
  // en-tÃªte n'exigent pas de donner de nom aux paramÃ¨tres.  Par contre, les
  // paramÃ¨tres doivent Ãªtre nommÃ©s dans l'implÃ©mentation.

  // constructeur initialement avec 0 elements - a vous de choisir une capacite
  // initiale
  deque();

  // constructeur avec dimension initiale - a vous de choisir une capacite
  // initiale
  deque(size_t);

  // Copieur.  Il est attendu que debut_elem et fin_elem soient aient le meme
  // positionnement que la source, relativement a debut_cap.
  deque(const deque &);

  // destructeur
  ~deque();

  // affectateur.  Il est attendu que debut_elem et fin_elem soient aient le
  // meme positionnement que la source,
  //  relativement a debut_cap.
  deque &operator=(const deque &);

  // changement de dimension.  Si la nouvelle dimension est plus petite que la
  // capacite, ne pas detruire le tableau actuel.  Si la nouvelle dimension est
  // plus grande que la capacite, detruire.
  void resize(size_t);

  // changement de la capacite - si plus petite que la dimension, alors certain
  // Ã©lÃ©ments seront perdus. Il est attendu que reserve detruise toujours le
  // tableau en memoire, peu importe le parametre
  void reserve(size_t);

  // mise a zero de la capacite (et de la dimension)
  void clear();

  // ajouter element au debut
  void push_front(const TYPE &);

  // retirer premier element (ne fait rien si vide)
  void pop_front();

  // ajouter element a la fin
  void push_back(const TYPE &);

  // retirer dernier element (ne fait rien si vide)
  void pop_back();

  // permutation: Ã©change le contenu de *this avec celui de l'argument.
  // Fonction standard de la SL.
  void swap(deque &);

  // selecteur : taille
  size_t size() const;

  // selecteur : est vide ?
  bool empty() const;

  // selecteur : dernier element
  TYPE &back();

  // selecteur const : dernier element
  const TYPE &back() const;

  // selecteur : premier element
  TYPE &front();

  // selecteur const : premier element
  const TYPE &front() const;

  // selecteur : ieme element.  Ne PAS vÃ©rifier les bornes du paramÃ¨tre.
  TYPE &operator[](size_t);

  // selecteur const : ieme element.  Ne PAS vÃ©rifier les bornes du paramÃ¨tre.
  // Cette version sera appelÃ©e dans un contexte const (par ex, si une fonction
  // const utilise le [])
  const TYPE &operator[](size_t) const;

  // affichage des Ã©lÃ©ments du premier au dernier
  void afficher() const;
};

////////////////////////////////////////////////////////////////////////////////////
// IMPLÃ‰MENTATION
////////////////////////////////////////////////////////////////////////////////////

template <typename TYPE> deque<TYPE>::deque() {
  size_t initial_capacity = 1;
  debut_cap = new TYPE[initial_capacity]();
  fin_cap = debut_cap;
  debut_elem = fin_elem = debut_cap;
  fin_elem = debut_elem - 1;
}

template <typename TYPE> deque<TYPE>::deque(size_t n) : deque() {
  debut_cap = new TYPE[n]();
  fin_cap = debut_cap + n - 1;
  debut_elem = fin_elem = debut_cap;
  fin_elem = debut_elem + n - 1;
}

template <typename TYPE> deque<TYPE>::deque(const deque &src) : deque() {
  /* Ã  implÃ©menter */
  size_t capacity = src.fin_cap - src.debut_cap + 1;
  debut_cap = new TYPE[capacity]();
  fin_cap = debut_cap + capacity - 1;
  debut_elem = debut_cap + (src.debut_elem - src.debut_cap);
  fin_elem = debut_cap + (src.fin_elem - src.debut_cap);

  for (size_t i = 0; i < src.size(); i++) {
    debut_cap[i] = src.debut_cap[i];
  }
}

template <typename TYPE> deque<TYPE>::~deque() { delete[] debut_cap; }

template <typename TYPE> deque<TYPE> &deque<TYPE>::operator=(const deque &src) {
  /* Ã  implÃ©menter */
  if (this != &src) {
    delete[] debut_cap;

    size_t capacity = src.fin_cap - src.debut_cap + 1;
    debut_cap = new TYPE[capacity]();
    fin_cap = debut_cap + capacity - 1;
    debut_elem = debut_cap + (src.debut_elem - src.debut_cap);
    fin_elem = debut_cap + (src.fin_elem - src.debut_cap);

    for (size_t i = 0; i < src.size(); i++) {
      debut_cap[i] = (*this)[i];
    }
  }
  return *this;
}

template <typename TYPE> void deque<TYPE>::resize(size_t n) {
  if (n <= size()) {
        fin_elem = debut_elem + n - 1;
    } else {
        reserve(n);
        fin_elem = debut_elem + n - 1;
    }
}

template <typename TYPE> void deque<TYPE>::reserve(size_t n) {
 if (n <= (fin_cap - debut_cap + 1)) return;

    size_t new_cap = n;
    TYPE* new_data = new TYPE[new_cap];
    size_t current_size = size();

    std::copy(debut_cap, fin_cap + 1, new_data);

    delete[] debut_cap;
    debut_cap = new_data;
    fin_cap = debut_cap + new_cap - 1;
    debut_elem = debut_cap;
    fin_elem = debut_cap + current_size - 1;
}

template <typename TYPE> void deque<TYPE>::push_front(const TYPE &val) {
   if (debut_elem == debut_cap) {
        size_t current_size = size();
        reserve(current_size * 2 + 1);
    }

    if (empty()) {
        debut_elem = fin_elem = debut_cap;
    } else {
        --debut_elem;
    }

    *debut_elem = val;
}

template <typename TYPE> void deque<TYPE>::push_back(const TYPE &val) {
  if (fin_elem == fin_cap) {
        size_t current_size = size();
        reserve(current_size * 2);
    }

    if (empty()) {
        debut_elem = fin_elem = debut_cap;
    } else {
        ++fin_elem;
    }

    *fin_elem = val;
}

template <typename TYPE> void deque<TYPE>::pop_front() { 
   if (!empty()) {
        if (debut_elem == fin_elem) {
            debut_elem = fin_elem = nullptr;
        } else {
            ++debut_elem;
        }
    }
 }

template <typename TYPE> void deque<TYPE>::pop_back() {  
  if (!empty()) {
        if (debut_elem == fin_elem) {
            debut_elem = fin_elem = nullptr;
        } else {
            --fin_elem;
        }
    } 
  }

template <typename TYPE> size_t deque<TYPE>::size() const {
  if (debut_elem <= fin_elem) {
    return fin_elem - debut_elem + 1;
  } else {
    return 0;
  }
}

template <typename TYPE> bool deque<TYPE>::empty() const {
  return (size() == 0);
}

template <typename TYPE> void deque<TYPE>::swap(deque &src) {
  std::swap(debut_cap, src.debut_cap);
  std::swap(debut_elem, src.debut_elem);
  std::swap(fin_cap, src.fin_cap);
  std::swap(fin_elem, src.fin_elem);
}

template <typename TYPE> TYPE &deque<TYPE>::back() {
  return (*this)[size() - 1];
}

template <typename TYPE> const TYPE &deque<TYPE>::back() const {
  return (*this)[size() - 1];
}

template <typename TYPE> TYPE &deque<TYPE>::front() { return (*this)[0]; }

template <typename TYPE> const TYPE &deque<TYPE>::front() const {
  return (*this)[0];
}

template <typename TYPE> TYPE &deque<TYPE>::operator[](size_t i) {

  return *(debut_elem + i);
}

template <typename TYPE> const TYPE &deque<TYPE>::operator[](size_t i) const {

  return *(debut_elem + i);
}

template <typename TYPE> void deque<TYPE>::afficher() const {
  std::cout << "Positions relatives a debut_cap: (-1 veut dire nullptr)"
            << std::endl;
  std::cout << "debut_elem = " << (debut_elem ? (debut_elem - debut_cap) : -1)
            << std::endl;
  std::cout << "fin_elem = " << (fin_elem ? (fin_elem - debut_cap) : -1)
            << std::endl;
  std::cout << "fin_cap = " << (fin_cap ? (fin_cap - debut_cap) : -1)
            << std::endl;

  std::cout << "Capacite = " << (debut_cap ? fin_cap - debut_cap + 1 : 0)
            << std::endl;
  std::cout << "Dimension = " << size() << std::endl;

  if (empty()) {
    std::cout << "Le deque est vide." << std::endl;
  } else {
    std::cout << "Elements utilisateurs = [";
    for (size_t i = 0; i < size(); i++) {
      std::cout << (*this)[i] << (i < size() - 1 ? ", " : "");
    }
    std::cout << "]" << std::endl;

    std::cout << "Elements de debut_cap = [";

    for (size_t i = 0; i < fin_cap - debut_cap + 1; i++) {
      // si on est dans la zone utilisateur
      if ((debut_elem <= fin_elem && debut_cap + i >= debut_elem &&
           debut_cap + i <= fin_elem) ||
          (fin_elem < debut_elem &&
           (debut_cap + i <= fin_elem || debut_cap + i >= debut_elem))) {
        std::cout << debut_cap[i];
      } else {
        std::cout << "X";
      }

      std::cout << (i < fin_cap - debut_cap ? ", " : "");
    }
    std::cout << "]" << std::endl;
  }
}

#endif
