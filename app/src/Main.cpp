#include <Main.hpp>
#include <MainController.hpp>

#include "spdlog/spdlog.h"

namespace my_app {
    void Main::app_setup() {
        spdlog::info("App setup");
        auto main_controller = register_controller<MainController>();
        main_controller->after(engine::core::Controller::get<engine::core::EngineControllersEnd>());
    }
}

int main(int argc, char **argv) {
    auto app = std::make_unique<my_app::Main>();
    return app->run(argc, argv);
}
