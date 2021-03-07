/*
** EPITECH PROJECT, 2021
** TESTS_COMPONENT
** File description:
** Test Component
*/

#include <criterion/criterion.h>
#include <tests_Component.hpp>

namespace nts
{
    Test(testComponent, false)
    {
        loadFactoryComponents("./components");
        std::unique_ptr<Circuit> circuit = std::make_unique<Circuit>();
        Parser::LoadComponentsFromFile("tests/circuits/valids/nts_single/false.nts", circuit);

        cr_assert_eq(stringToTristate(circuit->getComponent("in")->getValue()), F);
        cr_assert_eq(stringToTristate(circuit->getComponent("out")->getValue()), F);
        circuit->simulate();
        cr_assert_eq(stringToTristate(circuit->getComponent("in")->getValue()), F);
        cr_assert_eq(stringToTristate(circuit->getComponent("out")->getValue()), F);
        circuit->simulate();
        cr_assert_eq(stringToTristate(circuit->getComponent("in")->getValue()), F);
        cr_assert_eq(stringToTristate(circuit->getComponent("out")->getValue()), F);
    }

    Test(testComponent, true)
    {
        loadFactoryComponents("./components");
        std::unique_ptr<Circuit> circuit = std::make_unique<Circuit>();
        Parser::LoadComponentsFromFile("tests/circuits/valids/nts_single/true.nts", circuit);

        cr_assert_eq(stringToTristate(circuit->getComponent("in")->getValue()), T);
        cr_assert_eq(stringToTristate(circuit->getComponent("out")->getValue()), T);
        circuit->simulate();
        cr_assert_eq(stringToTristate(circuit->getComponent("in")->getValue()), T);
        cr_assert_eq(stringToTristate(circuit->getComponent("out")->getValue()), T);
        circuit->simulate();
        cr_assert_eq(stringToTristate(circuit->getComponent("in")->getValue()), T);
        cr_assert_eq(stringToTristate(circuit->getComponent("out")->getValue()), T);
    }

    Test(testComponent, clock)
    {
        loadFactoryComponents("./components");
        std::unique_ptr<Circuit> circuit = std::make_unique<Circuit>();
        Parser::LoadComponentsFromFile("tests/circuits/valids/nts_single/clock.nts", circuit);

        cr_assert_eq(stringToTristate(circuit->getComponent("out")->getValue()), U);
        circuit->simulate();
        cr_assert_eq(stringToTristate(circuit->getComponent("out")->getValue()), U);

        circuit->setInput("cl", tristateToString(T));
        cr_assert_eq(stringToTristate(circuit->getComponent("out")->getValue()), U);
        circuit->simulate();
        cr_assert_eq(stringToTristate(circuit->getComponent("out")->getValue()), T);
        circuit->simulate();
        cr_assert_eq(stringToTristate(circuit->getComponent("out")->getValue()), F);
        circuit->simulate();
        cr_assert_eq(stringToTristate(circuit->getComponent("out")->getValue()), T);

        circuit->setInput("cl", tristateToString(U));
        circuit->simulate();
        cr_assert_eq(stringToTristate(circuit->getComponent("out")->getValue()), U);

        circuit->setInput("cl", tristateToString(F));
        cr_assert_eq(stringToTristate(circuit->getComponent("out")->getValue()), U);
        circuit->simulate();
        cr_assert_eq(stringToTristate(circuit->getComponent("out")->getValue()), F);
        circuit->simulate();
        cr_assert_eq(stringToTristate(circuit->getComponent("out")->getValue()), T);
        circuit->simulate();
        cr_assert_eq(stringToTristate(circuit->getComponent("out")->getValue()), F);
    }

} // namespace nts
