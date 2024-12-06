#include "./controller/app.hpp"

int main() {
    App *app = new App();
    try {
        app->run();
    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << "\n";
    } catch (...) {
        std::cerr << "Unknown exception caught\n";
    }
}