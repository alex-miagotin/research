#pragma once

#include <vector>

#include "../core/physics/vector2D.hpp"

#include "layer.hpp"

namespace map
{
    
class GameMap
{

public:
    void render() {
        for (auto layer : m_layers) {
            layer->render();
        }
    }

    void update() {
        for (auto layer : m_layers) {
            layer->update();
        }
    }

    std::vector<Layer*>& getLayers() {
        return m_layers;
    }

    void addLayer(Layer* layer) {
        m_layers.push_back(layer);
    }
    
private:
    std::vector<Layer*> m_layers;

};

} // namespace map
