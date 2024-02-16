/*
l61 pak code
Copyright (C) 2024  tete

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "package.hpp"
#include <fstream>

pak_time_t::pak_time_t(BYTE month, BYTE day, WORD year)
: month(month), day(day), year(year){}
pak_time_t::pak_time_t(const pak_time_t& val)
: month(val.month), day(val.day), year(val.year){}
/*pak_module_t::pak_module_t(const std::string name, const std::vector<std::string>& depends, FLAG main_mod, const FLAG load_deps)
: name(name), depends(depends), load_deps(load_deps){}
pak_module_t::pak_module_t(const pak_module_t& mod)
:name(mod.name), depends(mod.depends), main_mod(mod.main_mod), load_deps(mod.load_deps){}*/
pak_metadata_t::pak_metadata_t(std::string dev_name, std::string vid, pak_time_t com_dev, std::string description)
: dev_name(dev_name), vid(vid), com_dev(com_dev), description(description){}
pak_t::pak_t(const pak_t& pak)
: pkgname(pak.pkgname), metadata(pak.metadata), depends(pak.depends), runtime_data(pak.runtime_data){}
pak_metadata_t::pak_metadata_t(const pak_metadata_t& meta)
: dev_name(meta.dev_name), vid(meta.vid), com_dev(meta.com_dev), description(meta.description){}
pak_t::pak_t(std::string pkgname, pak_metadata_t metadata, const std::vector<std::string>& depends, std::string runtime_data)
:pkgname(pkgname), metadata(metadata), depends(depends), runtime_data(runtime_data){}

using nlohmann::json;

std::pair<pak_t, std::string> getPakData(std::string pak_name)
{
    for (const std::string path : spaths)
    {
        if (fs::exists(path + "/" + pak_name + "/pak.json"))
        {
            pak_t s  = pak_t(STR_NULL, pak_metadata_t(STR_NULL, STR_NULL, pak_time_t(0,0,0), STR_NULL), std::vector<std::string>(), STR_NULL);
            json pal;
            std::fstream(path + "/" + pak_name + "/pak.json") >> pal;
            from_json(pal, s);
            return std::pair(s, path + "/" + pak_name);
        }
    }
    return std::pair(pak_t(STR_NULL, pak_metadata_t(STR_NULL, STR_NULL, pak_time_t(0,0,0), STR_NULL), std::vector<std::string>(), STR_NULL), STR_NULL);
}

C_CALL int lua_pak_mount(lua_State* L)
{
    if (!lua_isstring(L, -1))
    {
        std::cout << "[l61/C] input is not string\n";
    }
    std::string pak_name = lua_tostring(L, -1);
    lua_newtable(L);
    int index = lua_gettop(L);

    auto pd = getPakData(pak_name);
    std::filesystem::path mods = pd.second;
    pak_t d = pd.first;
    for(const auto& _dir : std::filesystem::directory_iterator{mods})
    {
        std::filesystem::path dir = _dir.path();
        std::cout << dir << '\n';
        if(dir.extension() == ".lua")
        {
            std::string lname = (pd.second + "/" + fs::basename(dir.string()) + fs::extension(dir.string()));
            std::string load_n = fs::basename(dir.string());
            if (luaL_dofile(L, lname.c_str()))
            {
                lua_getglobal(L, load_n.c_str());
                if(!lua_istable(L61stat.L, -1))
                {
                    continue;
                }
                lua_setfield(L61stat.L, -2, load_n.c_str());
                lua_pop(L, -1);
            }
        }
    }
    return 1;
}