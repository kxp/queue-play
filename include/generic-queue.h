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
 
    /*template <typename T> */void Enqueue(T object);
    /*template <typename T> */T Dequeue();
    ~GenericQueue() {
        delete[] m_queue;
    }
private :
    uint32_t m_queue_size;
    // atomic operations
    std::atomic<uint32_t>  m_head_index;            // The next position where the data will be inserted
    std::atomic<uint32_t>  m_tail_index;            // the next position where the data will be removed

    T* m_queue;
};

template <typename T>
void GenericQueue<T>::Enqueue(T object) {
    if (m_head_index >= m_queue_size) {
        // Currently resize is not supported
        printf("Currently resize is not supported\n");
        return;
    }
    m_queue[m_head_index++] = object;
}

template <typename T>
T GenericQueue<T>::Dequeue() {
    if(m_tail_index == m_head_index) {
        // There is no data to retrieve
        printf("There is no data to retrieve\n");
        return nullptr;
    }
    return m_queue[m_tail_index++];
}
