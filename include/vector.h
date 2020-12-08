/**
 * @file vector.h
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

template <class T> class vector : public container<T> {
public:
  /**
   * @brief funkcja dodająca element na koniec vectora
   *
   * @param item referencja na dodawany element, poźniej tworzona jest kopia,
   * więc tutaj warto przekazać referencję
   */
  void push_back(const T &item);

  /**
   * @brief funkcja dodająca element na początek vectora
   *
   * @param item referencja na dodawany element, poźniej tworzona jest kopia,
   * więc tutaj warto przekazać referencję
   */
  void push_front(const T &item);

  /**
   * @brief funkcja usuwająca element na końcu i zwracająca go
   *
   * @return T ostatni element
   */
  T pop_back();

  /**
   * @brief funkcja usuwająca element na początku i zwracająca go
   *
   * @return T pierwszy element
   */
  T pop_front();

  /**
   * @brief funkcja zamieniająca miejscami dwa elementy
   *
   * @param index1 indeks pierwszego elementu
   * @param index2 indeks drugiego elementu
   */
  void swap(const size_t index1, const size_t index2);

  /**
   * @brief funkcja sortująca vector
   *
   * @param ascendingOrder wybór porządku rosnącego lub
   */
  void sort(const bool ascendingOrder = true);
};


template <class T> void vector<T>::push_back(const T &item) {
  // wrapper dla funkcji chronionej z klasy nadrzędnej
  container<T>::add(item);
}

template <class T> void vector<T>::push_front(const T &item) {
    // wrapper dla funckcji z container<T>
  container<T>::add(item, 0);
}

template <class T> T vector<T>::pop_back() {
    //tymczasowy obiekt do którego przypisany zostanie ostatni obiekt
  T temp = container<T>::get(container<T>::size_of() - 1);
  //usunięcie ostatniego obiektu
  container<T>::delete_item(container<T>::size_of() - 1);
  return temp;
}

template <class T> T vector<T>::pop_front() {
    //tymczasowy obiekt do którego przypisany zostanie pierwszy obiekt
  T temp = container<T>::get(0);
  //usunięcie pierwszego obiektu
  container<T>::delete_item(0);
  return temp;
}

template <class T> void vector<T>::sort(const bool ascendingOrder) {
    //wrapper funkcji z container<T>
  container<T>::sort(ascendingOrder);
}

template <class T>
void vector<T>::swap(const size_t index1, const size_t index2) {
  T temp = container<T>::get(index1);
  T temp2 = container<T>::get(index2);
  container<T>::insert(temp, index2);
  container<T>::insert(temp2, index1);
}