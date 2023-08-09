#include "city.h"
#include <sstream>
#include <iomanip>

void city_forecast::add_day(const std::string& date, float max_temperature, float min_temperature,
             float precipitation_sum, float max_windspeed, unsigned char weather_code) {
    days.emplace_back(date, max_temperature, min_temperature, precipitation_sum, max_windspeed, weather_code);
}

std::string GetWeatherFromCode(unsigned char weather_code) {
    switch (weather_code) {
        case 0:
            return "Ясная погода";
        case 1:
            return "Преимущественно ясно";
        case 2:
            return "Переменная облачность";
        case 3:
            return "Пасмурно";
        case 45:
            return "Туман";
        case 48:
            return "Свергающий иней туман";
        case 51:
            return "Легкая морось";
        case 53:
            return "Умеренная морось";
        case 55:
            return "Сильная морось";
        case 56:
            return "Легкий моросящий дождик";
        case 57:
            return "Хорошо моросящий дождь";
        case 61:
            return "Небольшой дождь";
        case 63:
            return "Дождь";
        case 65:
            return "Сильный дождь";
        case 66:
            return "Легкий ледяной дождь";
        case 67:
            return "Сильный ледяной дождь";
        case 71:
            return "Небольшой снегопад";
        case 73:
            return "Умеренный снегопад";
        case 75:
            return "Сильный снегопад";
        case 77:
            return "Снежные зерна";
        case 80:
            return "Небольшой дождь";
        case 81:
            return "Дождь";
        case 82:
            return "Ливень";
        case 85:
            return "Небольшой снегопад";
        case 86:
            return "Сильный снегопад";
        case 95:
            return "Гроза";
        case 96:
            return "Гроза с небольшим градом";
        case 97:
            return "Гроза с сильным градом";
        default:
            return "Что-то случилось с источником информации...";
    }
}

void city_forecast::create_forecast(std::vector<std::shared_ptr<ftxui::Node>>& boxes, std::shared_ptr<ftxui::Node>& document) {
    time_t t;
    time(&t);
    std::vector<std::string> months = {"Январь", "Февраль", "Март", "Апрель", "Май", "Июнь", "Июль", "Август",
                                       "Сентябрь", "Октябрь", "Ноябрь", "Декабрь"};
    std::vector<std::string> week_days = { "Воскресенье", "Понедельник", "Вторник", "Среда", "Четверг", "Пятница", "Суббота"};
    int weeks_day = localtime(&t)->tm_wday;
    int months_day = localtime(&t)->tm_mday;
    int current_month = localtime(&t)->tm_mon;
    for (int i = 0; i < default_days; ++i) {
        std::stringstream stream_max_t, stream_min_t, stream_pr, stream_ws;
        stream_max_t << std::fixed << std::setprecision(1) << days[i].get_max_temperature();
        stream_min_t << std::fixed << std::setprecision(1) << days[i].get_min_temperature();
        stream_pr << std::fixed << std::setprecision(1) << days[i].get_precipitation();
        stream_ws << std::fixed << std::setprecision(1) << days[i].get_windspeed();
        std::string date = ' ' + week_days[weeks_day] + ", " + months[current_month] + ' ' + std::to_string(months_day) + ' ';
        weeks_day = (weeks_day + 1) % 7;
        if (months_day == 30 && (current_month == 1 || current_month == 3 || current_month == 5
        || current_month == 8 || current_month == 10)) {
            months_day = 1;
        } else if (months_day == 31 && (current_month == 0 || current_month == 2 || current_month == 4
        || current_month == 6 || current_month == 7 || current_month == 9 || current_month == 11)) {
            months_day = 1;
        } else {
            ++months_day;
        }
        if (is_red_weekend && (weeks_day == 0 || weeks_day == 1)) {
            boxes.emplace_back(ftxui::vbox({
                ftxui::text(date) | ftxui::color(ftxui::Color::Red),
                ftxui::separator(),
                ftxui::text(' ' + GetWeatherFromCode(days[i].get_weather_code()) + ' '),
                ftxui::text(' ' +stream_max_t.str()
                + '(' + stream_min_t.str() + ')' + " °C "),
                ftxui::text(' ' + stream_pr.str() + " mm "),
                ftxui::text(' ' + stream_ws.str() + " km/h ")
            }) | ftxui::border);
        } else {
            boxes.emplace_back(ftxui::vbox({
                ftxui::text(date) | ftxui::color(ftxui::Color::Aquamarine3),
                ftxui::separator(),
                ftxui::text(' ' + GetWeatherFromCode(days[i].get_weather_code()) + ' '),
                ftxui::text(' ' +stream_max_t.str()
                + '(' + stream_min_t.str() + ')' + " °C "),
                ftxui::text(' ' + stream_pr.str() + " mm "),
                ftxui::text(' ' + stream_ws.str() + " km/h ")
            }) | ftxui::border);
        }
    }
    auto help = hbox((ftxui::hflow({boxes})));
    document = ftxui::vbox({ftxui::text("Прогноз погоды: " + city) | ftxui::hcenter, help});
}

void city_forecast::default_days_increment() {
    if (default_days < 14) {
        ++default_days;
    }
}

void city_forecast::default_days_decrement() {
    if (default_days > 1) {
        --default_days;
    }
}
