#include <raylib.h>
#include <raygui.h>
#include "ui/pages/MainPage.hpp"

MainPage::MainPage() {

}

MainPage::~MainPage() {

}

void MainPage::draw() {
    DrawText("Main Page", 16, 16, 20, WHITE);
}
