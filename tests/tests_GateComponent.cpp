/*
** EPITECH PROJECT, 2021
** TESTS_GATECOMPONENT
** File description:
** Test GateComponent
*/

#include <criterion/criterion.h>
#include <tests_Component.hpp>

namespace nts
{
    Test(GateComponent, buffer)
    {
        loadFactoryComponents("./components");
        std::unique_ptr<Circuit> circuit = std::make_unique<Circuit>();
        Parser::LoadComponentsFromFile(GET_COMPONENT_PATH("buffer"), circuit);

        testComponent(circuit,
                      {"in"},
                      {"out"},
                      {{{U}, {U}},
                       {{F}, {F}},
                       {{T}, {T}}});
    }

    Test(GateComponent, and)
    {
        loadFactoryComponents("./components");
        std::unique_ptr<Circuit> circuit = std::make_unique<Circuit>();
        Parser::LoadComponentsFromFile(GET_COMPONENT_PATH("and"), circuit);

        testComponent(circuit,
                      {"in_1", "in_2"},
                      {"out"},
                      {{{U, U}, {U}},
                       {{F, U}, {F}},
                       {{T, U}, {U}},
                       {{U, F}, {F}},
                       {{U, T}, {U}},
                       {{F, F}, {F}},
                       {{F, T}, {F}},
                       {{T, F}, {F}},
                       {{T, T}, {T}}});
    }

    Test(GateComponent, or)
    {
        loadFactoryComponents("./components");
        std::unique_ptr<Circuit> circuit = std::make_unique<Circuit>();
        Parser::LoadComponentsFromFile(GET_COMPONENT_PATH("or"), circuit);

        testComponent(circuit,
                      {"in_1", "in_2"},
                      {"out"},
                      {{{U, U}, {U}},
                       {{F, U}, {U}},
                       {{T, U}, {T}},
                       {{U, F}, {U}},
                       {{U, T}, {T}},
                       {{F, F}, {F}},
                       {{F, T}, {T}},
                       {{T, F}, {T}},
                       {{T, T}, {T}}});
    }

    Test(GateComponent, xor)
    {
        loadFactoryComponents("./components");
        std::unique_ptr<Circuit> circuit = std::make_unique<Circuit>();
        Parser::LoadComponentsFromFile(GET_COMPONENT_PATH("xor"), circuit);

        testComponent(circuit,
                      {"in_1", "in_2"},
                      {"out"},
                      {{{U, U}, {U}},
                       {{F, U}, {U}},
                       {{T, U}, {U}},
                       {{U, F}, {U}},
                       {{U, T}, {U}},
                       {{F, F}, {F}},
                       {{F, T}, {T}},
                       {{T, F}, {T}},
                       {{T, T}, {F}}});
    }

    Test(GateComponent, not )
    {
        loadFactoryComponents("./components");
        std::unique_ptr<Circuit> circuit = std::make_unique<Circuit>();
        Parser::LoadComponentsFromFile(GET_COMPONENT_PATH("not"), circuit);

        testComponent(circuit,
                      {"in"},
                      {"out"},
                      {{{U}, {U}},
                       {{F}, {T}},
                       {{T}, {F}}});
    }

    Test(GateComponent, nor)
    {
        loadFactoryComponents("./components");
        std::unique_ptr<Circuit> circuit = std::make_unique<Circuit>();
        Parser::LoadComponentsFromFile(GET_COMPONENT_PATH("nor"), circuit);

        testComponent(circuit,
                      {"in_1", "in_2"},
                      {"out"},
                      {{{U, U}, {U}},
                       {{F, U}, {U}},
                       {{T, U}, {F}},
                       {{U, F}, {U}},
                       {{U, T}, {F}},
                       {{F, F}, {T}},
                       {{F, T}, {F}},
                       {{T, F}, {F}},
                       {{T, T}, {F}}});
    }

    Test(GateComponent, nxor)
    {
        loadFactoryComponents("./components");
        std::unique_ptr<Circuit> circuit = std::make_unique<Circuit>();
        Parser::LoadComponentsFromFile(GET_COMPONENT_PATH("nxor"), circuit);

        testComponent(circuit,
                      {"in_1", "in_2"},
                      {"out"},
                      {{{U, U}, {U}},
                       {{F, U}, {U}},
                       {{T, U}, {U}},
                       {{U, F}, {U}},
                       {{U, T}, {U}},
                       {{F, F}, {T}},
                       {{F, T}, {F}},
                       {{T, F}, {F}},
                       {{T, T}, {T}}});
    }

    Test(GateComponent, tristate)
    {
        loadFactoryComponents("./components");
        std::unique_ptr<Circuit> circuit = std::make_unique<Circuit>();
        Parser::LoadComponentsFromFile(GET_COMPONENT_PATH("tristate"), circuit);

        testComponent(circuit,
                      {"in", "enable"},
                      {"out"},
                      {{{U, U}, {U}},
                       {{F, F}, {U}},
                       {{F, T}, {F}},
                       {{T, T}, {T}},
                       {{T, F}, {U}}});
    }

    Test(GateComponent, 3and)
    {
        loadFactoryComponents("./components");
        std::unique_ptr<Circuit> circuit = std::make_unique<Circuit>();
        Parser::LoadComponentsFromFile(GET_COMPONENT_PATH("3and"), circuit);

        testComponent(circuit,
                      {"in_1", "in_2", "in_3"},
                      {"out"},
                      {{{U, U, U}, {U}},

                       {{F, U, U}, {F}},
                       {{T, U, U}, {U}},
                       {{U, F, U}, {F}},
                       {{U, T, U}, {U}},
                       {{U, U, F}, {F}},
                       {{U, U, T}, {U}},

                       {{F, F, U}, {F}},
                       {{F, T, U}, {F}},
                       {{T, F, U}, {F}},
                       {{T, T, U}, {U}},
                       {{F, U, F}, {F}},
                       {{F, U, T}, {F}},
                       {{T, U, F}, {F}},
                       {{T, U, T}, {U}},
                       {{U, F, F}, {F}},
                       {{U, F, T}, {F}},
                       {{U, T, F}, {F}},
                       {{U, T, T}, {U}},

                       {{F, F, F}, {F}},
                       {{F, F, T}, {F}},
                       {{F, T, F}, {F}},
                       {{F, T, T}, {F}},
                       {{T, F, F}, {F}},
                       {{T, F, T}, {F}},
                       {{T, T, F}, {F}},
                       {{T, T, T}, {T}}});
    }

    Test(GateComponent, 3nand)
    {
        loadFactoryComponents("./components");
        std::unique_ptr<Circuit> circuit = std::make_unique<Circuit>();
        Parser::LoadComponentsFromFile(GET_COMPONENT_PATH("3nand"), circuit);

        testComponent(circuit,
                      {"in_1", "in_2", "in_3"},
                      {"out"},
                      {{{U, U, U}, {U}},

                       {{F, F, U}, {T}},
                       {{F, T, U}, {T}},
                       {{T, F, U}, {T}},
                       {{T, T, U}, {U}},
                       {{F, U, F}, {T}},
                       {{F, U, T}, {T}},
                       {{T, U, F}, {T}},
                       {{T, U, T}, {U}},
                       {{U, F, F}, {T}},
                       {{U, F, T}, {T}},
                       {{U, T, F}, {T}},
                       {{U, T, T}, {U}},

                       {{F, F, F}, {T}},
                       {{F, F, T}, {T}},
                       {{F, T, F}, {T}},
                       {{F, T, T}, {T}},
                       {{T, F, F}, {T}},
                       {{T, F, T}, {T}},
                       {{T, T, F}, {T}},
                       {{T, T, T}, {F}}});
    }

} // namespace nts