#pragma once

#include "pages/Page.hpp"
#include <vector>

class UI {
    std::vector<Page*> pages;

public:
    UI(Page* main_page = nullptr);
    ~UI();

    void push(Page* page);
    void pop();
    void draw();
};
