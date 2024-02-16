/*
l61 main code
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
#include <iostream>
#include "defs.h"
#include "vals.hpp"
#include "l61_runer.hpp"
#include "loader.hpp"
#include "fs.hpp"
#include "package.hpp"
#include "inputs.hpp"
//#include <absl/strings/string_view.h>
//absl::string_view s = "";



//#include <dpp/dispatcher.h>
l61_stat L61stat = l61_stat(luaL_newstate(), fs::current_path().string(), fs::current_path().string() + "/build.l61", "/opt/l61", getenv("USER"));
FLAG canTRUST = 0;
WORD sage = 0;
std::vector<std::string> spaths = {(L61stat.work_path + "/scripts"), ("/home/" + L61stat.user_name + "/l61_lib"), (L61stat.bin_path + "/lib")};
const size_t sp_size = spaths.size();

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

C_CALL int getLibPathStack(lua_State *L)
{
    createIntStrTable(L, spaths);
    return 1;
}


C_CALL int pushLibPath(lua_State *L)
{
    if (lua_isstring(L, -1))
    {
        std::string path = lua_tostring(L, -1);
        spaths.push_back(path);
        return 0;
    }
    return 0;
}

C_CALL int getLibPathAt(lua_State *L)
{
    if (lua_isinteger(L, -1))
    {
        int index = (int)lua_tointeger(L, -1);
        if (index == spaths.size())
        {
            lua_pushstring(L, spaths[index - 1].c_str());
            return 1;
        }
        return 0;
    }
    return 0;
}

C_CALL int getSizeLibPath(lua_State *L)
{
    lua_pushinteger(L, spaths.size());
    return 1;
}

C_CALL int peekLibPath(lua_State *L)
{
    /*if (lua_isstring(L, -1))
    {
        std::string path = lua_tostring(L, -1);
        spaths.push_back(path);
        return 0;
    }*/
    lua_pushstring(L, spaths[spaths.size() - 1].c_str());
    return 1;
}

C_CALL int str_to_int(lua_State *L)
{
    if (lua_isstring(L, -1))
    {
        std::string str = lua_tostring(L, -1);
        int o = std::stoi(str);
        lua_pushinteger(L, o);
        return 1;
    }
}

C_CALL int popLibPath(lua_State *L)
{
    if (spaths.size() != sp_size)
    {
        spaths.pop_back();
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

C_CALL int lget_input(lua_State *L)
{
    if (lua_isstring(L, -1))
    {
        std::string out = get_input(lua_tostring(L, -1));
        lua_pushstring(L, out.c_str());
        return 1;
    }
    std::string out = get_input();
    lua_pushstring(L, out.c_str());
    return 1;
}

C_CALL int mks(lua_State *L)
{
    setlocc(666);
    mk_segfault();
}

C_CALL void linit_env(lua_State *L)
{
    setlocc(400);
    luaL_openlibs(L);
    lua_mount_cfun(L, "mk_segfault", &mks);
    lua_def_bool(L, "DEBUG", 0);
    lua_def_string(L, "L61_VID", "2.2.0_dev");
    lua_newtable(L);
    lua_setglobal(L, "sys");
    lua_def_nil(L, "os");
    lua_mount_cfun(L, "str_to_int", &str_to_int);
    lua_mount_cfun(L, "input", &lget_input);
    lua_mount_cfun(L, "setExitCode", &lexit_setcode);
    lua_mount_cfun(L, "libmount", &load);
    lua_mount_cfun(L, "pak_mount", &lua_pak_mount);
    lua_mount_cfun(L, "lib_mount", &load);
    lua_mount_cfun(L, "pushLibPath", &pushLibPath);
    lua_mount_cfun(L, "getLibPathStack", &getLibPathStack);
    lua_mount_cfun(L, "getLibPathAt", &getLibPathAt);
    lua_mount_cfun(L, "getSizeLibPath", &getSizeLibPath);
    lua_mount_cfun(L, "peekLibPath", &peekLibPath);
    lua_mount_cfun(L, "popLibPath", &popLibPath);
    lua_def_nil(L, "require");
    lua_mount_cfun(L, "require", &load);
    lua_mount_cfun(L, "exec", &lua_exec); 
    lua_mount_cfun(L, "getdirR", &getdirR);
    lua_def_string(L, "PWD", L61stat.work_path.c_str());
    lua_libmount(L, "libl61", "l61");
    lua_libmount(L, "libfs", "fs");
    lua_libmount(L, "libcolor", "color");
    lua_libmount(L, "utils", "", 0);
    lua_def_table(L, "sys", "os");
    lua_def_bool(L, "allowMountTableError", 1);
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


lua_type_e lua_gettype(lua_State *L, int idx)
{
    return (lua_type_e)lua_type(L, idx);
}
using boost::program_options::unknown_option;

FLAG au = 0;

C_CALL void int_h(int sig)
{
    switch (sig)
    {
    case SIGINT:
        std::cout << "\n\nUwU\n\n";
        exit(0);
    case SIGSEGV:
        std::cout << "\n\n!!SEGFAULT!! :-(\n\ndumping L61stat@" << &L61stat << '\n';
        std::cout << L61stat << "\n\n";

        std::cout << "START OF SPATHS\n";
        for(const std::string& path : spaths)
        {
            std::cout << "  " << path << '\n';
        }
        std::cout << "END OF SPATHS\n\n";
        for (size_t i = 0; i < 400; i++);
        if (au || (getlocc() <= 10))
        {
            abort();
        }
        exit(134);
        return;
    case SIGQUIT:
        exit(0);
    default:
        break;
    }
    
}
int main(int argc, const char** argv)
{
    //std::unique_ptr<lua_State, getTypeOf(&lua_close)> lua(luaL_newstate(), lua_close);
    setlocc(120);
    atexit(bl61_exit);
    signal(SIGINT, int_h);
    signal(SIGSEGV, int_h);
    signal(SIGQUIT, int_h);

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
        ("log-mode", po::value<FLAG>(), "")
        ("can-root", "")
        ("ls", "")
        ("ad","")
        ("copyright", "")
    ;
__asm("L15:");
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

    if (vm.count("copyright"))
    {
        std::cout << COPY_STR << '\n';
        exit(0);
    }

    FLAG logm = 0;
    if (vm.count("ad"))
    {
        au = 1;
    }

    if (vm.count("log-mode")) {
        logm = vm["log-mode"].as<FLAG>();
    }

    std::cout << exec("bash " + L61stat.bin_path + "/KROM.sh " + STRex(((int)!logm)));

    if (vm.count("help")) {
        std::cout << desc << "\n";
        std::cout << REP_BUG_TEXT << "\n";
        return 0;
    }
    FLAG rt = 0;
    if (vm.count("can-root")) {
        rt = 1;
    }

    if ((L61stat.user_name == "root") && !rt)
    {
        std::cout << "\033[1;31m" <<  NO_ROOT_MEG << "\033[0m" << '\n';
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

    if (vm.count("ls")) {
        L61stat.make_file_path = L61stat.work_path + "/make.lua";
    }

    if (vm.count("log-mode")) {
        logm = vm["log-mode"].as<FLAG>();
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
    setlocc(142);
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
    setlocc(186);
    std::vector<std::string> arg_vet = {L61stat.make_file_path};
    linit_env(L61stat);
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
    luaT_mount_cfun(L61stat.L, "fs", "list_files_c", &fs_list_files);
    
    try
    {
        setlocc(160);
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
    }
    catch(const std::exception& e)
    {
        std::cout << "\n\n!!EXCEPTION!! :-(\n\ndumping L61stat@" << &L61stat << '\n';
        
        std::cout << L61stat << "\n\n";
        std::cout << "START OF SPATHS\n";
        for(const std::string& path : spaths)
        {
            std::cout << "  " << path << '\n';
        }
        std::cout << "END OF SPATHS\n\n";
        std::cout << "\nMSG:\n" << e.what() << "\n\n";
        for (size_t i = 0; i < 400; i++);
        if (au)
        {
            abort();
        }
        exit(134);
    }
ERROR:
    setlocc(7);
    if (lua_isstring(L61stat.L, -1))
    {
        std::cerr << "\nError loading Lua script: " << lua_tostring(L61stat.L, -1) << "\n\n";
        std::cout << "\a\a";
        return 55;
    }
    return exit_code;
}
