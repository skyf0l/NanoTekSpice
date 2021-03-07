/*
** EPITECH PROJECT, 2021
** TESTS_LOGICCOMPONENT
** File description:
** Test LogicComponent
*/

#include <criterion/criterion.h>
#include <math.h>
#include <stdlib.h>

#include <tests_Component.hpp>

namespace nts
{
#define INT_TO_4BITS(x) GET_BIT(x, 3), GET_BIT(x, 2), GET_BIT(x, 1), GET_BIT(x, 0)

    Test(LogicComponent, 4008)
    {
        loadFactoryComponents("./components");
        std::unique_ptr<Circuit> circuit = std::make_unique<Circuit>();
        Parser::LoadComponentsFromFile(GET_COMPONENT_PATH("4008"), circuit);

        TruthTable truthTable;
        truthTable.push_back({{U, U, U, U, U, U, U, U, U}, {U, U, U, U, U}});
        for (int a = 0; a < 16; a++)
            for (int b = 0; b < 16; b++)
            {
                truthTable.push_back({{INT_TO_4BITS(a), INT_TO_4BITS(b), F}, {intToBits<5>(a + b)}});
                truthTable.push_back({{INT_TO_4BITS(a), INT_TO_4BITS(b), T}, {intToBits<5>(a + b + 1)}});
            }
        testComponent(circuit,
                      {"in_a4", "in_a3", "in_a2", "in_a1", "in_b4", "in_b3", "in_b2", "in_b1", "in_c"},
                      {"out_c", "out_4", "out_3", "out_2", "out_1"},
                      truthTable);
    }

    Test(LogicComponent, 4017)
    {
        loadFactoryComponents("./components");
        std::unique_ptr<Circuit> circuit = std::make_unique<Circuit>();
        Parser::LoadComponentsFromFile(GET_COMPONENT_PATH("4017"), circuit);

        testComponent(circuit,
                      {"clock", "inhibit", "reset"},
                      {"out_0", "out_1", "out_2", "out_3", "out_4", "out_5", "out_6", "out_7", "out_8", "out_9", "out_s"},
                      {
                          // init
                          {{U, U, U}, {U, U, U, U, U, U, U, U, U, U, U}},
                          {{F, F, F}, {U, U, U, U, U, U, U, U, U, U, U}},
                          {{F, F, T}, {T, F, F, F, F, F, F, F, F, F, T}},

                          // loop
                          {{F, F, F}, {T, F, F, F, F, F, F, F, F, F, T}},
                          {{T, F, F}, {F, T, F, F, F, F, F, F, F, F, T}},
                          {{F, F, F}, {F, T, F, F, F, F, F, F, F, F, T}},
                          {{T, F, F}, {F, F, T, F, F, F, F, F, F, F, T}},
                          {{F, F, F}, {F, F, T, F, F, F, F, F, F, F, T}},
                          {{T, F, F}, {F, F, F, T, F, F, F, F, F, F, T}},
                          {{F, F, F}, {F, F, F, T, F, F, F, F, F, F, T}},
                          {{T, F, F}, {F, F, F, F, T, F, F, F, F, F, T}},
                          {{F, F, F}, {F, F, F, F, T, F, F, F, F, F, T}},
                          {{T, F, F}, {F, F, F, F, F, T, F, F, F, F, F}},
                          {{F, F, F}, {F, F, F, F, F, T, F, F, F, F, F}},
                          {{T, F, F}, {F, F, F, F, F, F, T, F, F, F, F}},
                          {{F, F, F}, {F, F, F, F, F, F, T, F, F, F, F}},
                          {{T, F, F}, {F, F, F, F, F, F, F, T, F, F, F}},
                          {{F, F, F}, {F, F, F, F, F, F, F, T, F, F, F}},
                          {{T, F, F}, {F, F, F, F, F, F, F, F, T, F, F}},
                          {{F, F, F}, {F, F, F, F, F, F, F, F, T, F, F}},
                          {{T, F, F}, {F, F, F, F, F, F, F, F, F, T, F}},
                          {{T, T, F}, {F, F, F, F, F, F, F, F, F, T, F}},
                          {{T, F, F}, {T, F, F, F, F, F, F, F, F, F, T}},
                          {{F, F, F}, {T, F, F, F, F, F, F, F, F, F, T}},

                          // reset
                          {{T, F, F}, {F, T, F, F, F, F, F, F, F, F, T}},
                          {{F, F, F}, {F, T, F, F, F, F, F, F, F, F, T}},
                          {{F, F, F}, {F, T, F, F, F, F, F, F, F, F, T}},
                          {{F, F, T}, {T, F, F, F, F, F, F, F, F, F, T}},
                      });
    }

    Test(LogicComponent, 4040)
    {
        loadFactoryComponents("./components");
        std::unique_ptr<Circuit> circuit = std::make_unique<Circuit>();
        Parser::LoadComponentsFromFile(GET_COMPONENT_PATH("4040"), circuit);

        TruthTable truthTable;
        truthTable.push_back({{U, U}, {U, U, U, U, U, U, U, U, U, U, U, U}});
        truthTable.push_back({{F, F}, {U, U, U, U, U, U, U, U, U, U, U, U}});
        truthTable.push_back({{F, T}, {F, F, F, F, F, F, F, F, F, F, F, F}});
        truthTable.push_back({{F, F}, {F, F, F, F, F, F, F, F, F, F, F, F}});
        truthTable.push_back({{T, F}, {F, F, F, F, F, F, F, F, F, F, F, F}});
        for (int x = 1; x < 2500; x++)
        {
            truthTable.push_back({{F, F}, {intToBits<12>(x)}});
            truthTable.push_back({{T, F}, {intToBits<12>(x)}});
        }
        truthTable.push_back({{F, T}, {F, F, F, F, F, F, F, F, F, F, F, F}});
        truthTable.push_back({{F, F}, {F, F, F, F, F, F, F, F, F, F, F, F}});
        testComponent(circuit,
                      {"clock", "reset"},
                      {"out_11", "out_10", "out_09", "out_08", "out_07", "out_06", "out_05", "out_04", "out_03", "out_02", "out_01", "out_00"},
                      truthTable);
    }

    Test(LogicComponent, 4040_gates)
    {
        loadFactoryComponents("./components");
        std::unique_ptr<Circuit> circuit = std::make_unique<Circuit>();
        Parser::LoadComponentsFromFile(GET_COMPONENT_PATH("4040_gates"), circuit);

        TruthTable truthTable;
        truthTable.push_back({{U, U}, {U, U, U, U, U, U, U, U, U, U, U, U}});
        truthTable.push_back({{F, F}, {U, U, U, U, U, U, U, U, U, U, U, U}});
        truthTable.push_back({{F, T}, {F, F, F, F, F, F, F, F, F, F, F, F}});
        truthTable.push_back({{F, F}, {F, F, F, F, F, F, F, F, F, F, F, F}});
        truthTable.push_back({{T, F}, {F, F, F, F, F, F, F, F, F, F, F, F}});
        for (int x = 1; x < 2500; x++)
        {
            truthTable.push_back({{F, F}, {intToBits<12>(x)}});
            truthTable.push_back({{T, F}, {intToBits<12>(x)}});
        }
        truthTable.push_back({{F, T}, {F, F, F, F, F, F, F, F, F, F, F, F}});
        truthTable.push_back({{F, F}, {F, F, F, F, F, F, F, F, F, F, F, F}});
        testComponent(circuit,
                      {"clock", "reset"},
                      {"out_11", "out_10", "out_09", "out_08", "out_07", "out_06", "out_05", "out_04", "out_03", "out_02", "out_01", "out_00"},
                      truthTable);
    }

    Test(LogicComponentUnit, 4512)
    {
        loadFactoryComponents("./components");
        std::unique_ptr<Circuit> circuit = std::make_unique<Circuit>();
        Parser::LoadComponentsFromFile(GET_COMPONENT_PATH("4512"), circuit);

        testComponent(circuit,
                      {"in_0", "in_1", "in_2", "in_3", "in_4", "in_5", "in_6", "in_7", "in_a", "in_b", "in_c", "inhibit", "enable"},
                      {"out_data"},
                      {{{U, U, U, U, U, U, U, U, U, U, U, U, U}, {U}},
                       {{F, F, F, F, F, F, F, F, F, F, F, F, F}, {F}},

                       {{F, F, F, F, F, F, F, F,    F, F, F,     F, F}, {F}},
                       {{T, F, F, F, F, F, F, F,    F, F, F,     F, F}, {T}},
                       {{F, T, F, F, F, F, F, F,    F, F, T,     F, F}, {T}},
                       {{F, F, T, F, F, F, F, F,    F, T, F,     F, F}, {T}},
                       {{F, F, F, T, F, F, F, F,    F, T, T,     F, F}, {T}},
                       {{F, F, F, F, T, F, F, F,    T, F, F,     F, F}, {T}},
                       {{F, F, F, F, F, T, F, F,    T, F, T,     F, F}, {T}},
                       {{F, F, F, F, F, F, T, F,    T, T, F,     F, F}, {T}},
                       {{F, F, F, F, F, F, F, T,    T, T, T,     F, F}, {T}},

                       // inhibit
                       {{F, F, F, F, F, F, F, F, F, F, F, T, F}, {F}},
                       {{F, F, F, F, F, F, F, T, F, F, F, T, F}, {F}},
                       {{F, T, F, F, F, F, F, F, F, F, T, T, F}, {F}},
                       {{F, F, F, T, F, F, F, F, T, F, F, T, F}, {F}},
                       {{T, T, F, F, F, F, F, F, F, F, F, T, F}, {F}},
                       {{T, F, F, F, F, F, F, F, T, F, F, T, F}, {F}},
                       {{F, T, F, T, F, F, F, T, T, F, F, T, F}, {F}},
                       {{T, T, F, F, F, F, F, F, T, F, F, T, F}, {F}},

                       // enable
                       {{F, F, F, F, F, F, F, F, F, F, F, F, T}, {U}},
                       {{F, F, F, T, F, F, T, F, F, F, F, F, T}, {U}},
                       {{F, T, F, F, F, F, F, F, T, F, F, F, T}, {U}},
                       {{F, F, F, F, F, F, F, F, T, F, F, F, T}, {U}},
                       {{T, T, F, F, T, F, F, F, F, F, F, F, T}, {U}},
                       {{T, F, F, F, F, F, F, F, T, F, F, F, T}, {U}},
                       {{F, T, F, F, F, F, F, F, T, T, F, F, T}, {U}},
                       {{T, T, F, F, F, T, F, F, T, F, F, T, T}, {U}}});
    }

    Test(LogicComponentUnit, 4514)
    {
        loadFactoryComponents("./components");
        std::unique_ptr<Circuit> circuit = std::make_unique<Circuit>();
        Parser::LoadComponentsFromFile(GET_COMPONENT_PATH("4514"), circuit);

        TruthTable truthTable;
        truthTable.push_back({{U, U, U, U, U, U}, {U, U, U, U, U, U, U, U, U, U, U, U, U, U, U, U}});
        truthTable.push_back({{F, F, F, F, F, F}, {U, U, U, U, U, U, U, U, U, U, U, U, U, U, U, U}});
        truthTable.push_back({{F, F, F, F, F, T}, {F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, T}});
        truthTable.push_back({{F, F, F, F, F, F}, {F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, T}});
        truthTable.push_back({{F, F, F, F, T, F}, {F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F}});
        truthTable.push_back({{F, F, F, F, F, F}, {F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, T}});
        for (int a = 0; a < 16; a++)
        {
            std::vector<nts::Tristate> in_write = intToBits<4>(a);
            in_write.push_back(F);
            in_write.push_back(T);
            truthTable.push_back({in_write, intToBits<16>(std::pow(2, a))});

            std::vector<nts::Tristate> in_read = intToBits<4>(rand() % 16);
            in_read.push_back(F);
            in_read.push_back(F);
            truthTable.push_back({in_read, intToBits<16>(std::pow(2, a))});

            std::vector<nts::Tristate> in_inhibit = intToBits<4>(a);
            in_inhibit.push_back(T);
            in_inhibit.push_back(F);
            truthTable.push_back({in_inhibit, intToBits<16>(0)});
        }
        testComponent(circuit,
                      {"in_3", "in_2", "in_1", "in_0", "inhibit", "strobe"},
                      {"out_15", "out_14", "out_13", "out_12", "out_11", "out_10", "out_09", "out_08", "out_07", "out_06", "out_05", "out_04", "out_03", "out_02", "out_01", "out_00"},
                      {truthTable});
    }

    Test(LogicComponentUnit, 4094)
    {
        loadFactoryComponents("./components");
        std::unique_ptr<Circuit> circuit = std::make_unique<Circuit>();
        Parser::LoadComponentsFromFile(GET_COMPONENT_PATH("4094"), circuit);

        testComponent(circuit,
                      {"clock", "data", "strobe", "enable"},
                      {"out_0", "out_1", "out_2", "out_3", "out_4", "out_5", "out_6", "out_7", "out_qs", "out_qe"},
                      {
                           {{U, U, U, U}, {U, U, U, U, U, U, U, U, U, U}},

                           // append data
                           {{F, F, T, T}, {U, U, U, U, U, U, U, U, U, U}},
                           {{T, F, T, T}, {F, U, U, U, U, U, U, U, U, U}},
                           {{F, F, T, T}, {F, U, U, U, U, U, U, U, U, U}},
                           {{T, F, T, T}, {F, F, U, U, U, U, U, U, U, U}},
                           {{F, F, T, T}, {F, F, U, U, U, U, U, U, U, U}},
                           {{T, F, T, T}, {F, F, F, U, U, U, U, U, U, U}},
                           {{F, T, T, T}, {F, F, F, U, U, U, U, U, U, U}},
                           {{T, T, T, T}, {T, F, F, F, U, U, U, U, U, U}},
                           {{F, T, T, T}, {T, F, F, F, U, U, U, U, U, U}},
                           {{T, T, T, T}, {T, T, F, F, F, U, U, U, U, U}},
                           {{F, T, T, T}, {T, T, F, F, F, U, U, U, U, U}},
                           {{T, T, T, T}, {T, T, T, F, F, F, U, U, U, U}},
                           {{F, T, T, T}, {T, T, T, F, F, F, U, U, U, U}},

                           // enable
                           {{F, T, T, F}, {U, U, U, U, U, U, U, U, U, U}},
                           {{F, T, T, T}, {T, T, T, F, F, F, U, U, U, U}},
                           {{F, T, T, F}, {U, U, U, U, U, U, U, U, U, U}},

                      });
    }

} // namespace nts