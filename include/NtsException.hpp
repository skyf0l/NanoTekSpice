/*
** EPITECH PROJECT, 2021
** NTSEXCEPTION
** File description:
** NtsException header
*/

#ifndef NTSEXCEPTION_H_
#define NTSEXCEPTION_H_

#include <string>

#define NEW_EXCEPTION(name)                                                        \
    class name : public NtsException                                               \
    {                                                                              \
    public:                                                                        \
        name(std::string const &message, std::string const &type = #name) noexcept \
            : NtsException(message, type) {}                                       \
    };

namespace nts
{
    class NtsException : public std::exception
    {
    public:
        NtsException(std::string const &message, std::string const &type = "Unknown") noexcept
        {
            _message = message;
            _type = type;
        }

        std::string const &getType() const { return _type; }
        const char *what() const noexcept override { return _message.c_str(); }

    private:
        std::string _message;
        std::string _type;
    };

    // factory
    NEW_EXCEPTION(FactoryLoadingException)
    NEW_EXCEPTION(GenerateBlueprintComponentFactoryException)

    // shell command
    NEW_EXCEPTION(InvalidCommandException)
    NEW_EXCEPTION(InvalidInputCommandException)
    NEW_EXCEPTION(InvalidValueException)

    // parsing
    NEW_EXCEPTION(InvalidFileException)

    NEW_EXCEPTION(MissingSectionException)
    NEW_EXCEPTION(InvalidSectionException)
    NEW_EXCEPTION(UnknownSectionException)
    NEW_EXCEPTION(InvalidLineException)
    NEW_EXCEPTION(InvalidCircuitIOComponentException)

    // circuit
    NEW_EXCEPTION(UnusedMethodException)

    NEW_EXCEPTION(UnknownComponentException)
    NEW_EXCEPTION(UnknownNameException)

    NEW_EXCEPTION(InvalidComponentNameException)
    NEW_EXCEPTION(InvalidPinException)
    NEW_EXCEPTION(InvalidLinkException)

    NEW_EXCEPTION(IntputException)
    NEW_EXCEPTION(OutputException)

    // rom
    NEW_EXCEPTION(InvalidRomFileException)

    // graphic shell
    NEW_EXCEPTION(AssetLoadingException)


} // namespace nts

#endif /* !NTSEXCEPTION_H_ */