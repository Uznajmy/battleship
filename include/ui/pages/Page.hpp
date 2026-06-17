#pragma once

class Page {
protected:
    Page() = default;

public:
    virtual ~Page() = default;

    virtual void draw() = 0;
};
