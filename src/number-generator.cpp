#include "number-generator.h"

#include <functional>

#ifdef _WIN32
#include <Windows.h> // to have Sleep function
#else
#include <unistd.h>
#endif


constexpr uint32_t kNumberEntries = 500;

void NumberGenerator::Start()
{
    if(m_current_state == state::Started || m_current_state == state::Terminated)
        return; 

    m_current_state = state::Started;
    m_producer_thread = std::thread(&NumberGenerator::generator, this);
}

void NumberGenerator::Stop()
{
    if(m_current_state != state::Started)
        return;

    // sets the condition to stop the execution
    m_current_state = state::Stopped;

    //waits for it to finish
    if (m_producer_thread.joinable() == true)
        m_producer_thread.join();

}

void NumberGenerator::generator()
{
    int32_t run_counter = 0;
    while (m_current_state == state::Started) {

        std::vector<int32_t> generated_values;

        for (int i = 0; i < kNumberEntries; ++i) {
            auto value = rand();
            //printf("Generated value:%d\n", value);
            generated_values.push_back(value);
        }

        m_queue.Enqueue(generated_values);
        run_counter++;
        // We stop if the value is reached
        if (m_amount_of_runs > 0 && run_counter == m_amount_of_runs)
            break;

        printf("Sleeping\n");
        Sleep(500);
    }
    printf("Generator thread terminated\n");
    m_current_state = state::Stopped;

}
