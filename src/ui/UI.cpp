#include "ui/UI.hpp"

UI::UI(Page* main_page) {
    if (main_page != nullptr) {
        push(main_page);
    }
}
UI::~UI() {}

void UI::push(Page* page) {
    pages.push_back(page);
}
void UI::pop() {
    if (pages.empty()) {
        return;
    }
    delete pages.back();
}
void UI::draw() {
    if (pages.empty()) {
        return;
    }
    while (pages.back() == nullptr) {
        pages.pop_back();
    }
    pages.back()->draw();
}
