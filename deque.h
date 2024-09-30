/*
Nom:Thomas Toulouse                     CIP:tout3815
Nom:Canis Christabelle Tchonet Toukam   CIP:tchc0901
*/
#ifndef TP2_DEQUE_H
#define TP2_DEQUE_H

#include <iostream>
#include <stdexcept>

template <typename TYPE> class deque {
private:
  TYPE *debut_cap;
  TYPE *fin_cap;
  TYPE *debut_elem;
  TYPE *fin_elem;

public:
  deque();
  deque(size_t);
  deque(const deque &);
  ~deque();

  deque &operator=(const deque &);

  void resize(size_t);
  void reserve(size_t);
  void clear();

  void push_front(const TYPE &);
  void pop_front();
  void push_back(const TYPE &);
  void pop_back();

  void swap(deque &);

  size_t size() const;
  bool empty() const; // Vérification si vide

  TYPE &back();
  const TYPE &back() const;
  TYPE &front();
  const TYPE &front() const;

  TYPE &operator[](size_t);
  const TYPE &operator[](size_t) const;

  void afficher() const;
};

template <typename TYPE> deque<TYPE>::deque() {
  size_t capacite_initiale = 8;

  debut_cap = new TYPE[capacite_initiale];
  fin_cap = debut_cap + capacite_initiale - 1;
  debut_elem = fin_elem = nullptr;
}

template <typename TYPE> deque<TYPE>::deque(size_t n) : deque() {
  reserve(n);
  fin_elem = debut_elem = debut_cap;
}

template <typename TYPE>
deque<TYPE>::deque(const deque &src) : deque(src.size()) {
  size_t n = src.size();
  debut_elem = debut_cap;
  fin_elem = debut_cap + n - 1;

  for (size_t i = 0; i < n; i++) {
    debut_cap[i] = src[i];
  }
}

template <typename TYPE> deque<TYPE>::~deque() { delete[] debut_cap; }

template <typename TYPE> deque<TYPE> &deque<TYPE>::operator=(const deque &src) {
  if (this != &src) {
    reserve(src.size());
    size_t n = src.size();
    debut_elem = debut_cap;
    fin_elem = debut_cap + n - 1;

    for (size_t i = 0; i < n; i++) {
      debut_cap[i] = src[i];
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
  if (n <= (fin_cap - debut_cap + 1))
    return;

  size_t new_cap = n;
  TYPE *new_data = new TYPE[new_cap];
  size_t current_size = size();

  for (size_t i = 0; i < current_size; ++i) {
    new_data[i] = (*this)[i];
  }
  delete[] debut_cap;
  debut_cap = new_data;
  fin_cap = debut_cap + new_cap - 1;
  debut_elem = debut_cap;
  fin_elem = debut_cap + current_size - 1;
}

template <typename TYPE> void deque<TYPE>::push_front(const TYPE &val) {

  if (debut_cap == nullptr || debut_elem == debut_cap) {
    size_t current_size = size();
    size_t new_cap = current_size * 2;
    reserve(new_cap);
    debut_elem = debut_cap + (new_cap - current_size);
    fin_elem = debut_elem + current_size - 1;
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
    reserve(current_size * 2 + 1);
  }

  if (empty()) {
    debut_elem = fin_elem = fin_cap = debut_cap;

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
      fin_cap = debut_cap - 1;

    } else {
      --fin_elem;
    }
  }
}

template <typename TYPE> size_t deque<TYPE>::size() const {
  if (empty())
    return 0;
  return fin_elem - debut_elem + 1;
}

// Ajout de la définition de empty()
template <typename TYPE> bool deque<TYPE>::empty() const {
  return debut_elem == nullptr || fin_elem == nullptr;
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

template <typename TYPE> TYPE &deque<TYPE>::operator[](size_t i) {
  return *(debut_elem + i);
}

template <typename TYPE> const TYPE &deque<TYPE>::operator[](size_t i) const {
  return *(debut_elem + i);
}

template <typename TYPE> void deque<TYPE>::afficher() const {
  std::cout << "Positions relatives à debut_cap: (-1 veut dire nullptr)"
            << std::endl;
  std::cout << "debut_elem = " << (debut_elem ? (debut_elem - debut_cap) : -1)
            << std::endl;
  std::cout << "fin_elem = " << (fin_elem ? (fin_elem - debut_cap) : -1)
            << std::endl;
  std::cout << "fin_cap = " << (fin_cap ? (fin_cap - debut_cap) : -1)
            << std::endl;
  std::cout << "Capacité = " << (debut_cap ? fin_cap - debut_cap + 1 : 0)
            << std::endl;
  std::cout << "Dimension = " << size() << std::endl;

  if (empty()) {
    std::cout << "Le deque est vide." << std::endl;
  } else {
    std::cout << "Éléments utilisateurs = [";
    for (size_t i = 0; i < size(); i++) {
      std::cout << (*this)[i] << (i < size() - 1 ? ", " : "");
    }
    std::cout << "]" << std::endl;

    std::cout << "Éléments de debut_cap = [";
    for (size_t i = 0; i < fin_cap - debut_cap + 1; i++) {
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

#endif // TP2_DEQUE_H
