#ifndef MAIN_CONTROLLER_HPP
#define MAIN_CONTROLLER_HPP

#include <engine/core/Engine.hpp>

namespace my_app {
    class MainController final : public engine::core::Controller {
        [[nodiscard]] std::string_view name() const override;
    };
}

#endif
