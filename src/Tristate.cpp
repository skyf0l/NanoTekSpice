/*
** EPITECH PROJECT, 2021
** TRISTATE
** File description:
** Tristate class
*/

#include <Tristate.hpp>

namespace nts
{
    Tristate operator&&(Tristate tristate1, Tristate tristate2)
    {
        if (tristate1 == UNDEFINED && tristate2 == UNDEFINED)
            return UNDEFINED;
        if (tristate1 == TRUE && tristate2 == TRUE)
            return TRUE;
        if ((tristate1 == TRUE || tristate2 == TRUE) && (tristate1 == UNDEFINED || tristate2 == UNDEFINED))
            return UNDEFINED;
        return FALSE;
    }

    Tristate operator||(Tristate tristate1, Tristate tristate2)
    {
        if (tristate1 == UNDEFINED && tristate2 == UNDEFINED)
            return UNDEFINED;
        if (tristate1 == TRUE || tristate2 == TRUE)
            return TRUE;
        if (tristate1 == UNDEFINED || tristate2 == UNDEFINED)
            return UNDEFINED;
        return FALSE;
    }

    Tristate operator^(Tristate tristate1, Tristate tristate2)
    {
        if (tristate1 == UNDEFINED || tristate2 == UNDEFINED)
            return UNDEFINED;
        if ((tristate1 == TRUE) ^ (tristate2 == TRUE))
            return TRUE;
        return FALSE;
    }

    Tristate operator!(Tristate tristate)
    {
        if (tristate == UNDEFINED)
            return UNDEFINED;
        if (tristate == TRUE)
            return FALSE;
        return TRUE;
    }

} // namespace nts