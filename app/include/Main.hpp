#ifndef MAIN_HPP
#define MAIN_HPP

#include <engine/core/Engine.hpp>

namespace my_app {
    class Main final : public engine::core::App {
        void app_setup() override;
    };
}

#endif
