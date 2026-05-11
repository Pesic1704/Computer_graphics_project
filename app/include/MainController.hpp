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

        void update_camera();

        void update_torch();

        void update_reaper();

        void begin_draw() override;

        void draw() override;

        void set_light();

        void draw_floor();

        void draw_tower();

        void draw_tree();

        void draw_reaper();

        void draw_torch();

        void end_draw() override;

        bool m_cursor_enabled = true;

        bool torch_enabled = true;
        glm::vec3 torch_light;

        bool reaper_orbiting = false;
        float reaper_angle = 0.0f;
        glm::vec3 reaper_position = glm::vec3(2.5f, -4.9f, -18.5f);
    };
}

#endif
