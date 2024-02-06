#include "package.hpp"

pak_time_t::pak_time_t(BYTE month, BYTE day, WORD year)
: month(month), day(day), year(year){}
pak_time_t::pak_time_t(const pak_time_t& val)
: month(val.month), day(val.day), year(val.year){}
pak_module_t::pak_module_t(const std::string name, const std::vector<std::string>& depends, const FLAG load_deps)
: name(name), depends(depends), load_deps(load_deps){}
pak_module_t::pak_module_t(const pak_module_t& mod)
:name(mod.name), depends(mod.depends), load_deps(mod.load_deps){}
pak_metadata_t::pak_metadata_t(std::string dev_name, std::string vid, pak_time_t com_dev, std::string description)
: dev_name(dev_name), vid(vid), com_dev(com_dev), description(description){}
pak_t::pak_t(const pak_t& pak)
: pkgname(pak.pkgname), modules(pak.modules), metadate(pak.metadate), runtime_data(pak.runtime_data){}
pak_metadata_t::pak_metadata_t(const pak_metadata_t& meta)
: dev_name(meta.dev_name), vid(meta.vid), com_dev(meta.com_dev), description(meta.description){}
pak_t::pak_t(std::string pkgname, const std::vector<pak_module_t>& modules, pak_metadata_t metadate, std::string runtime_data)
:pkgname(pkgname), modules(modules), metadate(metadate), runtime_data(runtime_data){}