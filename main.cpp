#include <string>
#include <cstring>
#include <list>
#include <iostream>

class Station {
public:
    std::string name;
    int year;

    Station(const std::string& stationName, int yearAdd)
        : name(stationName), year(yearAdd) {}
};

void stationsPrint(const std::list<Station>& stations, int year) {
    std::cout << "==========================================\n";
    std::cout << "Stations in " << year << ":\n";
    std::cout << "------------------------------------------\n";
    for (const auto& station : stations) {
        if (station.year <= year) {
            std::cout << station.name << "\n";
        }
    }
}

int main() {
    std::list<Station> stations = {
        {"Shibuya",      1970},
        {"Ebisu",        1970}, 
        {"Meguro",       1970}, 
        {"Gotanda",      1970},
        {"Osaki",        1970},
        {"Shinagawa",    1970},
        {"Tamachi",      1970},
        {"Shinbashi",    1970},
        {"Yurakucho",    1970}, 
        {"Tokyo",        1970}, 
        {"Kanda",        1970},
        {"Akihabara",    1970},
        {"Okachimachi",  1970},
        {"Ueno",         1970},
        {"Uguisudani",   1970},
        {"Nippori",      1970},
        {"Tabata",       1970},
        {"Komagome",     1970},
        {"Sugamo",       1970},
        {"Otsuka",       1970},
        {"Ikebukuro",    1970},
        {"Mejiro",       1970}, 
        {"Takadanobaba", 1970},
        {"Shin-Okubo",   1970},
        {"Shinjuku",     1970}, 
        {"Yoyogi",       1970},
        {"Harajuku",     1970}
    };

    // 西日暮里駅
    auto it = std::find_if(stations.begin(), stations.end(),
        [](const Station& s) { return s.name == "Nippori"; });
    stations.insert(std::next(it), Station("Nishi-Nippori",     1971));

    // 高輪ゲートウェイ駅
    it = std::find_if(stations.begin(), stations.end(),
        [](const Station& s) { return s.name == "Tamachi"; });
    stations.insert(std::next(it), Station("Takanawa Gateway",  2020));

    // 1970年の駅リストを出力
    stationsPrint(stations, 1970);
    // 2019年の駅リストを出力
    stationsPrint(stations, 2019);
    // 2022年の駅リストを出力
    stationsPrint(stations, 2022);

    return 0;
}