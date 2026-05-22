#include "ui/UI.hpp"

UI::UI(Page* main_page) {
    if (main_page != nullptr) {
        push(main_page);
    }
}
UI::~UI() {}

void UI::push(Page* page) {
    pages.push(page);
}
void UI::pop() {
    if (pages.empty()) {
        return;
    }
    delete pages.top();
    pages.pop();
}
void UI::draw() {
    if (pages.empty()) {
        return;
    }
    if (pages.top() == nullptr) {
        pages.pop();
    }
    pages.top()->draw();
}
