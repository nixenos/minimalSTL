/**
 * @file set.h
 * @author Wojciech Janota
 * @brief 
 * @version 0.1
 * @date 2020-11-02
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#pragma once
#include "container.h"

template <class T> class set : public container<T> {
public:
  /**
   * @brief funkcja dodająca element do kontenera
   *
   * @param item element do dodania
   */
  void insert(const T &item);

  /**
   * @brief funkcja zwracająca indeks pierwszego nie mniejszego niż podany
   * elementu
   *
   * @param item element do sprawdzenia
   * @return int indeks znalezionego elementu, -1 jeżeli nie znaleziono elementu
   */
  int lower_bound(const T &item) const noexcept;

  /**
   * @brief funkcja zwracająca indeks pierwszego nie większego niż podany
   * elementu
   *
   * @param item element do sprawdzenia
   * @return int indeks znalezionego elementu, -1 jeżeli nie znaleziono elementu
   */
  int upper_bound(const T &item) const noexcept;
};

template <class T> void set<T>::insert(const T &item) {
    //przeszukuje kontener do elementu większego niż podany
  for (int i = 0; i <= this->size_of(); i++) {
      //jeżeli to ostatni element dodaje na koniec kontenera
    if (i == this->size_of()) {
      this->container<T>::add(item);
      //koniec pętli!
      break;
    }
    //jeżeli znalazła odpowiednie miejsce, wstawia tam obiekt
    if (this->container<T>::get(i) > item) {
      this->container<T>::add(item, i);
      //koniec pętli!
      break;
    }
  }
}

template <class T> int set<T>::lower_bound(const T &item) const noexcept {
    //przeszukuje kontener do pierwszego większego lub równego elementu i zwraca jego indeks
  for (int i = 0; i < this->container<T>::size_of(); i++) {
    if (this->container<T>::get(i) >= item) {
      return i;
    }
  }
  return -1;
}

template <class T> int set<T>::upper_bound(const T &item) const noexcept {
    //przeszukuje kontener do pierwszego mniejszego lub równego elementu i zwraca jego indeks
  for (int i = 0; i < this->container<T>::size_of(); i++) {
    if (this->container<T>::get(i) <= item) {
      return i;
    }
  }
  return -1;
}