/*
** EPITECH PROJECT, 2021
** BLUEPRINT
** File description:
** Blueprint header
*/

#ifndef BLUEPRINT_H_
#define BLUEPRINT_H_

#include <vector>
#include <tuple>
#include <string>

#include <Circuit.hpp>

namespace nts
{
    class Blueprint
    {
    public:
        Blueprint() = default;
        void loadBlueprint(std::unique_ptr<Circuit> &_circuit);

        std::vector<std::tuple<std::string, std::string>> chipsets;                        // name, type
        std::vector<std::tuple<std::string, std::size_t, std::string, std::size_t>> links; // name1, pin1, name2, pin2
        std::vector<std::tuple<std::string, std::size_t>> circuits;                        // name, pin
        std::vector<std::tuple<std::string, std::string>> values;                          // name, value

        static Blueprint getBlueprintFromFile(std::string path);
    };

} // namespace nts

#endif /* !BLUEPRINT_H_ */