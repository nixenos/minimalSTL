/**
 * @file list.h
 * @author Wojciech Janota
 * @brief 
 * @version 0.1
 * @date 2020-11-02
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#pragma once
#include <cstddef>
#include <iostream>
template <class T> class list {

  /**
   * @brief struktura przechowująca listę
   *
   */
  struct node {
    T data;
    node *prev;
    node *next;
  };

  node *pHead;
  size_t size;
  node *first;
  node *last;

  /**
   * @brief dodaje element na koniec listy
   *
   * @param item
   */
  inline void add(T item);

  /**
   * @brief dodaje element na konkretny indeks ("rozpycha" inne elementy)
   *
   * @param item element do dodania
   * @param index indeks do wstawienia elementu
   */
  void add(T item, const size_t index);

  /**
   * @brief pobiera element z podanego indeksu
   *
   * @param index indeks
   * @return T& zwracany element
   */
  T &get(const size_t index);

  /**
   * @brief czyści pamięć
   *
   * @param pHead pierwszy element (node)
   */
  void clear_memory(node *pHead);

public:
  /**
   * @brief Construct a new list object
   *
   */
  list();

  /**
   * @brief Destroy the list object
   *
   */
  ~list();

  /**
   * @brief zwraca wielkość listy
   *
   * @return int wielkość listy
   */
  inline int size_of() const;

  /**
   * @brief czy lista jest pusta
   *
   * @return true tak
   * @return false nie
   */
  inline bool empty() const;

  /**
   * @brief zwraca pierwszy element
   *
   * @return T& pierwszy element
   */
  inline T &front();

  /**
   * @brief zwraca ostatni element
   *
   * @return T& ostatni element
   */
  inline T &back();

  /**
   * @brief zwraca wskaźnik na pierwszy element
   *
   * @return T* wskaźnik na pierwszy element
   */
  inline T *begin();

  /**
   * @brief zwraca wskaźnik na ostatni element
   *
   * @return T* wskaźnik na ostatni element
   */
  inline T *end();

  /**
   * @brief dodaje element na koniec
   *
   * @param item element do dodania
   */
  void push_back(const T &item);

  /**
   * @brief dodaje element na początek
   *
   * @param item element do dodania
   */
  void push_front(const T &item);

  /**
   * @brief wstawia element na konkretny indeks
   *
   * @param item element do wstawienia
   * @param index indeks na którym ma być wstawiony
   */
  void insert(const T &item, const size_t index);

  /**
   * @brief usuwa element z końca
   *
   */
  void pop_back();

  /**
   * @brief usuwa element z początku
   *
   */
  void pop_front();

  /**
   * @brief usuwa element z podanego indeksu
   *
   * @param index indeks
   */
  void erase(size_t index);

  /**
   * @brief usuwa wszytskie wystapienia elementu
   *
   * @param item element do usunięcia
   */
  void remove(const T &item);

  /**
   * @brief operator wyłuskania []
   *
   * @param index indeks do pobrania
   * @return T& referencja do elementu
   */
  T &operator[](const size_t index);
};

template <class T> list<T>::list() {
  // tworzy nową listę i ustawia wielkość na 0
  this->pHead = new node;
  this->pHead->prev = nullptr;
  this->pHead->next = nullptr;
  this->size = 0;
  this->first = this->pHead;
  this->last = this->pHead;
}

template <class T> void list<T>::clear_memory(node *pHead) {
  if (pHead->next)
    clear_memory(pHead->next);
  delete pHead;
}

template <class T> list<T>::~list() { this->clear_memory(this->pHead); }

template <class T> inline int list<T>::size_of() const { return this->size; }

template <class T> inline bool list<T>::empty() const {
  return this->size == 0;
}

template <class T> inline T &list<T>::front() { return *(this->first); }

template <class T> inline T &list<T>::back() { return *(this->last); }

template <class T> inline T *list<T>::begin() { return this->first; }

template <class T> inline T *list<T>::end() { return this->last; }

template <class T> inline void list<T>::add(T item) {
  // tworzy nowy element
  this->last->next = new node;
  this->last->next->data = item;
  this->last->next->prev = this->last;
  this->last->next->next = nullptr;
  this->last = this->last->next;
  // zwiększa wielkość listy
  ++this->size;
}

template <class T> void list<T>::add(T item, const size_t index) {
  // sprawdza, czy indeks jest poprawny
  if (index < size) {
    node *pTemp = this->pHead;
    for (int i = 0; i < index; i++) {
      pTemp = pTemp->next;
    }
    // tworzy nowy element i wplata go pomiędzy dwa na podanym indeksie
    node *insertItem = new node;
    insertItem->next = pTemp->next;
    insertItem->prev = pTemp;
    insertItem->data = item;
    pTemp->next = insertItem;
    ++this->size;
    // jeżeli indeks jest równy wielkości listy dodaje element na końcu
    // (failsafe)
  } else if (index == size) {
    this->add(item);
  } else {
    std::cout << "Error: out of boundaries!\n";
    exit(EXIT_FAILURE);
  }
}

template <class T> T &list<T>::get(const size_t index) {
  // sprawdza poprawność indeksu
  if (index >= this->size) {
    std::cout << "Error: out of boundaries!\n";
    exit(EXIT_FAILURE);
  }
  node *pTemp = this->pHead;
  // przechodzi do indeksu
  for (int i = 0; i <= index; i++) {
    pTemp = pTemp->next;
  }
  // zwraca obiekt
  return pTemp->data;
}

template <class T> void list<T>::insert(const T &item, const size_t index) {
  this->add(item, index);
}

template <class T> void list<T>::push_back(const T &item) { this->add(item); }

template <class T> void list<T>::push_front(const T &item) {
  this->add(item, 0);
}

template <class T> void list<T>::erase(size_t index) {
  node *pTemp = this->pHead;
  // sprawdza poprawność indeksu
  if (index >= this->size) {
    std::cout << "Error: out of boundaries!\n";
    exit(EXIT_FAILURE);
  }
  // przechodzi do odpowiedniego elementu
  for (int i = 0; i <= index; i++) {
    pTemp = pTemp->next;
  }
  //"przeplata" sąsiednie elementy i usuwa obiekt
  pTemp->prev->next = pTemp->next;
  pTemp->next->prev = pTemp->prev;
  delete pTemp;
  pTemp = nullptr;
  --this->size;
}

template <class T> void list<T>::remove(const T &item) {
  node *pTemp = this->pHead;
  // szuka pierwszego wystąpienia elementu
  for (int i = 0; i < this->size; i++) {
    if (pTemp->data == item) {
      break;
    }
    pTemp = pTemp->next;
  }
  if (pTemp->data != item) {
    return;
  }
  // usuwa go
  pTemp->prev->next = pTemp->next;
  pTemp->next->prev = pTemp->prev;
  delete pTemp;
  pTemp = nullptr;
  --this->size;
}

template <class T> void list<T>::pop_front() { this->erase(0); }

template <class T> void list<T>::pop_back() { this->erase((this->size - 1)); }

template <class T> T &list<T>::operator[](const size_t index) {
  return this->get(index);
}