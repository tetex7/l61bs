#include <iostream>
#include "defs.h"
#include "vals.hpp"
#include "l61_runer.hpp"
#include "loader.hpp"
#include "fs.hpp"

namespace po = boost::program_options;
//#include <dpp/dispatcher.h>
l61_stat L61stat = l61_stat(luaL_newstate(), fs::current_path().string(), fs::current_path().string() + "/make.lua", "/opt/l61", getenv("USER"));

int exit_code = 0;
C_CALL int lexit_setcode(lua_State *L)
{
    if (lua_isinteger(L, -1))
    {
        exit_code = lua_tointeger(L, -1);
        return 0;
    }
    return 0;
}

C_CALL int lexit(lua_State *L)
{
    if (lua_isinteger(L, -1))
    {
        int exitcode = lua_tointeger(L, -1);
        exit(exitcode);
    }
    else
    {
        exit(0);
    }
    return 0;
}

C_CALL void linit_env(lua_State *L)
{
    luaL_openlibs(L);
    lua_def_bool(L, "DEBUG", 0);
    lua_def_string(L61stat.L, "L61_VID", "2.2.0_dev");
    lua_newtable(L61stat.L);
    lua_setglobal(L61stat.L, "sys");
    lua_def_nil(L, "os");
    lua_mount_cfun(L, "setExitCode", &lexit_setcode);
    lua_mount_cfun(L, "libmount", &load);
    lua_mount_cfun(L, "lib_mount", &load);
    lua_def_nil(L, "require");
    lua_mount_cfun(L, "require", &load);
    //luaL_dostring(L, "function require(name) return libmount(name) end");
    lua_mount_cfun(L, "exec", &lua_exec); 
    lua_mount_cfun(L, "getdirR", &getdirR);
    lua_def_string(L, "PWD", L61stat.work_path.c_str());
    lua_libmount(L, "libl61", "l61");
    lua_libmount(L, "libfs", "fs");
    lua_def_table(L, "sys", "os");

}

//std::unique_ptr<BYTE, getTypeOf(&free)> buff = std::unique_ptr<BYTE, getTypeOf(&free)>(malloc(sizeof(BYTE) * 850), &free);
/*std::array<BYTE, 850> buff = run<std::array<BYTE, 850>>([&](){
    std::array<BYTE, 850> f = std::array<BYTE, 850>();
    for (BYTE& v : f)
    {
        v = 256;
    }
    return f;
});//std::array<BYTE, 850>();*/
std::vector<VOID_FPTR> exit_funs;

C_CALL void bl61_exit()
{
    if(exit_funs.empty())
    {
        goto eL1;
    } 
    for(VOID_FPTR v : exit_funs)
    {
        v();
    }
eL1:
    if (L61stat.L != NULL)
    {
        lua_close(L61stat.L);
        L61stat.L = NULL;
        goto sip_stat;
    }
sip_stat:
    return;
}

lua_type_e lua_gettype(lua_State *L, int idx)
{
    return (lua_type_e)lua_type(L, idx);
}
using boost::program_options::unknown_option;

int main(int argc, const char** argv)
{
    //std::unique_ptr<lua_State, getTypeOf(&lua_close)> lua(luaL_newstate(), lua_close);
    atexit(bl61_exit);
    const char* exe_path_str = argv[0];
    //std::cout << "user: " << L61stat.user_name << "\n";
    
    //L61stat.bin_path = install_path;
    //std::cout << L61stat.bin_path << '\n';
    std::string start_file = "main.lua";
    po::options_description desc("the λ61 build system cls options");
    desc.add_options()
        ("help-fs", "")
        ("help,h", "produce help message")
        ("init", "init's the cwd")
        ("dir,d", po::value<std::string>(), "cha the dir")
        ("mainl,l", po::value<std::string>(), "the start lua file")
        ("argv,a", po::value<std::string>(), "biled lua args (RIP)")
        ("log-mode", po::value<FLAG>(), "biled lua args (RIP)")
        ("can-root", po::value<FLAG>(), "")
    ;
    

    po::variables_map vm;
    try
    {
        
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);  
    }
    catch(const unknown_option& e)
    {
        std::cerr << e.what() << '\n';
        exit(1);
    }

    FLAG logm = 0;

    if (vm.count("log-mode")) {
        logm = vm["log-mode"].as<FLAG>();
    }

    std::cout << exec("bash " + L61stat.bin_path + "/KROM.sh " + STRex(((int)!logm)));

    if (vm.count("help")) {
        std::cout << desc << "\n";
        std::cout << REP_BUG_TEXT << "\n";
        return 0;
    }

    if ((L61stat.user_name == "root") && !vm.count("can-root"))
    {
        std::cout << NO_ROOT_MEG << '\n';
        exit(45);
    }

    if (vm.count("init")) 
    {
        //fs::copy_directory(L61stat.bin_path + "/prefrom_l61", L61stat.work_path);
        //fs::create_directory(L61stat.work_path, L61stat.bin_path + "/prefrom_l61");
        //exec("cp -ra " + L61stat.bin_path + "/prefrom_l61 " + L61stat.work_path);
        //if (fs::exists(L61stat.make_file_path))
        //{
        try
        {
            std::filesystem::copy(L61stat.bin_path + "/prefrom_l61", L61stat.work_path, std::filesystem::copy_options::recursive);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            return 55;
        }
        //}
        //std::cout << "cp -ra " + L61stat.bin_path + "/prefrom_l61 " + L61stat.work_path;
        return 0;
    }

    if (vm.count("mainl"))
    {
        start_file = vm["mainl"].as<std::string>();
    }

    if (vm.count("dir"))
    {
        std::cout << "[l61/C] seting l61's cwd dir to " << vm["dir"].as<std::string>() << ".\n";
        L61stat.work_path = vm["dir"].as<std::string>();
        L61stat.make_file_path = L61stat.work_path + "/" + start_file;
        std::cout << "[l61/C] l61's cwd is" << L61stat.make_file_path << ".\n";
    }

    std::vector<std::string> lua_arg = {L61stat.make_file_path};
    if (vm.count("argv")) 
    {
        lua_arg = splitString(vm["argv"].as<std::string>());

    }

    std::string title = "λ61 on " + L61stat.make_file_path;
    std::cout << "\033]0;" << title << "\007";

    /*if (vm.count("compression")) {
        std::cout << "Compression level was set to " << vm["compression"].as<int>() << ".\n";
    } else {
        std::cout << "Compression level was not set.\n";
    }*/

    //std::cout << exec("ls /");
    //char buffer[PATH_MAX];
    /*ssize_t len = readlink("/proc/self/exe", buffer, strlen(buffer)); 
    getcwd(buffer, sizeof(buffer));*/
    std::vector<std::string> arg_vet = {L61stat.make_file_path};
    linit_env(L61stat.L);
    lua_getglobal(L61stat.L, "l61");
    if(lua_istable(L61stat.L, -1))
    {
        lua_pushcfunction(L61stat.L, &libl61_taplelen);
        lua_setfield(L61stat.L, -2, "taplelen");
        
    }
    else
    {
        goto ERROR;
    }
    for (std::string& arg : lua_arg)
    {
        arg_vet.push_back(arg);
    }

    

    lua_getglobal(L61stat.L, "sys");
    if(lua_istable(L61stat.L, -1))
    {
        lua_pushinteger(L61stat.L, arg_vet.size());
        lua_setfield(L61stat.L, -2, "argc");
        lua_getglobal(L61stat.L, "sys");
        createIntStrTable(L61stat.L, arg_vet);
        lua_setfield(L61stat.L, -2, "argv");
        
    }
    else
    {
        goto ERROR;
    }
    
    /*createIntStrTable(L61stat.L, arg_vet);
    lua_setglobal(L61stat.L, "argv");
    lua_def_int(L61stat.L, "argc", arg_vet.size());*/
    

    lua_getglobal(L61stat.L, "sys");
    if(lua_istable(L61stat.L, -1))
    {
        lua_getglobal(L61stat.L, "fs");
        lua_setfield(L61stat.L, -2, "fs");
        
    }
    else
    {
        goto ERROR;
    }


    lua_getglobal(L61stat.L, "sys");
    if(lua_istable(L61stat.L, -1))
    {
        lua_pushstring(L61stat.L, L61stat.user_name.c_str());
        lua_setfield(L61stat.L, -2, "user");
        
    }
    else
    {
        goto ERROR;
    }


    lua_getglobal(L61stat.L, "sys");
    if(lua_istable(L61stat.L, -1))
    {
        lua_getglobal(L61stat.L, "l61");
        lua_setfield(L61stat.L, -2, "l61");
        
    }
    else
    {
        goto ERROR;
    }

    lua_getglobal(L61stat.L, "l61");
    if(lua_istable(L61stat.L, -1))
    {
        lua_pushcfunction(L61stat.L, &lexit);
        lua_setfield(L61stat.L, -2, "exit");
        
    }
    else
    {
        goto ERROR;
    }



    lua_getglobal(L61stat.L, "sys");
    if(lua_istable(L61stat.L, -1))
    {
        lua_pushcfunction(L61stat.L, &lexit);
        lua_setfield(L61stat.L, -2, "exit");
        
    }
    else
    {
        goto ERROR;
    }

    luaT_mount_cfun(L61stat.L, "fs", "mkdir", &fs_mkdir);
    luaT_mount_cfun(L61stat.L, "fs", "delet", &fs_delet);
    luaT_mount_cfun(L61stat.L, "fs", "exists", &fs_exists);
    luaT_mount_cfun(L61stat.L, "fs", "is_dir", &fs_is_dir);
    luaT_mount_cfun(L61stat.L, "fs", "getEx", &fs_getEx);
    luaT_mount_cfun(L61stat.L, "fs", "copy", &fs_copy);
    luaT_mount_cfun(L61stat.L, "fs", "copyr", &fs_copyr);
    luaT_mount_cfun(L61stat.L, "fs", "raw_filename", &fs_rfilename);


    if (luaL_dofile(L61stat.L, L61stat.make_file_path.c_str()) != LUA_OK) {
        std::cerr << "Error loading Lua script: " << lua_tostring(L61stat.L, -1) << "\n";
        return 1;
    }
    else
    {
        if (luaL_dofile(L61stat.L, (L61stat.bin_path + "/boot.lua").c_str()) != LUA_OK) {
            std::cerr << "Error loading Lua script: " << lua_tostring(L61stat.L, -1) << "\n";
            return 1;
        }

        /*lua_getglobal(L61stat.L, "main"); // get the function on the stack
        if (lua_isfunction(L61stat.L, -1)) { 
            std::cout << "[λ61/C++] Runing main\n";
            lua_pcall(L61stat.L, 0, 0, 0); // now call the function
        } else { 
            std::cout << "[λ61/C] Error: didn't find a main function on top of Lua stack\n";
        }*/
        lua_getglobal(L61stat.L, "boot"); // get the function on the stack
        if (lua_isfunction(L61stat.L, -1)) { 
            std::cout << "[λ61/C++] Runing boot\n";
            lua_pcall(L61stat.L, 0, 0, 0); // now call the function
        } else { 
            std::cout << "[λ61/C] Error: didn't find a boot function on top of Lua stack\n";
        }
        
    }
ERROR:
    if (lua_isstring(L61stat.L, -1))
    {
        std::cerr << "\nError loading Lua script: " << lua_tostring(L61stat.L, -1) << "\n\n";
        std::cout << "\a\a";
        return 55;
    }
    std::cout << '\a';
    return exit_code;
}