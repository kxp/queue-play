#pragma once
#include <cstdint>
#include <thread>
#include <vector>
#include "generic-queue.h"
#include "state.h"

class NumberGenerator
{
public:
    /// <summary>
    /// Initializes a new instance of the <see cref="NumberGenerator"/> class.
    /// </summary>
    /// <param name="shared_queue">The shared queue.</param>
    /// <param name="amount_runs">The amount runs. If a negative value is provided the function will run indefinitely</param>
    NumberGenerator(GenericQueue<std::vector<int64_t>> &shared_queue, int32_t amount_runs)
                : m_queue(shared_queue)
                , m_amount_of_runs(amount_runs) {
        m_current_state = state::NotInitialized;
    }
     ~NumberGenerator() {
        m_current_state = state::Terminated;
    }

    void Start();
    void Stop();

private:

    void generator();

    GenericQueue<std::vector<int64_t>>& m_queue;
    std::thread m_producer_thread;

    state m_current_state;
    uint32_t m_amount_of_runs;              // Number of vectors generated
};
