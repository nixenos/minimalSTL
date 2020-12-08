/**
 * @file binary_tree.h
 * @author Wojciech Janota
 * @brief 
 * @version 0.1
 * @date 2020-11-02
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#pragma once
#include <stddef.h>

#include <iostream>

template <class T> class binary_tree {
  /**
   * @brief struktura struktury drzewa
   *
   */
  struct node {
    T data;
    node *left;
    node *right;
  };
  node *root;
  /**
   * @brief pomocnicza funkcja do zwracania lewego elementu rekurencyjnie
   *
   * @param item element z którego lewy element ma być zwrócony
   * @param pHead wskażnik na korzeń
   * @return T element po lewej stronie
   */
  T left_recursive(const T &item, node *pHead) const;

  /**
   * @brief pomocnicza funkcja do zwracania prawego elementu rekurencyjnie
   *
   * @param item element z którego prawy element ma być zwrócony
   * @param pHead wskażnik na korzeń
   * @return T element po prawej stronie
   */
  T right_recursive(const T &item, node *pHead) const;

  /**
   * @brief pomicnicza funkcja do usuwania rekurencyjnie elementu i jego
   * poddrzewa
   *
   * @param item element do usunięcia
   * @param pHead wskaźnik na korzeń
   */
  void delete_recursive(const T &item, node *pHead);

  /**
   * @brief pomocnicza funckja do usuwania node
   *
   * @param pHead wskaźnik na node
   */
  void delete_node(node *pHead);

  /**
   * @brief funkcja wypisująca drzewo w porządku inorder
   *
   * @param pHead wskaźnik na korzeń
   */
  void print(node *pHead) const noexcept;

public:
  /**
   * @brief Construct a new binary tree object
   *
   */
  binary_tree();

  /**
   * @brief Destroy the binary tree object
   *
   */
  ~binary_tree();

  /**
   * @brief wypisuje drzewo w porządku in-order
   *
   */
  void print() const noexcept;

  /**
   * @brief zwraca lewego syna ojca
   *
   * @param item ojciec
   * @return T lewy syn ojca
   */
  inline T left(const T &item) const;

  /**
   * @brief zwraca prawego syna ojca
   *
   * @param item ojciec
   * @return T prawy syn ojca
   */
  inline T right(const T &item) const;

  /**
   * @brief usuwa element
   *
   * @param item element
   */
  void delete_item(const T &item);

  /**
   * @brief czyści całe drzewo z pamięci
   *
   */
  void clear();

  /**
   * @brief wstawia wartość do drzewa
   *
   * @param item
   */
  void insert(const T &item);
};

template <class T> binary_tree<T>::binary_tree() { this->root = nullptr; }

template <class T> binary_tree<T>::~binary_tree() { this->clear(); }

template <class T> void binary_tree<T>::print(node *pHead) const noexcept {
  if (pHead) {
    // najpierw wypisuje lewych synów, potem prawych
    print(pHead->left);
    std::cout << pHead->data << "\n";
    print(pHead->right);
  }
}

template <class T> void binary_tree<T>::print() const noexcept {
  // wywołuje funkcję rekurencyjną
  this->print(this->root);
}

template <class T> void binary_tree<T>::clear() { delete_node(this->root); }

template <class T> void binary_tree<T>::delete_node(node *pHead) {
  if (pHead) {
    // usuwa wszystkie wychodzące node'y
    delete_node(pHead->right);
    delete_node(pHead->left);
    delete pHead;
    // ustawia wskaźnik na nullptr
    pHead = nullptr;
  }
}

template <class T>
void binary_tree<T>::delete_recursive(const T &item, node *pHead) {
  if (pHead) {
    if (pHead->right) {
      if (pHead->right->data == item) {
        // usuwa i ustawia wskaźnik na null
        delete_node(pHead->right);
        pHead->right = nullptr;
        return;
      } else {
        // lub wywołuje się dla synów
        delete_recursive(item, pHead->left);
        delete_recursive(item, pHead->right);
      }
    }
    if (pHead->left) {
      if (pHead->left->data == item) {
        // usuwa i ustawia wskaźnik na null
        delete_node(pHead->left);
        pHead->left = nullptr;
        return;
      } else {
        // lub wywołuje się dla synów
        delete_recursive(item, pHead->left);
        delete_recursive(item, pHead->right);
      }
    }
  }
}

template <class T> void binary_tree<T>::delete_item(const T &item) {
  delete_recursive(item, this->root);
}

template <class T> T binary_tree<T>::right(const T &item) const {
  return this->right_recursive(item, this->root);
}

template <class T> T binary_tree<T>::left(const T &item) const {
  return this->left_recursive(item, this->root);
}

template <class T>
T binary_tree<T>::left_recursive(const T &item, node *pHead) const {
  if (pHead) {
    if (pHead->data == item) {
      if (pHead->left) {
        return pHead->left->data;
      } else {
        std::cout << "Error: parent has no left child!\n";
        exit(EXIT_FAILURE);
      }
    } else {
      left_recursive(item, pHead->left);
      left_recursive(item, pHead->right);
    }
  }
}

template <class T>
T binary_tree<T>::right_recursive(const T &item, node *pHead) const {
  if (pHead) {
    if (pHead->data == item) {
      if (pHead->right) {
        return pHead->right->data;
      } else {
        std::cout << "Error: parent has no left child!\n";
        exit(EXIT_FAILURE);
      }
    } else {
      left_recursive(item, pHead->left);
      left_recursive(item, pHead->right);
    }
  }
}

template <class T> void binary_tree<T>::insert(const T &item) {
  if (this->root == nullptr) {
    // tworzy nowy obiekt dla pustego drzewa i ustawia jako korzeń
    this->root = new node;
    this->root->data = item;
    this->root->left = nullptr;
    this->root->right = nullptr;
  } else {
    node *pHead = this->root;
    node *qHead;
    // tworzy obiekt tymczasowy
    node *tmp = new node;
    tmp->data = item;
    tmp->right = nullptr;
    tmp->left = nullptr;
    while (pHead) {
      // szuka odpowiedniego wolnego miejsca
      qHead = pHead;
      if (pHead->data <= item) {
        pHead = pHead->right;
      } else {
        pHead = pHead->left;
      }
    }
    // wstawia tam obiekt tymczasowy
    if (qHead->data <= item) {
      qHead->right = tmp;
    } else {
      qHead->left = tmp;
    }
  }
}