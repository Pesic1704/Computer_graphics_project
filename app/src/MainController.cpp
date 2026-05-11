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
        const auto platform = engine::core::Controller::get<engine::platform::PlatformController>();

        if (platform->key(engine::platform::KEY_F1).state() == engine::platform::Key::State::JustPressed) {
            m_cursor_enabled = !m_cursor_enabled;
            platform->set_enable_cursor(m_cursor_enabled);
        }

        if (platform->key(engine::platform::KEY_X).state() == engine::platform::Key::State::JustPressed) {
            torchEnabled = !torchEnabled;
        }
    }

    void MainController::update() {
        update_camera();
    }

    void MainController::begin_draw() {
        engine::graphics::OpenGL::clear_buffers();
    }

    void MainController::draw() {
        set_light();
        draw_floor();
        draw_tower();
        draw_tree();
        draw_reaper();
        draw_torch();
    }

    void MainController::set_light() {
        glm::vec3 dir_light_direction = glm::vec3(-0.3f, -1.0f, -0.2f);
        glm::vec3 dir_light_color = glm::vec3(0.2f, 0.2f, 0.35f);
        glm::vec3 point_light_position = glm::vec3(-1.1f, -4.1f, -18.625f);
        glm::vec3 point_light_color = torchEnabled
                                          ? glm::vec3(1.0f, 0.6f, 0.2f)
                                          : glm::vec3(0.0f);

        auto resources = get<engine::resources::ResourcesController>();
        auto shader = resources->shader("basic");

        shader->use();
        shader->set_vec3("dirLightDirection", dir_light_direction);
        shader->set_vec3("dirLightColor", dir_light_color);
        shader->set_vec3("pointLightPosition", point_light_position);
        shader->set_vec3("pointLightColor", point_light_color);
    }

    void MainController::draw_floor() {
        auto graphics = get<engine::graphics::GraphicsController>();
        auto resources = get<engine::resources::ResourcesController>();

        auto shader = resources->shader("basic");
        auto floor = resources->model("floor");

        auto model_floor =
                glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -5.0f, -20.0f)) *
                glm::rotate(glm::mat4(1.0f), glm::radians(75.0f), glm::vec3(0.0f, 1.0f, 0.0f)) *
                glm::scale(glm::mat4(1.0f), glm::vec3(70.0f, 1.0f, 70.0f));

        shader->use();
        shader->set_mat4("projection", graphics->projection_matrix());
        shader->set_mat4("view", graphics->camera()->view_matrix());
        shader->set_mat4("model", model_floor);
        floor->draw(shader);
    }

    void MainController::draw_tower() {
        auto graphics = get<engine::graphics::GraphicsController>();
        auto resources = get<engine::resources::ResourcesController>();

        auto shader = resources->shader("basic");
        auto tower = resources->model("tower");

        auto model_tower =
                glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -2.7f, -20.0f)) *
                glm::rotate(glm::mat4(1.0f), glm::radians(175.0f), glm::vec3(0.0f, 1.0f, 0.0f)) *
                glm::scale(glm::mat4(1.0f), glm::vec3(0.001f));

        shader->use();
        shader->set_mat4("projection", graphics->projection_matrix());
        shader->set_mat4("view", graphics->camera()->view_matrix());
        shader->set_mat4("model", model_tower);
        tower->draw(shader);
    }

    void MainController::draw_tree() {
        auto graphics = get<engine::graphics::GraphicsController>();
        auto resources = get<engine::resources::ResourcesController>();

        auto shader = resources->shader("basic");
        auto tree = resources->model("tree");

        auto model_tree =
                glm::translate(glm::mat4(1.0f), glm::vec3(-5.0f, -3.9f, -18.0f)) *
                glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f)) *
                glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));

        shader->use();
        shader->set_mat4("projection", graphics->projection_matrix());
        shader->set_mat4("view", graphics->camera()->view_matrix());
        shader->set_mat4("model", model_tree);
        tree->draw(shader);
    }

    void MainController::draw_reaper() {
        auto graphics = get<engine::graphics::GraphicsController>();
        auto resources = get<engine::resources::ResourcesController>();

        auto shader = resources->shader("basic");
        auto reaper = resources->model("reaper");

        auto model_reaper =
                glm::translate(glm::mat4(1.0f), glm::vec3(2.5f, -4.9f, -18.5f)) *
                glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f)) *
                glm::scale(glm::mat4(1.0f), glm::vec3(20.0f));

        shader->use();
        shader->set_mat4("projection", graphics->projection_matrix());
        shader->set_mat4("view", graphics->camera()->view_matrix());
        shader->set_mat4("model", model_reaper);
        reaper->draw(shader);
    }

    void MainController::draw_torch() {
        auto graphics = get<engine::graphics::GraphicsController>();
        auto resources = get<engine::resources::ResourcesController>();

        auto shader = resources->shader("basic");
        auto torch = resources->model("torch");

        auto model_torch =
                glm::translate(glm::mat4(1.0f), glm::vec3(-1.1f, -4.1f, -18.625f)) *
                glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f)) *
                glm::scale(glm::mat4(1.0f), glm::vec3(0.4f));

        shader->use();
        shader->set_mat4("projection", graphics->projection_matrix());
        shader->set_mat4("view", graphics->camera()->view_matrix());
        shader->set_mat4("model", model_torch);
        torch->draw(shader);
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
