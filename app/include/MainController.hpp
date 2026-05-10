#ifndef MAIN_CONTROLLER_HPP
#define MAIN_CONTROLLER_HPP

#include <engine/core/Engine.hpp>

namespace my_app {
    class MainController final : public engine::core::Controller {
    public:
        [[nodiscard]] std::string_view name() const override;

    private:
        void initialize() override;

        bool loop() override;

        void poll_events() override;

        void update() override;

        void begin_draw() override;

        void draw() override;

        void end_draw() override;

        void update_camera();
    };
}

#endif
