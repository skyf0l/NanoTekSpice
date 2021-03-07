/*
** EPITECH PROJECT, 2021
** ISHELL
** File description:
** IShell header
*/

#ifndef ISHELL_H_
#define ISHELL_H_

namespace nts
{
    class IShell
    {
    public:
        virtual ~IShell() = default;

        virtual int run() = 0;
    };
} // namespace nts

#endif /* !ISHELL_H_ */