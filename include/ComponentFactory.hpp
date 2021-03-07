/*
** EPITECH PROJECT, 2021
** COMPONENTFACTORY
** File description:
** ComponentFactory header
*/

#ifndef COMPONENTFACTORY_H_
#define COMPONENTFACTORY_H_

#include <functional>
#include <unordered_map>

#include <Circuit.hpp>
#include <Components.hpp>
#include <Parser.hpp>
#include <NtsException.hpp>

#define LAMBDA_CONSTRUCTOR(className) [](const std::string &name) -> std::unique_ptr<IComponent> { return std::make_unique<className>(name); }

namespace nts
{
    class ComponentFactory
    {
    public:
        typedef std::function<std::unique_ptr<IComponent>(const std::string &name)> lambdaConstructorPrototype;

        static std::unordered_map<std::string, lambdaConstructorPrototype> builtinComponentFactoryMap;

        static std::unordered_map<std::string, std::string> blueprintPathComponentFactoryMap;
        static std::unordered_map<std::string, Blueprint> blueprintComponentFactoryMap;

        static void addComponentConstructor(const std::string type, const std::string path);

        static std::unique_ptr<IComponent> createComponent(const std::string &type, const std::string &name);
    
    protected:
        static void generateBlueprint(const std::string type);
    };

    void loadFactoryComponents(std::string directoryPath);
    void loadFactoryComponent(std::string path);

} // namespace nts

#endif /* !COMPONENTFACTORY_H_ */