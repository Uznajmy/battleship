#include "ui/widgets/Widget.hpp"

Widget::Widget() {}
Widget::~Widget() {}

Widget* Widget::get_parent() {
    return parent;
}
void Widget::set_parent(Widget* parent) {
    this->parent = parent;
}

Vector2 Widget::get_size() const {
    return size;
}
void Widget::calculate_size() {
    if (parent) parent->calculate_size();
}
