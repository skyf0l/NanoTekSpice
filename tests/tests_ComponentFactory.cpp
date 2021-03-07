/*
** EPITECH PROJECT, 2021
** TESTS_COMPONENTFACTORY
** File description:
** Test ComponentFactory
*/

#include <criterion/criterion.h>
#include <ComponentFactory.hpp>
#include <Components.hpp>

#define TEST_CREATE_HARDCODED_COMPONENT(typeName, className)                                                 \
    Test(CreateComponent, create##className)                                                                 \
    {                                                                                                        \
        nts::loadFactoryComponents("./components");                                                          \
        std::unique_ptr<nts::IComponent> component = std::make_unique<className>("ok");                      \
        cr_assert_str_eq(component->getType().c_str(), typeName);                                            \
        cr_assert_str_eq(component->getName().c_str(), "ok");                                                \
        cr_assert_eq(typeid(*component) == typeid(className), 1);                                            \
    }                                                                                                        \
    Test(CreateComponent, create##className##FromFactory)                                                    \
    {                                                                                                        \
        nts::loadFactoryComponents("./components");                                                          \
        std::unique_ptr<nts::IComponent> component = nts::ComponentFactory::createComponent(typeName, "ok"); \
        cr_assert_str_eq(component->getType().c_str(), typeName);                                            \
        cr_assert_str_eq(component->getName().c_str(), "ok");                                                \
        cr_assert_eq(typeid(*component) == typeid(className), 1);                                            \
    }
#define TEST_CREATE_COMPONENT(typeName)                                                                       \
    Test(CreateComponent, create##typeName##FromFactory)                                                      \
    {                                                                                                         \
        nts::loadFactoryComponents("./components");                                                           \
        std::unique_ptr<nts::IComponent> component = nts::ComponentFactory::createComponent(#typeName, "ok"); \
        cr_assert_str_eq(component->getType().c_str(), #typeName);                                            \
        cr_assert_str_eq(component->getName().c_str(), "ok");                                                 \
        cr_assert_eq(typeid(*component) == typeid(Circuit), 1);                                               \
    }

namespace nts
{
    // IOComponents
    // In
    TEST_CREATE_HARDCODED_COMPONENT("clock", Clock)
    TEST_CREATE_HARDCODED_COMPONENT("false", False)
    TEST_CREATE_HARDCODED_COMPONENT("input", Input)
    TEST_CREATE_HARDCODED_COMPONENT("true", True)
    // Out
    TEST_CREATE_HARDCODED_COMPONENT("output", Output)
    TEST_CREATE_HARDCODED_COMPONENT("logger", Logger)

    // LogicComponents
    // GateComponents
    TEST_CREATE_HARDCODED_COMPONENT("nand", Nand)

    TEST_CREATE_COMPONENT(and)
    TEST_CREATE_COMPONENT(or)
    TEST_CREATE_COMPONENT(xor)
    TEST_CREATE_COMPONENT(nor)
    TEST_CREATE_COMPONENT(nxor)

    TEST_CREATE_COMPONENT(4001)
    TEST_CREATE_COMPONENT(4011)
    TEST_CREATE_COMPONENT(4030)
    TEST_CREATE_COMPONENT(4069)
    TEST_CREATE_COMPONENT(4071)
    TEST_CREATE_COMPONENT(4081)

    TEST_CREATE_HARDCODED_COMPONENT("2716", C2716)
    TEST_CREATE_COMPONENT(4008)
    TEST_CREATE_COMPONENT(4013)
    TEST_CREATE_COMPONENT(4017)
    TEST_CREATE_COMPONENT(4040)
    TEST_CREATE_COMPONENT(4094)
    TEST_CREATE_COMPONENT(4512)
    TEST_CREATE_COMPONENT(4514)
    TEST_CREATE_HARDCODED_COMPONENT("4801", C4801)

    // LogicComponents

} // namespace nts