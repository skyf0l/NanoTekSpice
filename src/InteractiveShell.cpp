/*
** EPITECH PROJECT, 2021
** INTERACTIVESHELL
** File description:
** InteractiveShell class
*/

#include <iostream>
#include <signal.h>

#include <Parser.hpp>
#include <InteractiveShell.hpp>

namespace nts
{
    InteractiveShell::InteractiveShell(std::string path, char *const *raw_inputs)
    {
        _circuit = std::make_unique<Circuit>();

        Parser::LoadComponentsFromFile(path, _circuit);
        if (raw_inputs)
            _circuit->setRawInputs(raw_inputs);
    }

    InteractiveShell::~InteractiveShell()
    {
    }

    int is_sigint(int _state = -1)
    {
        static bool state = false;

        if (_state == 0)
            state = false;
        else if (_state == 1)
            state = true;
        return state;
    }

    void signal_handler(int signal)
    {
        if (signal == 2)
            is_sigint(true);
    }

    void InteractiveShell::loop()
    {
        signal(SIGINT, signal_handler);
        while (!is_sigint())
        {
            _circuit->simulate();
            _circuit->display();
        }
        signal(SIGINT, SIG_DFL);
        is_sigint(false);
    }

    int InteractiveShell::run()
    {

        std::string command;

        std::cout << "> ";
        while (std::getline(std::cin, command))
        {
            command = trim(command);
            if (command == "exit")
                return EXIT_SUCCESS;
            else if (command == "display" || command == "d")
                _circuit->display();
            else if (command == "simulate" || command == "s")
                _circuit->simulate();
            else if (command == "sd")
            {
                _circuit->simulate();
                _circuit->display();
            }
            else if (command == "loop" || command == "l")
                loop();
            else if (command == "dump")
                _circuit->dump();
            else if (!command.empty())
            {
                try
                {
                    _circuit->setRawInput(command);
                }
                catch (const InvalidInputCommandException &ex)
                {
                    std::cerr << "\"" << command << "\" is not a valid input command" << std::endl;
                }
                catch (const NtsException &ex)
                {
                    std::cerr << ex.what() << std::endl;
                }
            }
            std::cout << "> ";
        }
        return EXIT_SUCCESS;
    }

} // namespace nts