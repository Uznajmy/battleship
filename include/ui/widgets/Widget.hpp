#pragma once

#include <raylib.h>

class Widget {
protected:
    Widget* parent = nullptr;
    Vector2 size = {0, 0};

public:
    Widget();
    virtual ~Widget();

    Widget* get_parent();
    void set_parent(Widget* parent);

    Vector2 get_size() const;
    virtual void calculate_size();

    virtual void draw(Rectangle bounds) = 0;
};
