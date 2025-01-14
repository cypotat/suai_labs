#include "Settings.h"
#include <ostream>
#include <fstream>
#include "bipbop.hpp"
using namespace std;
using json = nlohmann::json;

void Settings::add(const std::string& name, int value) {
    IntData.add(name, value);
}

void Settings::add(const std::string& name, const std::string& value) {
    StrData.add(name, value);
}

void Settings::erase_int(const std::string& name) {
    IntData.erase(name);
};

void Settings::erase_str(const std::string& name) {
    StrData.erase(name);
}

int Settings::find_int(const std::string& name) {
    return IntData.find(name);
}

std::string Settings::find_str(const std::string& name) {
    return StrData.find(name);
}

void Settings::load(const std::string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        size_t stage = 0;
        while (std::getline(file, line)) {
            if (line == "===") {
                stage++;
                continue;
            }

            std::string key;
            size_t i;
            for (i = 0; i < line.size(); i++)
            {
                if (line[i] == '=') break;
                key.push_back(line[i]);
            }
            i++;
            std::string value;
            for (; i < line.size(); i++)
                value.push_back(line[i]);
            switch (stage)
            {
            case 0:
                IntData.add(key, std::stoi(value));
                break;
            case 1:
                StrData.add(key, value);
                break;
            default:
                break;
            }
        }
        file.close();
    }
}

void Settings::save(const std::string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        file << IntData;
        file << "===" << "\n";
        file << StrData;

        file.close();
    }

}

void Settings::read_bmp(const std::string& filename) {
    FILE* input = fopen(filename.c_str(), "rb");

    BitMapFileHeader file;
    file.Type = get(input, sizeof(file.Type));
    file.Size = get(input, sizeof(file.Size));
    file.Reserved1 = get(input, sizeof(file.Reserved1));
    file.Reserved2 = get(input, sizeof(file.Reserved2));
    file.OffsetBits = get(input, sizeof(file.OffsetBits));

    BitMapInfoHeader image;
    image.Size = get(input, sizeof(image.Size));
    image.Width = get(input, sizeof(image.Width));
    image.Height = get(input, sizeof(image.Height));
    image.Planes = get(input, sizeof(image.Planes));
    image.BitCount = get(input, sizeof(image.BitCount));
    image.Compression = get(input, sizeof(image.Compression));
    image.SizeImage = get(input, sizeof(image.SizeImage));
    image.XpelsPerMeter = get(input, sizeof(image.XpelsPerMeter));
    image.YpelsPerMeter = get(input, sizeof(image.YpelsPerMeter));
    image.ColorsUsed = get(input, sizeof(image.ColorsUsed));
    image.ColorsImportant = get(input, sizeof(image.ColorsImportant));

    json j;
    j["file"] = file;
    j["image"] = image;
    for (auto& el : j["file"].items())
        IntData.add(el.key(), el.value());

    for (auto& el : j["image"].items())
        IntData.add(el.key(), el.value());

    // cout << setw(4) << j << endl;
    fclose(input);
}


ostream& operator<<(ostream& os, const Settings& sets) {
    os << "Str - Int\n";
    os << sets.IntData << "\n\nStr - Str\n";
    os << sets.StrData;

    return os;
}