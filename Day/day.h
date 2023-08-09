#pragma once
#include <string>

class day {
public:
    day() = default;
    day(std::string  date, float max_temperature, float min_temperature,
        float precipitation_sum, float max_windspeed, unsigned char weather_code):
        date(std::move(date)), max_temperature(max_temperature),
        min_temperature(min_temperature), precipitation_sum(std::max((float)0, precipitation_sum)),
        max_windspeed(std::max(float(0), max_windspeed)), weather_code(weather_code) {
    }


    //std::string get_date() {return date;}
    [[nodiscard]] float get_max_temperature() const {return max_temperature;}
    [[nodiscard]] float get_min_temperature() const {return min_temperature;}
    [[nodiscard]] double get_precipitation() const {return precipitation_sum;}
    [[nodiscard]] double get_windspeed() const {return max_windspeed;}
    [[nodiscard]] unsigned char get_weather_code() const {return weather_code;}

private:
    std::string date;
    unsigned char weather_code;
    float max_temperature;
    float min_temperature;
    float precipitation_sum;
    float max_windspeed;
};


