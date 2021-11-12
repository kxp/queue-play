#pragma once
#include <array>
#include <atomic>
#include <cstdint>
#include <cstdio>

template <typename T>
class GenericQueue
{
public:
    GenericQueue(uint32_t initial_size)
                : m_queue_size(initial_size) {
        // initial position of the buffers
        m_head_index.store(0);
        m_tail_index.store(0);
        m_queue = new T[initial_size];
    }
    ~GenericQueue() {
        delete[] m_queue;
    }

    uint32_t Count() const;
    bool IsEmpty() const;

    void Enqueue(T& object);            // Accepts a reference of an object
    void Enqueue(const T object);       // a constant type.
   
    bool Dequeue(T& object);

private :
    uint32_t m_queue_size;
    // atomic operations
    std::atomic<uint32_t>  m_head_index;            // The next position where the data will be inserted
    std::atomic<uint32_t>  m_tail_index;            // the next position where the data will be removed

    T* m_queue;
};

//Managing functions

template <typename T>
uint32_t GenericQueue<T>::Count() const {
    return m_head_index - m_tail_index;
}

template <typename T>
bool GenericQueue<T>::IsEmpty() const {
    if (Count() == 0)
        return true;
    return false;
}

// Operation functions

template <typename T>
void GenericQueue<T>::Enqueue(T& object) {
    if (m_head_index >= m_queue_size) {
        // Currently resize is not supported
        printf("Currently resize is not supported\n");
        return;
    }
    m_queue[m_head_index++] = object;
}

template <typename T>
void GenericQueue<T>::Enqueue(const T object) {
    if (m_head_index >= m_queue_size) {
        // Currently resize is not supported
        printf("Currently resize is not supported\n");
        return;
    }
    m_queue[m_head_index++] = object;
}


template <typename T>
bool GenericQueue<T>::Dequeue(T& object ) {
    if(m_tail_index == m_head_index) {
        //printf("There is no data to retrieve\n");
        return false;
    }
    object =  m_queue[m_tail_index++];
    return true;
}
