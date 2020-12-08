/**
 * @file priority_queue.h
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
#include <algorithm>

typedef enum priorityType {MIN, MAX} priorityType;

template <class T>
class priority_queue : public container<T>{
    priorityType priority;
    public:

        /**
         * @brief ustawia priorytet kolejki
         * 
         * @param choice jaki priorytet (najmniejszy lub największy)
         */
        inline void setPriority(priorityType choice);

        /**
         * @brief wkłada element do kolejki
         * 
         * @param item element do włożenia
         */
        void push(const T &item);

        /**
         * @brief ściąga element z kolejki i zwraca ten element
         * 
         * @return T ściągnięty element
         */
        T pop();
};

template <class T>
inline void priority_queue<T>::setPriority(priorityType choice){
    this->priority = choice;
}

template <class T>
void priority_queue<T>::push(const T &item){
    //wrapper dla funkcji z container<T>
    container<T>::add(item);
}

template <class T>
T priority_queue<T>::pop(){
    T temp = this->container<T>::get(0);
    size_t index=0;
    switch(this->priority){
        case MAX:
        //przeszukuje kontener, szuka największego elementu
        for(int i=0; i<this->container<T>::size_of(); i++){
            if(this->container<T>::get(i) > temp){
                temp = this->container<T>::get(i);
                index = i;
            }
        }
        break;
        case MIN:
        //przeszukuje kontener, szuka najmniejszego elementu
        for(int i=0; i<this->container<T>::size_of(); i++){
            if(this->container<T>::get(i) < temp){
                temp = this->container<T>::get(i);
                index = i;
            }
        }
        break;
    }
    //usuwa znaleziony element i zwraca go
    this->container<T>::delete_item(index);
    return temp;
}