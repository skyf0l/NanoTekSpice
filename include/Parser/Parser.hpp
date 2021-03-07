/*
** EPITECH PROJECT, 2021
** PARSER
** File description:
** Parser header
*/

#ifndef PARSER_H_
#define PARSER_H_

#include <regex>

#include <Blueprint.hpp>
#include <Circuit.hpp>

namespace nts
{

    static inline std::string trim(std::string str)
    {
        return std::regex_replace(str, std::regex("^\\s+|\\s+$"), "");
    }

    class Parser
    {
    public:
        enum FileSection
        {
            START,
            CHIPSETS,
            LINKS,
            CIRCUIT
        };
        Parser(Blueprint &blueprint);

        void parseFile(const std::string &filePath);

        void processLine(std::string line, int n);
        void processChipsetLine(std::string line, int n);
        void processLinkLine(std::string line, int n);
        void processCircuitLine(std::string line, int n);

        static void LoadBlueprintFromFile(const std::string &filePath, Blueprint &blueprint);
        static void LoadComponentsFromFile(const std::string &filePath, std::unique_ptr<Circuit> &circuit);

        static std::string getFilename(std::string path);
        static std::string removeExtension(std::string filename);
        static std::string getFileName(std::string path);

    protected:
        std::unique_ptr<Circuit> _circuit;
        Blueprint &_blueprint;

        FileSection _currentSection;
        std::vector<std::tuple<std::string, std::string>> _inputCommands;
    };
} // namespace nts

#endif /* !PARSER_H_ */