#include "Forecast.h"
#include <iostream>

std::string base_of_city_request = "https://api.api-ninjas.com/v1/city?name=";

void Forecast::GetForecast(const nlohmann::json& j_config) {
        std::vector<std::string> cities = j_config["city"];
        int default_day_forecast = j_config["day"];

        std::vector<std::pair<std::string, std::pair<double, double>>> coordinates;
        for (auto& c: cities) {
            cpr::Response r = cpr::Get(cpr::Url{base_of_city_request + c},
                                       cpr::Header{{"X-Api-Key", "JXlsqUjnUc0BSl2Z9NwWyA==Tnlr4VRlj20LYlYZ"}});
            json help = json::parse(r.text);
            if (r.text != "[]") {
                coordinates.emplace_back();
                coordinates.back().first = c;
                coordinates.back().second.first = double((int)((double)(help.front()["latitude"]) * 100)) / 100;
                coordinates.back().second.second = double((int)((double)(help.front()["longitude"]) * 100)) / 100;
            }
        }


        for (auto& city: coordinates) {
            city_forecast current_forecast(city.first, default_day_forecast);
            cpr::Response r = cpr::Get(cpr::Url{"https://api.open-meteo.com/v1/forecast?latitude=" + std::to_string(city.second.first)
                                                + "&longitude=" + std::to_string(city.second.second) + "&timezone=Europe/Moscow&daily=weathercode"
                                                + "&daily=temperature_2m_max&daily=temperature_2m_min&daily=precipitation_sum&daily=windspeed_10m_max&forecast_days=14"});
            json j = json::parse(r.text);
            int count = 0;
            for (auto& x: j["daily"]["time"]) {
                current_forecast.add_day(x, j["daily"]["temperature_2m_max"][count], j["daily"]["temperature_2m_min"][count],
                                         j["daily"]["precipitation_sum"][count], j["daily"]["windspeed_10m_max"][count],
                                         j["daily"]["weathercode"][count]);
                count++;
            }
            city_forecasts.emplace_back(current_forecast);
        }

}

void Forecast::CreatePic() {
    city_forecasts[current_city].create_forecast(boxes, document);
    screen = ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Fit(document));
    Render(screen, document);
    screen.Print();
}

void Forecast::NextCity() {
    current_city = (++current_city)%city_forecasts.size();
};

void Forecast::PrevCity() {
    if (current_city) {
        --current_city;
    } else {
        current_city = city_forecasts.size() - 1;
    }
}

void Forecast::Update_Screen() {
    screen.Clear();
    system("cls");
    boxes.clear();
    city_forecasts[current_city].create_forecast(boxes, document);
    screen = ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Fit(document));
    Render(screen, document);
    screen.Print();
}
