#pragma once

#include "Widget.hpp"
#include <string>
#include <raylib.h>

class Label: public Widget {
    std::string text = "";

public:
    Label();
    Label(const std::string& text);
    ~Label() override;

    void calculate_size() override;

    const std::string& get_text();
    void set_text(const std::string& new_text);

    void draw(Rectangle bounds) override;
};
