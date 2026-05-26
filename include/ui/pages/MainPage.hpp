#pragma once

#include "Page.hpp"
#include "ui/widgets/Grid.hpp"

class MainPage : public Page {
    Grid grid;

public:
    MainPage();
    ~MainPage() override;

    void draw() override;
};
