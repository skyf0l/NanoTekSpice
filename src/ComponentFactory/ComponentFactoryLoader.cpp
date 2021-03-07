/*
** EPITECH PROJECT, 2021
** COMPONENTFACTORYLOADER
** File description:
** ComponentFactoryLoader class
*/

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/stat.h>
#include <dirent.h>
#endif

#include <ComponentFactory.hpp>

namespace nts
{
#ifdef _WIN32
    void loadFactoryComponents(std::string directoryPath)
    {
        WIN32_FIND_DATA fileData;
        HANDLE hFind = FindFirstFile((directoryPath + "\\*").c_str(), &fileData);

        if (hFind != INVALID_HANDLE_VALUE)
        {
            do
            {
                std::string name = fileData.cFileName;
                if (name == "." || name == "..")
                    continue;
                std::string path = directoryPath + "\\" + fileData.cFileName;
                if (GetFileAttributesA(path.c_str()) == FILE_ATTRIBUTE_DIRECTORY)
                    loadFactoryComponents(path);
                else
                    loadFactoryComponent(path);
            } while (FindNextFile(hFind, &fileData));
            FindClose(hFind);
        }
    }
#else
    static bool isRegularFile(std::string path)
    {
        struct stat path_stat;

        stat(path.c_str(), &path_stat);
        return S_ISREG(path_stat.st_mode);
    }

    void loadFactoryComponents(std::string directoryPath)
    {
        struct dirent *entry;
        DIR *dp;

        dp = opendir(directoryPath.c_str());
        if (dp == NULL)
            throw FactoryLoadingException("\"" + directoryPath + "\" does not exist or could not be read");

        while ((entry = readdir(dp)))
        {
            std::string name(entry->d_name);
            std::string path(directoryPath + "/" + name);

            if (name == "." || name == "..")
                continue;
            if (isRegularFile(path))
                loadFactoryComponent(path);
            else
                loadFactoryComponents(path);
        }
        closedir(dp);
    }
#endif

    void loadFactoryComponent(std::string path)
    {
        std::string type = Parser::getFileName(path);
        if (type == "")
            throw FactoryLoadingException("\"" + path + "\" is not a valid component file");
        ComponentFactory::addComponentConstructor(type, path);
    }

} // namespace nts