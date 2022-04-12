#pragma once

#include <string>
#include <map>


template<class TKey, class TBaseClass>
class Factory
{
    using TConstructorFunction = TBaseClass* (*)();
    
public:
    bool IsRegistered(const TKey& identifier) const
    {
        return m_Elements.find(identifier) != m_Elements.end();
    }

    bool Register(const TKey& identifier, TConstructorFunction constructor)
    {
        auto it = m_Elements.find(identifier);

        if (it == m_Elements.end())
        {
            m_Elements.emplace(identifier, constructor);
            return true;
        }

        return false;
    }

    bool Unregister(const TKey& identifier)
    {
        auto it = m_Elements.find(identifier);
        
        if (it != m_Elements.end())
        {
            m_Elements.erase(it);
            return true;
        }

        return false;
    }

    TBaseClass* NewInstance(const TKey& identifier)
    {
        auto it = m_Elements.find(identifier);

        if (it != m_Elements.end())
        {
            return (*it).operator();
        }

        return nullptr;
    }

    const std::map<TKey, TConstructorFunction>& GetElements() const { return m_Elements; }

private:
    std::map<TKey, TConstructorFunction> m_Elements;
};