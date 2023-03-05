#ifndef SFML_DESIGN_RESOURCEHOLDER_HPP
#define SFML_DESIGN_RESOURCEHOLDER_HPP

#include <unordered_map>
#include <memory>
#include <cassert>
#include <exception>

#include "SFML/Graphics.hpp"

template<typename Resource, typename Id>
class ResourceHolder
{
public:
    void load(Id id, const std::string &path);

    template<typename Parameter>
    void load(Id id, const std::string &path, const Parameter &parameter);

    Resource& get(Id id);
    const Resource& get(Id id) const;

private:
    void insertMap(Id id, std::unique_ptr<Resource> ptr);

private:
    std::unordered_map<Id, std::unique_ptr<Resource>> resourceMap_;
};

#include "ResourceHolder.inl"

#endif //SFML_DESIGN_RESOURCEHOLDER_HPP
