//
// Created by beloin on 28/12/23.
//

#ifndef TWAMP_SETUP_LOGGER_H
#define TWAMP_SETUP_LOGGER_H

namespace Setup {

    struct logger_info_tag {
    };
    struct logger_none_tag {
    };

    void setup_logger(logger_info_tag);

    void setup_logger(logger_none_tag);

}

#endif //TWAMP_SETUP_LOGGER_H
