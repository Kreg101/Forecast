#include <iostream>
#include <Conio.h>

#include <nlohmann/json.hpp>

#include "Forecast/Forecast.h"

using json = nlohmann::json;
std::string config_file_name = "config.json";

int main() {

    // reading json config file
    std::ifstream config(config_file_name, std::ios::binary);
    json j_config = json::parse(config);

    // creating current forecast
    Forecast forecast;
    forecast.GetForecast(j_config);

    system("cls");

    // printing forecast
    forecast.CreatePic();

    int button;

    // catching keys
    while (true) {
        if (kbhit()) {
            button = getch();
            if (button == 27) {
                return 0;
            } else if (button == 110) {
                forecast.NextCity();
                forecast.Update_Screen();
            } else if (button == 112) {
                forecast.PrevCity();
                forecast.Update_Screen();
            } else if (button == 43) {
                forecast.GetCurrentCity().default_days_increment();
                forecast.Update_Screen();
            } else if (button == 45) {
                forecast.GetCurrentCity().default_days_decrement();
                forecast.Update_Screen();
            } else if (button == 103) {
                forecast.GetCurrentCity().change_weekend_color();
                forecast.Update_Screen();
            }
        }
    }
    
}