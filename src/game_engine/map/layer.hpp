#pragma once

namespace map
{

class Layer
{
    public:
        virtual void update() = 0;
        virtual void render() = 0;

};

} // namespace map