#include <MainController.hpp>

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
    }

    void MainController::begin_draw() {
        engine::graphics::OpenGL::clear_buffers();
    }

    void MainController::draw() {
    }

    void MainController::end_draw() {
        auto platform = get<engine::platform::PlatformController>();
        platform->swap_buffers();
    }
}
