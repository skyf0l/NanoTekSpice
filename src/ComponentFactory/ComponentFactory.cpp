/*
** EPITECH PROJECT, 2021
** COMPONENTFACTORY
** File description:
** ComponentFactory class
*/

#include <regex>

#include <ComponentFactory.hpp>

namespace nts
{
    // init builtinComponentFactoryMap
    std::unordered_map<std::string, ComponentFactory::lambdaConstructorPrototype> ComponentFactory::builtinComponentFactoryMap({
        // IOComponents / In
        {"clock", LAMBDA_CONSTRUCTOR(Clock)},
        {"false", LAMBDA_CONSTRUCTOR(False)},
        {"input", LAMBDA_CONSTRUCTOR(Input)},
        {"true", LAMBDA_CONSTRUCTOR(True)},
        // IOComponents / Out
        {"output", LAMBDA_CONSTRUCTOR(Output)},
        {"logger", LAMBDA_CONSTRUCTOR(Logger)},

        // GateComponents
        {"nand", LAMBDA_CONSTRUCTOR(Nand)},
        {"tristate_core", LAMBDA_CONSTRUCTOR(Tristate_core)},

        // LogicComponents
        {"2716", LAMBDA_CONSTRUCTOR(C2716)},
        {"4801", LAMBDA_CONSTRUCTOR(C4801)},

        {"4040_core", LAMBDA_CONSTRUCTOR(C4040_core)},
        {"4094_core", LAMBDA_CONSTRUCTOR(C4094_core)},
    });

    // init componentFactoryMap
    std::unordered_map<std::string, std::string> ComponentFactory::blueprintPathComponentFactoryMap;
    std::unordered_map<std::string, Blueprint> ComponentFactory::blueprintComponentFactoryMap;

    void ComponentFactory::addComponentConstructor(const std::string type, const std::string path)
    {
        ComponentFactory::blueprintPathComponentFactoryMap[type] = path;
    }

    std::unique_ptr<IComponent> ComponentFactory::createComponent(const std::string &type, const std::string &name)
    {
        if (ComponentFactory::builtinComponentFactoryMap.find(type) != ComponentFactory::builtinComponentFactoryMap.end())
        {
            lambdaConstructorPrototype constructor = ComponentFactory::builtinComponentFactoryMap[type];
            return constructor(name);
        }

        if (ComponentFactory::blueprintPathComponentFactoryMap.find(type) == ComponentFactory::blueprintPathComponentFactoryMap.end())
            throw UnknownComponentException("Component \"" + type + "\" not exists");
        if (ComponentFactory::blueprintComponentFactoryMap.find(type) == ComponentFactory::blueprintComponentFactoryMap.end())
            generateBlueprint(type);
        if (ComponentFactory::blueprintComponentFactoryMap.find(type) == ComponentFactory::blueprintComponentFactoryMap.end())
            throw UnknownComponentException("Component \"" + type + "\" not exists");

        std::unique_ptr<Circuit> component = std::unique_ptr<Circuit>(new Circuit(name, type));
        ComponentFactory::blueprintComponentFactoryMap[type].loadBlueprint(component);
        return component;
    }

    void ComponentFactory::generateBlueprint(const std::string type)
    {
        try
        {
            Blueprint blueprint;
            Parser::LoadBlueprintFromFile(ComponentFactory::blueprintPathComponentFactoryMap[type], blueprint);
            ComponentFactory::blueprintComponentFactoryMap[type] = blueprint;
        }
        catch (const NtsException &ex)
        {
            throw GenerateBlueprintComponentFactoryException("Can not generate blueprint for " + type + " (" + ex.what() + ")");
        }
    }

} // namespace nts