// JSON2YML.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

void setCursorVisible(bool visible)
{
    CONSOLE_CURSOR_INFO cursorinfo;
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleCursorInfo(handle, &cursorinfo);
    if (!cursorinfo.bVisible == visible)
    {
        cursorinfo.bVisible = visible;
        SetConsoleCursorInfo(handle, &cursorinfo);
    }
}

int main()
{
    setCursorVisible(false);          

    std::regex translationExp("\"[^(]+\\(([^)]+)\\)\" *: *\"( *[^:]+:0 *[^]*)\"");
    std::regex escapeExp("\\\\([^])");
    std::regex languageExp("<lang>");

    std::smatch matches;

    std::vector<std::pair<std::string, std::string>> filenames = {
        { "ST New Horizons - Main Localisation.json", "localisation\\<lang>\\STH_main_l_<lang>.yml" },
        { "ST New Horizons - Events Localisation.json", "localisation\\<lang>\\STH_events_l_<lang>.yml" },
        { "ST New Horizons - Tech Localisation.json", "localisation\\<lang>\\STH_tech_l_<lang>.yml" },
		{ "ST New Horizons - Synced Localisation.json", "localisation_synced\\STH_synced_l_<lang>.yml" }
    };
	std::cout << "#############################################" << std::endl;
	std::cout << "### Starting SWGD Localisation Creator... ###" << std::endl;
	std::cout << "#############################################" << std::endl;
    for (auto filename : filenames)
    {                     
        std::ifstream inputfile("Input\\" + filename.first);

        if (!inputfile.is_open())
        {
            std::cout << "Could not find file!" << std::endl;
            return 0;
        }

        inputfile.seekg(0, std::ios::end);
        int64_t size = inputfile.tellg();
        inputfile.seekg(0, std::ios::beg);
        int64_t modvalue = size / 100;
        int64_t counter = 0;
        std::unordered_map<std::string, std::vector<std::string>> translations;        
        while (!inputfile.eof())
        {
            while (counter <= 0)
            {
                std::cout << "\rLoading: " << inputfile.tellg() * 100 / size << "%";
                counter += modvalue;
            }
            std::string line;
            std::getline(inputfile, line);
            counter -= line.size();

            if (std::regex_search(line, matches, translationExp))
            {
                std::string text = std::regex_replace(matches[2].str(), escapeExp, "$1");
                translations[matches[1]].push_back(text);
            }
        }
        std::cout << "\rLoading: 100%" << std::endl;
        inputfile.close();

        std::cout << "Writing..." << std::endl;

        for (auto entry : translations)
        {
            std::string language = entry.first;
            const std::vector<std::string>& lines = entry.second;

            std::cout << language << std::endl;

            std::transform(language.begin(), language.end(), language.begin(), tolower);
            std::string name = std::regex_replace(filename.second, languageExp, language);

            if (lines.size() > 0) {
                std::ofstream output("Output\\" + name);

                if (!output.is_open()) {
                    std::cout << "Could not write to file " << name << std::endl;
                    continue;
                }

                int64_t bom = '¿»ï';
                output.write((char*)&bom, 3);
                output << "################\\" << std::endl;
                output << "# " << language << " translation" << std::endl;
                output << "##################\\" << std::endl;
                output << std::endl;
                output << "l_" << language << ":" << std::endl;

                for (const std::string& line : lines) {
                    output << line << std::endl;
                }

                output.close();
            }

        }
    }

    return 0;
}

