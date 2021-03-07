/*
** EPITECH PROJECT, 2021
** TESTS_COMPONENT
** File description:
** Tests_Component header
*/

#ifndef TESTS_COMPONENT_H_
#define TESTS_COMPONENT_H_

#include <vector>
#include <tuple>

#include <ComponentFactory.hpp>
#include <Circuit.hpp>

#define GET_COMPONENT_PATH(name) ComponentFactory::blueprintPathComponentFactoryMap[name]

namespace nts
{
    typedef std::vector<std::tuple<std::vector<Tristate>, std::vector<Tristate>>> TruthTable;

    static inline void testComponent(std::unique_ptr<Circuit> &circuit, std::vector<std::string> inputs, std::vector<std::string> outputs, TruthTable truthTable)
    {
        for (auto truthTableIt = truthTable.begin(); truthTableIt != truthTable.end(); truthTableIt++)
        {
            auto truthTableInputs = std::get<0>(*truthTableIt);
            auto truthTableOutputs = std::get<1>(*truthTableIt);

            int id = 0;
            for (auto inputIt = inputs.begin(); inputIt != inputs.end(); inputIt++)
                circuit->setInput(*inputIt, tristateToString(truthTableInputs.at(id++)));
            circuit->simulate();
            id = 0;
            for (auto outputIt = outputs.begin(); outputIt != outputs.end(); outputIt++)
            {
                Tristate output = stringToTristate(circuit->getComponent(*outputIt)->getValue());
                cr_assert_eq(output, truthTableOutputs.at(id++));
            }
        }
    }

#define GET_BIT(x, n) (x >> n & 0b1 ? T : F)

    template <int N>
    static inline std::vector<Tristate> intToBits(int x)
    {
        std::vector<Tristate> array;
        for (int k = N - 1; k >= 0; k--)
            array.push_back(GET_BIT(x, k));
        return array;
    }

} // namespace nts

#endif /* !TESTS_COMPONENT_H_ */