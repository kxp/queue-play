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
        round_complete = false;
        m_queue = new T[initial_size];
    }
    ~GenericQueue() {
        delete[] m_queue;
    }

    uint32_t Count() const;
    bool IsEmpty() const;

    //bool TryEnqueue(T& object);           // Accepts a reference of an object
    bool TryEnqueue(const T object);        // a constant type.
   
    bool TryDequeue(T& object);

private :
    uint32_t m_queue_size;
    bool round_complete;
    // atomic operations
    std::atomic<uint32_t>  m_head_index;            // The next position where the data will be inserted
    std::atomic<uint32_t>  m_tail_index;            // the next position where the data will be removed


    T* m_queue;
};

//Managing functions

template <typename T>
uint32_t GenericQueue<T>::Count() const {
    if (round_complete == false)
        return m_head_index - m_tail_index;

    const auto remaining_space_until_end = m_queue_size - m_tail_index;
    return remaining_space_until_end + m_head_index;
}

template <typename T>
bool GenericQueue<T>::IsEmpty() const {
    if (Count() == 0)
        return true;
    return false;
}

// Operation functions

//template <typename T>
//bool GenericQueue<T>::TryEnqueue(T& object) {
//    if (m_head_index >= m_queue_size && round_complete == true) {
//        // Currently resize is not supported
//        printf("Currently resize is not supported\n");
//        return false;
//    }
//    else if (m_head_index >= m_queue_size && round_complete == false) {
//        // goes back to start
//        printf("Round completed\n");
//        round_complete = true;
//        m_head_index = 0;
//    }
//    if (round_complete == true && m_head_index == m_tail_index) {
//        printf("Buffer full!\n");
//        return false;
//    }
//
//    m_queue[m_head_index++] = object;
//    return true;
//}

template <typename T>
bool GenericQueue<T>::TryEnqueue(const T object) {
    if (m_head_index >= m_queue_size && round_complete == true) {
        // Currently resize is not supported
        printf("Currently resize is not supported\n");
        return false;
    }
    else if (m_head_index >= m_queue_size && round_complete == false) {
        // goes back to start
        printf("Round completed\n");
        round_complete = true;
        m_head_index = 0;
    }
    if (round_complete == true && m_head_index == m_tail_index) {
        printf("Buffer full!\n");
        return false;
    }

    m_queue[m_head_index++] = object;
    return true;
}


template <typename T>
bool GenericQueue<T>::TryDequeue(T& object ) {
    if(m_tail_index == m_head_index) {
        printf("There is no data to retrieve\n");
        return false;
    } else if (m_tail_index == m_queue_size) {
        printf("Its going around on dequeue\n");
        m_tail_index = 0;
        if (round_complete == true)
            round_complete = false;
        else {
            printf("Failled to deque\n");
            //probably the buffer is full, and we need to re-evalute in the next time we enter
            return false;
        }
    }
    object =  m_queue[m_tail_index++];
    return true;
}
