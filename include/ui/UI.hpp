#pragma once

#include "pages/Page.hpp"
#include <stack>

class UI {
    std::stack<Page*> pages;

public:
    UI(Page* main_page = nullptr);
    ~UI();

    void push(Page* page);
    void pop();
    void draw();
};
