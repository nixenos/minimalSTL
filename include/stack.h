/**
 * @file stack.h
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

template <class T>
class stack : public container<T>{
    public:

        /**
         * @brief funkcja wstawiąjąca element na stos
         * 
         * @param item element do wstawienia
         */
        inline void insert(const T &item);

        /**
         * @brief funkcja zwracająca element z góry stosu
         * 
         * @return T pierwszy element na stosie
         */
        inline T pop();
};

template <class T>
inline void stack<T>::insert(const T &item){
    //wrapper funkcji z container<T>
    this->container<T>::add(item, 0);
}

template <class T>
inline T stack<T>::pop(){
    //pobiera pierwszy element kontenera
    T temp = this->container<T>::get(0);
    //usuwa go
    this->container<T>::delete_item(0);
    //zwraca obiekt tymczasowy
    return temp;
}