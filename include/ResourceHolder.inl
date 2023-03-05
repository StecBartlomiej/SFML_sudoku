#include "ResourceHolder.hpp"

template<typename Resource, typename Id>
void ResourceHolder<Resource, Id>::load(Id id, const std::string &path)
{
    std::unique_ptr<Resource> ptr(new Resource());
    if (!ptr->loadFromFile(path))
    {
        throw std::runtime_error("ResourceHolder::Load Failed to load a file " + path);
    }
    insertMap(id, std::move(ptr));
}

template<typename Resource, typename Id>
Resource& ResourceHolder<Resource, Id>::get(Id id)
{
    auto find = resourceMap_.find(id);
    assert(find != resourceMap_.end());
    return *find->second;
}

template<typename Resource, typename Id>
const Resource& ResourceHolder<Resource, Id>::get(Id id) const{
    return get(id);
}

template<typename Resource, typename Id>
template<typename Parameter>
void ResourceHolder<Resource, Id>::load(Id id, const std::string &path, const Parameter &parameter)
{
    std::unique_ptr<Resource> ptr(new Resource);
    if (!ptr->loadFromFile(path, parameter))
    {
        throw std::runtime_error("ResourceHolder::Load Failed to load a file " + path);
    }
    insertMap(id, std::move(ptr));
}

template<typename Resource, typename Id>
void ResourceHolder<Resource, Id>::insertMap(Id id, std::unique_ptr<Resource> ptr)
{
    auto iter = resourceMap_.insert(std::make_pair(id, std::move(ptr)));
    assert(iter.second);
}
