/**
 * @file queue.h
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
class queue : public container<T>{
    public:

        /**
         * @brief funkcja dodająca element na koniec vectora
         * 
         * @param item referencja na dodawany element, poźniej tworzona jest kopia, więc tutaj warto przekazać referencję
         */
        void push_back(const T &item);

        /**
         * @brief funkcja usuwająca element na początku i zwracająca go
         * 
         * @return T pierwszy element
         */
        T pop_front();
};

template <class T>
void queue<T>::push_back(const T &item){
    // wrapper dla funkcji chronionej z klasy nadrzędnej
    container<T>::add(item);
}

template <class T>
T queue<T>::pop_front(){
    //pobiera pierwszy element
    T temp = container<T>::get(0);
    //usuwa pierwszy element i zwraca go
    container<T>::delete_item(0);
    return temp;
}