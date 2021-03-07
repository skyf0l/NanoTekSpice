/*
** EPITECH PROJECT, 2021
** TRISTATE
** File description:
** Tristate header
*/

#ifndef TRISTATE_H_
#define TRISTATE_H_

#ifdef BONUS
#include <SFML/Graphics.hpp>
#endif

#include <NtsException.hpp>

// undef TRUE and FALSE in already exists (vs projects)
#ifdef TRUE
#undef TRUE
#endif
#ifdef FALSE
#undef FALSE
#endif

#define U UNDEFINED
#define T TRUE
#define F FALSE

namespace nts
{
    enum Tristate
    {
        UNDEFINED = -1,
        TRUE = true,
        FALSE = false
    };

    Tristate operator&&(Tristate tristate1, Tristate tristate2);
    Tristate operator||(Tristate tristate1, Tristate tristate2);
    Tristate operator^(Tristate tristate1, Tristate tristate2);
    Tristate operator!(Tristate tristate);

    static inline std::string tristateToString(Tristate tristate)
    {
        switch (tristate)
        {
        case UNDEFINED:
            return "U";
        case TRUE:
            return "1";
        case FALSE:
            return "0";
        default:
            return "?";
        }
    }

    static inline Tristate stringToTristate(std::string str)
    {
        if (str == "1")
            return TRUE;
        else if (str == "0")
            return FALSE;
        else if (str == "U")
            return UNDEFINED;
        else
            throw InvalidValueException("\"" + str + "\" is not a valid value");
    }

#ifdef BONUS
    static inline sf::Color tristateToColor(Tristate tristate)
    {
        switch (tristate)
        {
        case UNDEFINED:
            return sf::Color::Red;
        case TRUE:
            return sf::Color::Blue;
        case FALSE:
            return sf::Color::White;
        default:
            return sf::Color::Magenta;
        }
    }
#endif

} // namespace nts

#endif /* !TRISTATE_H_ */