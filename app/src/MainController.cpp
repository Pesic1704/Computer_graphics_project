#include <MainController.hpp>
#include <engine/graphics/GraphicsController.hpp>

namespace my_app {
    std::string_view MainController::name() const {
        return "MainController";
    }

    void MainController::initialize() {
        engine::graphics::OpenGL::enable_depth_testing();
    }

    bool MainController::loop() {
        auto platform = get<engine::platform::PlatformController>();

        if (platform->key(engine::platform::KeyId::KEY_ESCAPE).state() == engine::platform::Key::State::Pressed) {
            return false;
        }

        return true;
    }

    void MainController::poll_events() {
    }

    void MainController::update() {
        update_camera();
    }

    void MainController::begin_draw() {
        engine::graphics::OpenGL::clear_buffers();
    }

    void MainController::draw() {
        draw_reaper();
    }

    void MainController::draw_tower() {
        auto graphics = get<engine::graphics::GraphicsController>();
        auto resources = get<engine::resources::ResourcesController>();

        auto shader = resources->shader("basic");
        auto tower = resources->model("tower");

        shader->use();
        shader->set_mat4("projection", graphics->projection_matrix());
        shader->set_mat4("view", graphics->camera()->view_matrix());
        shader->set_mat4("model", glm::scale(glm::mat4(0.01f), glm::vec3(0.001f)));
        tower->draw(shader);
    }

    void MainController::draw_reaper() {
        auto graphics = get<engine::graphics::GraphicsController>();
        auto resources = get<engine::resources::ResourcesController>();

        auto shader = resources->shader("basic");
        auto reaper = resources->model("reaper");

        shader->use();
        shader->set_mat4("projection", graphics->projection_matrix());
        shader->set_mat4("view", graphics->camera()->view_matrix());
        shader->set_mat4("model", glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -2.0f)),
                                             glm::vec3(5.0f)));
        reaper->draw(shader);
    }

    void MainController::end_draw() {
        auto platform = get<engine::platform::PlatformController>();
        platform->swap_buffers();
    }

    void MainController::update_camera() {
        auto platform = get<engine::platform::PlatformController>();
        auto camera = get<engine::graphics::GraphicsController>()->camera();

        float dt = platform->dt();
        if (platform->key(engine::platform::KEY_W).state() == engine::platform::Key::State::Pressed) {
            camera->move_camera(engine::graphics::Camera::Movement::FORWARD, dt);
        }
        if (platform->key(engine::platform::KEY_S).state() == engine::platform::Key::State::Pressed) {
            camera->move_camera(engine::graphics::Camera::Movement::BACKWARD, dt);
        }
        if (platform->key(engine::platform::KEY_A).state() == engine::platform::Key::State::Pressed) {
            camera->move_camera(engine::graphics::Camera::Movement::LEFT, dt);
        }
        if (platform->key(engine::platform::KEY_D).state() == engine::platform::Key::State::Pressed) {
            camera->move_camera(engine::graphics::Camera::Movement::RIGHT, dt);
        }

        auto mouse = platform->mouse();
        camera->rotate_camera(mouse.dx, mouse.dy);
        camera->zoom(mouse.scroll);
    }
}
