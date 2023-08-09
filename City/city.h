#pragma once
#include "../Day/day.h"
#include <vector>
#include "ftxui/component/component.hpp"

#include <memory>

class city_forecast {
public:
    explicit city_forecast(std::string city, int default_days): city(std::move(city)), default_days(default_days) {}

    void add_day(const std::string& date, float max_temperature, float min_temperature,
                 float precipitation_sum, float max_windspeed, unsigned char weather_code);

    void create_forecast(std::vector<std::shared_ptr<ftxui::Node>>& boxes, std::shared_ptr<ftxui::Node>& document);

    void default_days_increment();
    void default_days_decrement();

    void change_weekend_color() {is_red_weekend = !is_red_weekend; }

private:
    std::string city;
    int default_days;
    std::vector<day> days;
    bool is_red_weekend;
};
