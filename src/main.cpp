/*
** EPITECH PROJECT, 2021
** MAIN
** File description:
** Main class
*/

#include <iostream>
#include <stdlib.h>
#include <string>

#include <NtsException.hpp>
#include <ComponentFactory.hpp>
#include <NanoTekSpice.hpp>
#include <Circuit.hpp>
#include <Parser.hpp>

#include <IShell.hpp>
#include <InteractiveShell.hpp>
#ifdef BONUS
#include <GraphicShell.hpp>
#endif

#ifndef TESTS_RUN
int main(int argc, char *const *argv)
{
    if (argc < 2 || argv[1] == std::string("-h") || argv[1] == std::string("--help"))
    {
        std::cout << HELP_MSG << std::endl;
        return 84;
    }

    std::unique_ptr<nts::IShell> shell;
    try
    {
        nts::loadFactoryComponents("./components");
#ifdef BONUS
        if ((argc >= 3 && std::string("-g") == argv[1]))
            shell = std::make_unique<nts::GraphicShell>(argv[2], &argv[3]);
        else
#endif
            shell = std::make_unique<nts::InteractiveShell>(argv[1], &argv[2]);
    }
    catch (nts::NtsException &e)
    {
        std::cout << e.what() << std::endl;
        return 84;
    }

    return shell->run();
}
#endif