#pragma once
#ifndef PACK_HPP
#define PACK_HPP
#include "vals.hpp"

struct pak_time_t
{
    BYTE month;
    BYTE day;
    WORD year;
    pak_time_t(BYTE month, BYTE day, WORD year);
    pak_time_t(const pak_time_t& val);
    __inline pak_time_t operator=(pak_time_t& val)
    {
        return pak_time_t(val);
    }
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(pak_time_t, month, day, year);
};



struct pak_module_t
{
    std::string name;
    std::vector<std::string> depends;
    FLAG load_deps;
    pak_module_t(const pak_module_t& mod);
    __inline pak_module_t operator=(pak_module_t& val)
    {
        return pak_module_t(val);
    }
    pak_module_t(const std::string name, const std::vector<std::string>& depends, const FLAG load_deps);
    
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(pak_module_t, name, depends, load_deps);

struct pak_metadata_t
{
    std::string dev_name;
    std::string vid;
    pak_time_t com_dev;
    std::string description;
    pak_metadata_t(const pak_metadata_t& meta);
    __inline pak_metadata_t operator=(pak_metadata_t& val)
    {
        return pak_metadata_t(val);
    }
    pak_metadata_t(std::string dev_name, std::string vid, pak_time_t com_dev, std::string description);
    
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(pak_metadata_t, dev_name, vid, com_dev, description);

// partial specialization (full specialization works too)
namespace nlohmann {
    template <>
    struct adl_serializer<std::vector<pak_module_t>> {
        static void to_json(json& j, const std::vector<pak_module_t>& vet) {
            
        }

        static void from_json(const json& j, std::vector<pak_module_t>& vet) {
            for(const auto& data : j)
            {
                pak_module_t __d = pak_module_t("", std::vector<std::string>(), 0);
                ::from_json(data, __d);
                vet.push_back(__d);
            }
        }
    };
}

struct pak_t
{
    std::string pkgname;
    std::vector<pak_module_t> modules;
    pak_metadata_t metadate;
    std::string runtime_data; // ask Tete
    pak_t(std::string pkgname, const std::vector<pak_module_t>& modules, pak_metadata_t metadate, std::string runtime_data = "");
    pak_t(const pak_t& pak);
    __inline pak_t operator=(pak_t& val)
    {
        return pak_t(val);
    }
    
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(pak_t, pkgname, modules, metadate, runtime_data);

C_CALL int lua_pak_mount(lua_State* L);

#endif