/*
** EPITECH PROJECT, 2021
** INTERACTIVESHELL
** File description:
** InteractiveShell header
*/

#ifndef INTERACTIVESHELL_H_
#define INTERACTIVESHELL_H_

#include <IShell.hpp>
#include <Circuit.hpp>

namespace nts
{
    class InteractiveShell : public IShell
    {
    public:
        InteractiveShell(std::string path, char *const *raw_inputs = nullptr);
        ~InteractiveShell() override;

        int run() override;

    protected:
        void loop();

        std::unique_ptr<Circuit> _circuit;
    };
} // namespace nts

#endif /* !INTERACTIVESHELL_H_ */