/**
 * @file container.h
 * @author Wojciech Janota
 * @brief 
 * @version 0.1
 * @date 2020-11-02
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#pragma once
#include <algorithm>
#include <cstddef>
#include <exception>
#include <functional>
#include <iostream>
#include <stdexcept>
#define START_SIZE 32
#define RESIZE_STEP 64

/**
 * @brief bazowa klasa zarządzająca pamięcią, implementująca podstawowe
 * funkcjonalności itd.
 *
 */
template <class T> class container {
private:
  T *data;
  size_t size;
  size_t realSize;

public:
  /**
   * @brief Konstruktor bezparametryczny, inicjalizuje pusty kontener
   *
   */
  container();

  /**
   * @brief Destruktor zwalnia pamięć alokowaną dynamicznie,
   * jest wirtualna, aby niemożliwe było stworzenie obiektu z klasy container
   *
   */
  virtual ~container() = 0;

  /**
   * @brief funkcja zwracająca wielkość kontenera
   *
   * @return const size_t wielkość kontenera, 0 jeżeli pusty
   */
  inline size_t size_of() const noexcept;

  /**
   * @brief funkcja sprawdzająca, czy dany element wystepuje w kontenerze
   *
   * @param item element do sprawdzenia
   * @return true element jest w kontenerze
   * @return false elementu nie ma w kontenerze
   */
  bool contains(const T &item) const noexcept;

  /**
   * @brief funkcja sprawdzająca, czy kontener jest pusty
   *
   * @return true kontener jest pusty
   * @return false kontener nie jest pusty
   */
  inline bool empty() const noexcept;

  /**
   * @brief funkcja zwracająca pierwszy element kontenera
   *
   * @return T pierwszy element kontenera
   */
  inline T begin() const noexcept;

  /**
   * @brief funkcja zwracająca ostatni element kontenera
   *
   * @return T ostatni element kontenera
   */
  inline T end() const noexcept;

  /**
   * @brief funkcja usuwająca wszystkie elementy z kontenera, lecz nie
   * zwalniająca pamięci
   *
   */
  void clear() noexcept;

  /**
   * @brief funkcja usuwająca element na podanym indeksie
   *
   * @param index indeks wystapienia elementu
   */
  void delete_item(const size_t &index) noexcept;

  /**
   * @brief funkcja zliczająca wystąpienia danego elementu w kontenerze
   *
   * @param item szukany element
   * @return const size_t liczba wystapień danego elementu
   */
  size_t count(const T &item) const noexcept;

  /**
   * @brief funkcja znajdująca indeks elementu
   *
   * @param item szukany element
   * @return const int indeks szukanego elementu, -1 jeżeli element nie
   * występuje
   */
  int find(const T &item) const noexcept;

  /**
   * @brief operator wyłuskania []
   *
   * @param index indeks elementu
   * @return T& referencja
   */
  T &operator[](const size_t index);

protected:
  /**
   * @brief funkcja dodająca element na koniec kontenera
   *
   * @param item element do dodania
   */
  void add(const T item);

  /**
   * @brief przeładowana funkcja add(), dodająca element w konkretnym indeksie,
   * "rozpychająca" pozostałe elementy
   *
   * @param item element do dodania
   * @param index indeks na którym na znaleźć się ten element
   */
  void add(const T item, const size_t index);

  /**
   * @brief funkcja pobierająca element z podanego indeksu
   *
   * @param index indeks na którym jest element
   * @return T element, który ma zostać zwrócony
   */
  T &get(const size_t index);

  /**
   * @brief funkcja zmieniająca wielkość kontenera
   *
   * @param step kolejna wielkość kontenera
   */
  void resize(const size_t step);

  /**
   * @brief funkcja sortująca wewnętrzną tablicę kontenera
   *
   * @param ascendingOrder jeżeli True, sortuje rosnąco, jeżeli false malejąco,
   * domyślnie True
   */
  void sort(const bool ascendingOrder = true);

  /**
   * @brief funkcja wstawiająca element na daną pozycję
   *
   * @param item element do wstawienia
   * @param index indeks na którym ma być wstawiony element
   */
  void insert(const T item, const size_t index);

  /**
   * @brief funkcja czyszcząca pamięć obiektu
   *
   */
  void clear_memory();
};

template <class T> container<T>::container() {
	//ustawia początkową wewnętrzną tablicę danych na określone wielkości
  this->data = new T[START_SIZE];
  this->size = 0;
  this->realSize = START_SIZE;
}

template <class T> container<T>::~container() {
  this->clear_memory();
}

template <class T> void container<T>::clear_memory() {
	//usuwa wewnętrzną tablicę danych
  delete[] this->data;
}

template <class T> inline size_t container<T>::size_of() const noexcept {
  return this->size;
}

template <class T>
bool container<T>::contains(const T &item) const noexcept {
	//przeszukuje całą wew. tablicę i jeżeli znajdzie identyczny obiekt, zwraca jego indeks
  for (int i = 0; i < this->size; i++) {
    if (*(data + i) == item) {
      return true;
    }
  }
  return false;
}

template <class T> inline bool container<T>::empty() const noexcept {
	//jeżeli wielkość kontenera to zero, zwraca prawdę
  return this->size == 0 ? true : false;
}

template <class T> inline T container<T>::begin() const noexcept {
  return this->data[0];
}

template <class T> inline T container<T>::end() const noexcept {
  return this->data[this->size - 1];
}

template <class T>
void container<T>::delete_item(const size_t &index) noexcept {
	//przenosi wszystkie obiekty o jeden indeks w lewo
  for (int i = index; i < (this->size - 1); i++) {
    data[i] = data[i + 1];
  }
  //zmniejsza wielkość kontenera
  --(this->size);
  //optymalizacja pamięci, jeżeli róznica jest większa, niż krok zwiększenia pojemności kontenera, dealokuje nadmiarową pamięć
  if ((this->realSize - this->size) > RESIZE_STEP) {
    this->resize(this->realSize - RESIZE_STEP);
  }
}

template <class T> void container<T>::clear() noexcept {
	//usuwa obecną tablicę
  delete[] this->data;
  //tworzy nową i ustawia rozmiar kontenera na 0
  this->data = new T[START_SIZE];
  this->realSize = START_SIZE;
  this->size = 0;
}

template <class T>
size_t container<T>::count(const T &item) const noexcept {
  size_t counter = 0;
  for (int i = 0; i < this->size; i++) {
    if (this->data[i] == item) {
      ++counter;
    }
  }
  return counter;
}

template <class T> int container<T>::find(const T &item) const noexcept {
  for (int i = 0; i < this->size; i++) {
    if (this->data[i] == item) {
      return i;
    }
  }
  //jeżeli nie znajdzie elementu, zwraca -1
  return -1;
}

template <class T> void container<T>::resize(const size_t step) {
  T *tmp = new T[step];
  //jeżeli nie udało się zainicjalizować pamięci, błąd
  if (tmp == nullptr) {
    std::cout << "Bad alloc\n";
	exit(EXIT_FAILURE);
  }
  //przekopiowanie starej tablicy
  for (int i = 0; i < this->size; i++) {
    tmp[i] = this->data[i];
  }
  //podmiana starej tablicy na nową
  delete[] this->data;
  this->data = tmp;
  this->realSize = step;
}

template <class T> void container<T>::add(const T item) {
  //jeżeli brakuje miejsca, zwiększa tablicę
  if (this->realSize == this->size) {
    this->resize(this->realSize + RESIZE_STEP);
  }
  //dodaje na koniec i zwiększa wielkość kontenera
  this->data[this->size] = item;
  ++(this->size);
}

template <class T> void container<T>::add(const T item, const size_t index) {
  //jeżeli indeks jest większy niż wielkość kontenera, błąd
  if (index > this->realSize) {
    std::cout << "Error: out of boundaries!\n";
	exit(EXIT_FAILURE);
  }
  //jeżeli brakuje miejsca, zwiększa tablicę
  if (this->realSize == this->size) {
    this->resize(RESIZE_STEP);
  }
  ++(this->size);
  //rotacja elementów w prawo, przesuwa wszystko o jeden indeks w prawo od miejsca, gdzie ma być wstawiony nowy element
  std::rotate(this->data + index, this->data + this->size - 1,
              this->data + this->size);
  this->data[index] = item;
}

template <class T> T &container<T>::get(const size_t index) {
	//sprawdzenie czy mieści się w obecnej wielkości kontenera
  if (index < this->size) {
    return this->data[index];
  } else {
    std::cout << "Error: out of boundaries!\n";
    exit(EXIT_FAILURE);
  }
}

template <class T> T &container<T>::operator[](const size_t index) {
  return this->get(index);
}

template <class T> void container<T>::sort(const bool ascendingOrder) {
	//użycie funkcji z biblioteki alghoritm
  if (ascendingOrder) {
    std::sort(this->data, this->data + this->size);
  } else {
    std::sort(this->data, this->data + this->size, std::greater<T>());
  }
}

template <class T> void container<T>::insert(const T item, const size_t index) {
  this->data[index] = item;
}