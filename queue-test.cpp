// QueueTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <ctime>
#include "include/number-generator.h"
#include "include/data-aggregator.h"
#include "include/data-processor.h"

int main() {
    constexpr auto queue_capacity = 5;

    // initializes the srand with a time based seed
    srand((unsigned)time(NULL));

    GenericQueue <std::vector<int32_t>> generated_values_queue(queue_capacity);
    GenericQueue <int32_t> processed_values_queue(queue_capacity);

    const auto generator = new NumberGenerator(generated_values_queue, 10);
    const auto processor = new DataProcessor(generated_values_queue,processed_values_queue);
    const auto aggregator = new DataAggregator(processed_values_queue);

    // Start the threads
    generator->Start();
    
    //stops the terminal
    getchar();
    delete processor;
    delete aggregator;
}
