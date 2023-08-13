#pragma once
#include "../City/city.h"
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

#include "ftxui/component/captured_mouse.hpp"  // for ftxui
#include "ftxui/component/component.hpp"       // for Slider, Renderer, Vertical
#include "ftxui/component/component_base.hpp"  // for ComponentBase
#include "ftxui/dom/elements.hpp"  // for Elements, Element, operator|, separator, text, focusPositionRelative, size, border, flex, frame, bgcolor, gridbox, vbox, EQUAL, center, HEIGHT, WIDTH
#include "ftxui/screen/color.hpp"

class Forecast {
public:

    using json = nlohmann::json;

    Forecast(): current_city(0), screen(2, 2) {}

    void GetForecast(const nlohmann::json& j_config);

    void CreatePic();

    void NextCity();

    void PrevCity();

    city_forecast& GetCurrentCity() {return city_forecasts[current_city];}

    void Update_Screen();

private:
    std::vector<city_forecast> city_forecasts;
    int current_city;
    std::vector<std::shared_ptr<ftxui::Node>> boxes;
    std::shared_ptr<ftxui::Node> document;
    ftxui::Screen screen;
};

