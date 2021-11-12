#include "data-processor.h"
//#include <numeric>        // For std::reduce

#ifdef _WIN32
#include <Windows.h>            // for Sleep function
#else
#include <unistd.h>
#endif


void DataProcessor::data_processor() const {
    uint32_t num_processed_data = 0;
    while (m_current_state == state::Started) {
        int64_t sum = 0;
        int32_t amount_of_values = 0;
        std::vector<int32_t> processingData;

        if (m_source_data_queue.IsEmpty() == true) {
            Sleep(500);
            continue;
        }

        const auto result = m_source_data_queue.Dequeue(processingData);
        if (result == false || processingData.empty() == true) {
            Sleep(500);
            continue;
        }

        for (auto it = processingData.begin(); it != processingData.end(); ++it) {
            sum += *it;
            amount_of_values++;
        }
        const auto mean_vale = sum / amount_of_values;

        // retrieves the results first method is only available in C++17.
        //const auto modern_result = std::reduce(processingData.begin(), processingData.end()) / processingData.size();
        //printf("Iteration:%u Mean value:%lld Second method:%lld\n", num_processed_data, old_result, modern_result);

        printf("Processor[%u] - Mean= %lld \n", num_processed_data, mean_vale);
        m_destination_queue.Enqueue(mean_vale);
        num_processed_data++;
    }
    printf("Data processor thread terminated\n");
}
