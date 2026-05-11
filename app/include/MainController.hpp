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

        void set_light();

        void draw_floor();

        void draw_tower();

        void draw_tree();

        void draw_reaper();

        void draw_torch();

        void end_draw() override;

        void update_camera();

        bool m_cursor_enabled{true};
    };
}

#endif
