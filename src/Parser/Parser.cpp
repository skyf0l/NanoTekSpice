/*
** EPITECH PROJECT, 2021
** PARSER
** File description:
** Parser class
*/

#include <fstream>
#include <sstream>
#include <sys/stat.h>

#include <Parser.hpp>
#include <Circuit.hpp>
#include <NtsException.hpp>

#define LINE_DATA(line, n) ("(line " + std::to_string(n) + ": \"" + line + "\")")

namespace nts
{
    void Parser::LoadComponentsFromFile(const std::string &filePath, std::unique_ptr<Circuit> &circuit)
    {
        Blueprint blueprint;

        LoadBlueprintFromFile(filePath, blueprint);
        blueprint.loadBlueprint(circuit);
    }

    void Parser::LoadBlueprintFromFile(const std::string &filePath, Blueprint &blueprint)
    {
        Parser parser(blueprint);
        parser.parseFile(filePath);
    }

    Parser::Parser(Blueprint &blueprint) : _blueprint(blueprint)
    {
        _circuit = std::make_unique<Circuit>("blueprint", "circuit");
        _currentSection = START;
    }

    void Parser::processChipsetLine(std::string line, int n)
    {
        std::smatch matches;
        if (std::regex_search(line, matches, std::regex("^(\\S+)\\s+(\\S+)\\s*\\(\\s*(\\S+)\\s*\\)$")))
        {
            std::string type = matches[1].str();
            std::string name = matches[2].str();
            std::string value = matches[3].str();
            _circuit->addComponent(name, type);
            _inputCommands.push_back(std::tuple<std::string, std::string>(name, value));
            _blueprint.chipsets.push_back(std::make_tuple<>(name, type));
            _blueprint.values.push_back(std::make_tuple<>(name, value));
        }
        else if (std::regex_search(line, matches, std::regex("^(\\S+)\\s+(\\S+)$")))
        {
            std::string type = matches[1].str();
            std::string name = matches[2].str();
            _circuit->addComponent(name, type);
            _blueprint.chipsets.push_back(std::make_tuple<>(name, type));
        }
        else
            throw InvalidLineException("Invalid line in chipsets section " + LINE_DATA(line, n));
    }

    void Parser::processLinkLine(std::string line, int n)
    {
        std::smatch matches;
        if (std::regex_search(line, matches, std::regex("^(\\S+)\\s*:\\s*(\\d+)\\s+(\\S+)\\s*:\\s*(\\d+)$")))
        {
            std::string name1 = matches[1].str();
            std::string name2 = matches[3].str();
            int pin1;
            int pin2;
            try
            {
                pin1 = std::stoi(matches[2].str());
                pin2 = std::stoi(matches[4].str());
            }
            catch (std::exception &)
            {
                throw InvalidLineException("Invalid pin in links section " + LINE_DATA(line, n));
            }
            _circuit->addLink(name1, pin1, name2, pin2);
            _blueprint.links.push_back(std::make_tuple<>(name1, pin1, name2, pin2));
        }
        else
            throw InvalidLineException("Invalid line in link section " + LINE_DATA(line, n));
    }

    void Parser::processCircuitLine(std::string line, int n)
    {
        std::smatch matches;
        if (std::regex_search(line, matches, std::regex("^(\\S+)\\s+(\\d+)$")))
        {
            std::string name = matches[1].str();
            int pin;
            try
            {
                pin = std::stoi(matches[2].str());
            }
            catch (std::exception &)
            {
                throw InvalidLineException("Invalid pin in circuit section " + LINE_DATA(line, n));
            }

            if (!_circuit->isComponent())
                return;

            std::unique_ptr<nts::IComponent> &ioComponent = _circuit->getComponent(name);
            if (ioComponent->getType() == "input")
            {
                _circuit->getPins()[pin] = std::unique_ptr<nts::Pin>(new Pin(nts::PIN_INPUT));
                _circuit->getPins()[pin]->connect(ioComponent, 1);
            }
            else if (ioComponent->getType() == "output")
            {
                _circuit->getPins()[pin] = std::unique_ptr<nts::Pin>(new Pin(nts::PIN_OUTPUT));
                ioComponent->getPins()[1]->connect(_circuit.get(), pin);
            }
            else
                throw InvalidCircuitIOComponentException("\"" + ioComponent->getName() + "\" (" + ioComponent->getType() + ") can not be an input or an output of a component");
            _blueprint.circuits.push_back(std::make_tuple<>(name, pin));
        }
        else
            throw InvalidLineException("Invalid line in circuit section " + LINE_DATA(line, n));
    }

    void Parser::processLine(std::string line, int n)
    {
        std::smatch matches;
        if (std::regex_search(line, matches, std::regex("^\\.(\\w+)\\s*:$")))
        {
            std::string sectionName = matches[1].str();
            if (sectionName == "chipsets")
            {
                if (_currentSection == START)
                    _currentSection = CHIPSETS;
                else
                    throw InvalidSectionException("Chipsets section must be the first section " + LINE_DATA(line, n));
            }
            else if (sectionName == "links")
            {
                if (_currentSection == CHIPSETS)
                    _currentSection = LINKS;
                else
                    throw InvalidSectionException("Link section must be after the chipsets section " + LINE_DATA(line, n));
            }
            else if (sectionName == "circuit")
            {
                if (_currentSection == LINKS)
                    _currentSection = CIRCUIT;
                else
                    throw InvalidSectionException("Circuit section must be the link section " + LINE_DATA(line, n));
            }
            else
                throw UnknownSectionException("Unknown section: " + sectionName + " " + LINE_DATA(line, n));
        }
        else
        {
            if (_currentSection == START)
                throw InvalidLineException("Nothing is expected before chipsets section " + LINE_DATA(line, n));
            else if (_currentSection == CHIPSETS)
                processChipsetLine(line, n);
            else if (_currentSection == LINKS)
                processLinkLine(line, n);
            else if (_currentSection == CIRCUIT)
                processCircuitLine(line, n);
        }
    }

    static std::string removeComment(std::string line)
    {
        return std::regex_replace(line, std::regex("#.*"), "");
    }

    void Parser::parseFile(const std::string &filePath)
    {
        std::ifstream ifs(filePath, std::ifstream::binary);
        if (!ifs)
            throw InvalidFileException("File \"" + filePath + "\" does not exist or is not readable");

        std::string line;
        int n = 1;
        while (std::getline(ifs, line))
        {
            line = trim(line);
            line = removeComment(line);
            if (!line.empty())
                processLine(line, n);
            n++;
        }
        ifs.close();
        if (_currentSection == START || _currentSection == CHIPSETS)
            throw MissingSectionException("Link section is missing");
        for (auto it = _inputCommands.begin(); it != _inputCommands.end(); it++)
            _circuit->setInput(std::get<0>(*it), std::get<1>(*it));
        _inputCommands.clear();
    }

    std::string Parser::getFilename(std::string path)
    {
        std::replace(path.begin(), path.end(), '\\', '/');

        size_t lastSlash = path.find_last_of("/");
        if (lastSlash == std::string::npos)
            return path;
        return path.substr(lastSlash + 1);
    }

    std::string Parser::removeExtension(std::string filename)
    {
        size_t lastDot = filename.find_last_of(".");

        if (lastDot == std::string::npos)
            return filename;
        return filename.substr(0, lastDot);
    }

    std::string Parser::getFileName(std::string path)
    {
        return removeExtension(getFilename(path));
    }

} // namespace nts