//
// Created by beloin on 28/12/23.
//

#include "setup_logger.h"
#include "spdlog/spdlog.h"

using namespace Setup;

void Setup::setup_logger(logger_info_tag) {
#ifdef SPDLOG_DEBUG_ON
    spdlog::set_level(spdlog::level::debug);
#endif
    spdlog::info("spdlog version {}.{}.{} and level {}", SPDLOG_VER_MAJOR, SPDLOG_VER_MINOR,
                 SPDLOG_VER_PATCH, to_string_view(spdlog::get_level()));
}

void Setup::setup_logger(logger_none_tag) {
#ifdef SPDLOG_DEBUG_ON
    spdlog::set_level(spdlog::level::debug);
#endif
}