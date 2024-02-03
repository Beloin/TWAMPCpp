//
// Created by beloin on 02/02/24.
//

#include "time_utils.h"

std::chrono::system_clock::time_point const &twamp_start_date() {
    static tm tp = std::tm{0, 0, 0, 1, 0, (1900 - 1900)};
    const static std::chrono::system_clock::time_point specific_date =
            std::chrono::system_clock::from_time_t(std::mktime(&tp));
    return specific_date;
}