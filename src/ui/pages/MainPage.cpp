#include "ui/pages/MainPage.hpp"
#include "ui/widgets/Label.hpp"
#include <raylib.h>
#include <raygui.h>

MainPage::MainPage() {
    grid.set_widget({0, 0}, new Label("Main Page"));
}

MainPage::~MainPage() {

}

void MainPage::draw() {
    grid.draw({0, 0, 800, 600});
}
