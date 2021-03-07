/*
** EPITECH PROJECT, 2021
** TESTS_LOGICCOMPONENTUNIT
** File description:
** Test LogicComponentUnit
*/

#include <criterion/criterion.h>
#include <math.h>

#include <tests_Component.hpp>

namespace nts
{
    Test(LogicComponentUnit, SR_latch)
    {
        loadFactoryComponents("./components");
        std::unique_ptr<Circuit> circuit = std::make_unique<Circuit>();
        Parser::LoadComponentsFromFile(GET_COMPONENT_PATH("SR_latch"), circuit);

        testComponent(circuit,
                      {"S", "R"},
                      {"Q", "Q2"},
                      {{{U, U}, {U, U}},
                       {{F, F}, {T, T}},
                       {{F, T}, {T, F}},
                       {{T, F}, {F, T}},
                       {{T, T}, {F, T}},
                       {{T, F}, {F, T}},
                       {{F, T}, {T, F}},
                       {{T, T}, {T, F}},
                       {{F, F}, {T, T}}});
    }

    Test(LogicComponentUnit, D_latch)
    {
        loadFactoryComponents("./components");
        std::unique_ptr<Circuit> circuit = std::make_unique<Circuit>();
        Parser::LoadComponentsFromFile(GET_COMPONENT_PATH("D_latch"), circuit);

        testComponent(circuit,
                      {"D", "E"},
                      {"Q", "Q2"},
                      {{{U, U}, {U, U}},
                       {{F, F}, {U, U}},
                       {{F, T}, {F, T}},
                       {{F, F}, {F, T}},
                       {{T, F}, {F, T}},
                       {{F, F}, {F, T}},
                       {{F, T}, {F, T}},
                       {{T, T}, {T, F}},
                       {{T, F}, {T, F}},
                       {{F, F}, {T, F}},
                       {{F, T}, {F, T}},
                       {{F, T}, {F, T}}});
    }

    Test(LogicComponentUnit, 4bits_register)
    {
        loadFactoryComponents("./components");
        std::unique_ptr<Circuit> circuit = std::make_unique<Circuit>();
        Parser::LoadComponentsFromFile(GET_COMPONENT_PATH("4bits_register"), circuit);

        testComponent(circuit,
                      {"in_0", "in_1", "in_2", "in_3", "strobe"},
                      {"out_0", "out_1", "out_2", "out_3"},
                      {{{U, U, U, U, U}, {U, U, U, U}},

                       // init
                       {{F, F, F, F, F}, {U, U, U, U}},
                       {{F, F, F, F, T}, {F, F, F, F}},
                       {{F, F, F, F, F}, {F, F, F, F}},

                       // write disable
                       {{F, F, F, F, F}, {F, F, F, F}},
                       {{T, F, F, F, F}, {F, F, F, F}},
                       {{F, T, F, F, F}, {F, F, F, F}},
                       {{F, F, T, F, F}, {F, F, F, F}},
                       {{F, F, F, T, F}, {F, F, F, F}},
                       {{T, T, T, T, F}, {F, F, F, F}},

                       // write enable
                       {{F, F, F, F, T}, {F, F, F, F}},
                       {{T, F, F, F, T}, {T, F, F, F}},
                       {{F, T, F, F, T}, {F, T, F, F}},
                       {{F, F, T, F, T}, {F, F, T, F}},
                       {{F, F, F, T, T}, {F, F, F, T}},
                       {{T, T, T, T, T}, {T, T, T, T}},

                       // save
                       {{T, T, T, T, F}, {T, T, T, T}},
                       {{F, F, F, F, F}, {T, T, T, T}},
                       {{F, F, F, F, T}, {F, F, F, F}},
                       {{F, F, F, F, F}, {F, F, F, F}}});
    }

    Test(LogicComponentUnit, 8bits_register)
    {
        loadFactoryComponents("./components");
        std::unique_ptr<Circuit> circuit = std::make_unique<Circuit>();
        Parser::LoadComponentsFromFile(GET_COMPONENT_PATH("8bits_register"), circuit);

        testComponent(circuit,
                      {"in_0", "in_1", "in_2", "in_3", "in_4", "in_5", "in_6", "in_7", "strobe"},
                      {"out_0", "out_1", "out_2", "out_3", "out_4", "out_5", "out_6", "out_7"},
                      {{{U, U, U, U, U, U, U, U, U}, {U, U, U, U, U, U, U, U}},

                       // init
                       {{F, F, F, F, F, F, F, F, F}, {U, U, U, U, U, U, U, U}},
                       {{F, F, F, F, F, F, F, F, T}, {F, F, F, F, F, F, F, F}},
                       {{F, F, F, F, F, F, F, F, F}, {F, F, F, F, F, F, F, F}},

                       // write disable
                       {{F, F, F, F, F, F, F, F, F}, {F, F, F, F, F, F, F, F}},
                       {{T, F, F, F, F, F, F, F, F}, {F, F, F, F, F, F, F, F}},
                       {{F, T, F, F, F, F, F, F, F}, {F, F, F, F, F, F, F, F}},
                       {{F, F, T, F, F, F, F, F, F}, {F, F, F, F, F, F, F, F}},
                       {{F, F, F, T, F, F, F, F, F}, {F, F, F, F, F, F, F, F}},
                       {{F, F, F, F, T, F, F, F, F}, {F, F, F, F, F, F, F, F}},
                       {{F, F, F, F, F, T, F, F, F}, {F, F, F, F, F, F, F, F}},
                       {{F, F, F, F, F, F, T, F, F}, {F, F, F, F, F, F, F, F}},
                       {{F, F, F, F, F, F, F, T, F}, {F, F, F, F, F, F, F, F}},
                       {{T, T, T, T, T, T, T, T, F}, {F, F, F, F, F, F, F, F}},

                       // write enable
                       {{F, F, F, F, F, F, F, F, T}, {F, F, F, F, F, F, F, F}},
                       {{T, F, F, F, F, F, F, F, T}, {T, F, F, F, F, F, F, F}},
                       {{F, T, F, F, F, F, F, F, T}, {F, T, F, F, F, F, F, F}},
                       {{F, F, T, F, F, F, F, F, T}, {F, F, T, F, F, F, F, F}},
                       {{F, F, F, T, F, F, F, F, T}, {F, F, F, T, F, F, F, F}},
                       {{F, F, F, F, T, F, F, F, T}, {F, F, F, F, T, F, F, F}},
                       {{F, F, F, F, F, T, F, F, T}, {F, F, F, F, F, T, F, F}},
                       {{F, F, F, F, F, F, T, F, T}, {F, F, F, F, F, F, T, F}},
                       {{F, F, F, F, F, F, F, T, T}, {F, F, F, F, F, F, F, T}},
                       {{T, T, T, T, T, T, T, T, T}, {T, T, T, T, T, T, T, T}},

                       // save
                       {{T, T, T, T, T, T, T, T, F}, {T, T, T, T, T, T, T, T}},
                       {{F, F, F, F, F, F, F, F, F}, {T, T, T, T, T, T, T, T}},
                       {{F, F, F, F, F, F, F, F, T}, {F, F, F, F, F, F, F, F}},
                       {{F, F, F, F, F, F, F, F, F}, {F, F, F, F, F, F, F, F}}});
    }

    Test(LogicComponentUnit, D_R_flipflop)
    {
        loadFactoryComponents("./components");
        std::unique_ptr<Circuit> circuit = std::make_unique<Circuit>();
        Parser::LoadComponentsFromFile(GET_COMPONENT_PATH("D_R_flipflop"), circuit);

        testComponent(circuit,
                      {"D", "CLK", "R"},
                      {"Q", "Q2"},
                      {{{U, U, U}, {U, U}},
                       {{F, F, F}, {F, T}},
                       {{F, F, T}, {F, T}},
                       {{T, F, T}, {F, T}},
                       {{T, T, T}, {T, F}},
                       {{T, F, T}, {T, F}},
                       {{T, T, T}, {T, F}},
                       {{F, F, T}, {T, F}},
                       {{F, T, T}, {F, T}},
                       {{F, F, T}, {F, T}},
                       {{T, F, T}, {F, T}},
                       {{T, T, T}, {T, F}},
                       {{F, F, T}, {T, F}},
                       {{F, F, F}, {F, T}},
                       {{F, F, T}, {F, T}}});
    }

    Test(LogicComponentUnit, T_R_flipflop)
    {
        loadFactoryComponents("./components");
        std::unique_ptr<Circuit> circuit = std::make_unique<Circuit>();
        Parser::LoadComponentsFromFile(GET_COMPONENT_PATH("T_R_flipflop"), circuit);

        testComponent(circuit,
                      {"T", "CLK", "R"},
                      {"Q", "Q2"},
                      {{{U, U, U}, {U, U}},
                       {{F, F, F}, {F, T}},
                       {{F, F, T}, {F, T}},
                       {{F, T, T}, {F, T}},
                       {{F, F, T}, {F, T}},
                       {{T, F, T}, {F, T}},
                       {{T, T, T}, {T, F}},
                       {{T, F, T}, {T, F}},
                       {{F, F, T}, {T, F}},
                       {{T, F, T}, {T, F}},
                       {{T, T, T}, {F, T}},
                       {{T, F, T}, {F, T}},
                       {{T, T, T}, {T, F}},
                       {{F, F, T}, {T, F}},
                       {{F, F, F}, {F, T}},
                       {{F, F, T}, {F, T}}});
    }

    Test(LogicComponentUnit, adder)
    {
        loadFactoryComponents("./components");
        std::unique_ptr<Circuit> circuit = std::make_unique<Circuit>();
        Parser::LoadComponentsFromFile(GET_COMPONENT_PATH("adder"), circuit);

        testComponent(circuit,
                      {"in_1", "in_2", "in_c"},
                      {"sum", "out_c"},
                      {{{U, U, U}, {U, U}},
                       {{F, F, F}, {F, F}},
                       {{T, F, F}, {T, F}},
                       {{F, T, F}, {T, F}},
                       {{F, F, T}, {T, F}},
                       {{T, T, F}, {F, T}},
                       {{T, F, T}, {F, T}},
                       {{F, T, T}, {F, T}},
                       {{T, T, T}, {T, T}}});
    }

#define INT_TO_4BITS(x) (x >> 3 & 0b1 ? T : F), (x >> 2 & 0b1 ? T : F), (x >> 1 & 0b1 ? T : F), (x & 0b1 ? T : F)

    Test(LogicComponentUnit, 4bit_adder)
    {
        loadFactoryComponents("./components");
        std::unique_ptr<Circuit> circuit = std::make_unique<Circuit>();
        Parser::LoadComponentsFromFile(GET_COMPONENT_PATH("4bit_adder"), circuit);

        TruthTable truthTable;
        truthTable.push_back({{U, U, U, U, U, U, U, U, U}, {U, U, U, U, U}});
        for (int a = 0; a < 16; a++)
            for (int b = 0; b < 16; b++)
            {
                truthTable.push_back({{INT_TO_4BITS(a), INT_TO_4BITS(b), F}, intToBits<5>(a + b)});
                truthTable.push_back({{INT_TO_4BITS(a), INT_TO_4BITS(b), T}, intToBits<5>(a + b + 1)});
            }
        testComponent(circuit,
                      {"in_a4", "in_a3", "in_a2", "in_a1", "in_b4", "in_b3", "in_b2", "in_b1", "in_c"},
                      {"out_c", "out_4", "out_3", "out_2", "out_1"},
                      truthTable);
    }

    Test(LogicComponentUnit, 2mux)
    {
        loadFactoryComponents("./components");
        std::unique_ptr<Circuit> circuit = std::make_unique<Circuit>();
        Parser::LoadComponentsFromFile(GET_COMPONENT_PATH("2mux"), circuit);

        testComponent(circuit,
                      {"I0", "I1", "A"},
                      {"Y"},
                      {{{U, U, U}, {U}},
                       {{F, F, F}, {F}},
                       {{F, T, F}, {F}},
                       {{F, F, T}, {F}},
                       {{T, T, F}, {T}},
                       {{T, F, T}, {F}},
                       {{F, T, T}, {T}},
                       {{T, T, T}, {T}}});
    }

    Test(LogicComponentUnit, 4mux)
    {
        loadFactoryComponents("./components");
        std::unique_ptr<Circuit> circuit = std::make_unique<Circuit>();
        Parser::LoadComponentsFromFile(GET_COMPONENT_PATH("4mux"), circuit);

        testComponent(circuit,
                      {"I0", "I1", "I2", "I3", "A", "B"},
                      {"Y"},
                      {{{U, U, U, U, U, U}, {U}},
                       {{F, F, F, F, F, F}, {F}},
                       {{F, F, F, F, F, F}, {F}},
                       {{F, T, F, F, F, F}, {F}},
                       {{F, F, F, F, T, F}, {F}},
                       {{T, T, F, F, F, F}, {T}},
                       {{T, F, F, F, T, F}, {F}},
                       {{F, T, F, F, T, F}, {T}},
                       {{T, T, F, F, T, F}, {T}}});
    }

    Test(LogicComponentUnit, 8mux)
    {
        loadFactoryComponents("./components");
        std::unique_ptr<Circuit> circuit = std::make_unique<Circuit>();
        Parser::LoadComponentsFromFile(GET_COMPONENT_PATH("8mux"), circuit);

        testComponent(circuit,
                      {"I0", "I1", "I2", "I3", "I4", "I5", "I6", "I7", "A", "B", "C"},
                      {"Y"},
                      {{{U, U, U, U, U, U, U, U, U, U, U}, {U}},
                       {{F, F, F, F, F, F, F, F, F, F, F}, {F}},
                       {{F, F, F, F, F, F, F, F, F, F, F}, {F}},
                       {{F, T, F, F, F, F, F, F, F, F, F}, {F}},
                       {{F, F, F, F, F, F, F, F, T, F, F}, {F}},
                       {{T, T, F, F, F, F, F, F, F, F, F}, {T}},
                       {{T, F, F, F, F, F, F, F, T, F, F}, {F}},
                       {{F, T, F, F, F, F, F, F, T, F, F}, {T}},
                       {{T, T, F, F, F, F, F, F, T, F, F}, {T}}});
    }

    Test(LogicComponentUnit, 2dmux)
    {
        loadFactoryComponents("./components");
        std::unique_ptr<Circuit> circuit = std::make_unique<Circuit>();
        Parser::LoadComponentsFromFile(GET_COMPONENT_PATH("2dmux"), circuit);

        testComponent(circuit,
                      {"D", "A"},
                      {"Y0", "Y1"},
                      {{{U, U}, {U, U}},
                       {{F, F}, {F, F}},
                       {{F, T}, {F, F}},
                       {{T, F}, {T, F}},
                       {{T, T}, {F, T}}});
    }

    Test(LogicComponentUnit, 2_to_4_decoder)
    {
        loadFactoryComponents("./components");
        std::unique_ptr<Circuit> circuit = std::make_unique<Circuit>();
        Parser::LoadComponentsFromFile(GET_COMPONENT_PATH("2_to_4_decoder"), circuit);

        TruthTable truthTable;
        truthTable.push_back({{U, U, U}, {U, U, U, U}});
        truthTable.push_back({{F, F, F}, {F, F, F, F}});
        truthTable.push_back({{F, F, T}, {F, F, F, T}});
        for (int a = 0; a < 4; a++)
        {
            std::vector<nts::Tristate> in = intToBits<2>(a);
            in.push_back(T);
            truthTable.push_back({in, intToBits<4>(std::pow(2, a))});
        }
        testComponent(circuit,
                      {"A1", "A0", "E"},
                      {"Y3", "Y2", "Y1", "Y0"},
                      {truthTable});
    }

    Test(LogicComponentUnit, 3_to_8_decoder)
    {
        loadFactoryComponents("./components");
        std::unique_ptr<Circuit> circuit = std::make_unique<Circuit>();
        Parser::LoadComponentsFromFile(GET_COMPONENT_PATH("3_to_8_decoder"), circuit);

        TruthTable truthTable;
        truthTable.push_back({{U, U, U, U}, {U, U, U, U, U, U, U, U}});
        truthTable.push_back({{F, F, F, F}, {F, F, F, F, F, F, F, F}});
        truthTable.push_back({{F, F, F, T}, {F, F, F, F, F, F, F, T}});
        for (int a = 0; a < 8; a++)
        {
            std::vector<nts::Tristate> in = intToBits<3>(a);
            in.push_back(T);
            truthTable.push_back({in, intToBits<8>(std::pow(2, a))});
        }
        testComponent(circuit,
                      {"A2", "A1", "A0", "E"},
                      {"Y7", "Y6", "Y5", "Y4", "Y3", "Y2", "Y1", "Y0"},
                      {truthTable});
    }

    Test(LogicComponentUnit, 4_to_16_decoder)
    {
        loadFactoryComponents("./components");
        std::unique_ptr<Circuit> circuit = std::make_unique<Circuit>();
        Parser::LoadComponentsFromFile(GET_COMPONENT_PATH("4_to_16_decoder"), circuit);

        TruthTable truthTable;
        truthTable.push_back({{U, U, U, U, U}, {U, U, U, U, U, U, U, U, U, U, U, U, U, U, U, U}});
        truthTable.push_back({{F, F, F, F, F}, {F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F}});
        truthTable.push_back({{F, F, F, F, T}, {F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, T}});
        for (int a = 0; a < 16; a++)
        {
            std::vector<nts::Tristate> in = intToBits<4>(a);
            in.push_back(T);
            truthTable.push_back({in, intToBits<16>(std::pow(2, a))});
        }
        testComponent(circuit,
                      {"A3", "A2", "A1", "A0", "E"},
                      {"Y15", "Y14", "Y13", "Y12", "Y11", "Y10", "Y9", "Y8", "Y7", "Y6", "Y5", "Y4", "Y3", "Y2", "Y1", "Y0"},
                      {truthTable});
    }

} // namespace nts