#pragma once

#include "Page.hpp"

class MainPage : public Page {
public:
    MainPage();
    ~MainPage() override;

    void draw() override;
};
