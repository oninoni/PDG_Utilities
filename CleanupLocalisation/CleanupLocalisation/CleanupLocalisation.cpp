// CleanupLocalisation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int main()
{
    std::unordered_set<std::string> usedTags;

    std::vector<std::string> vanillaFiles = {
        "l_english.yml",
        "l_french.yml",
        "l_german.yml",
        "l_polish.yml",
        //"l_spanish.yml",
        "l_russian.yml"
    };

    std::vector<std::string> STNHFiles = {
        "STH_event_l_english.yml",
        "STH_tech_and_components_l_english.yml",
        "STH_text_l_english.yml"
    };

    std::regex regexer(" +(.+?):0");
    std::smatch matches;

    for (std::string fileName : STNHFiles) {
        std::cout << "Loading " << fileName << std::endl;
        std::ifstream file(fileName);
        if (!file.is_open()) {
            std::cout << "Error opening \"" << fileName << "\"!! :(" << std::endl;
            continue;
        }
        std::string line;
        while (!file.eof()) {
            std::getline(file, line);
            if (std::regex_search(line, matches, regexer, std::regex_constants::match_continuous)) {
                usedTags.insert(matches[1]);
            }
        }
        file.close();
        std::cout << "Loaded " << fileName << std::endl;
    }

    for (std::string fileName : vanillaFiles) {
        std::cout << "Loading " << fileName << std::endl;
        std::ifstream file(fileName);
        std::vector<std::string> fileData;

        if (!file.is_open()) {
            std::cout << "Error opening \"" << fileName << "\"!! :(" << std::endl;
            continue;
        }
        std::string line;
        while (!file.eof()) {
            std::getline(file, line);
            if (std::regex_search(line, matches, regexer, std::regex_constants::match_continuous)) {
                if (usedTags.find(matches[1]) == usedTags.end()) {
                    fileData.push_back(line);
                }
                else {
                    std::cout << "Ignoring " << matches[1] << std::endl;
                }
            }
            else {
                fileData.push_back(line);
            }
        }
        file.close();
        std::cout << "Loaded " << fileName << std::endl;

        std::ofstream outFile(fileName);
        for (std::string line : fileData) {
            outFile << line << std::endl;
        }
        outFile.close();
        std::cout << "Saved " << fileName << std::endl;
    }

    return 0;
}

