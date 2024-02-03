--fs = libmount("libfs")
bash = libmount("libbash")
--l61 = libl61
gcc =  libmount("libgcc")


src_files = fs.lfl("./src")--list_files(PWD.."/src")

INC = "-I./include"

function main(argc, argv)
    if argc == 2 then
        if argv[2] == "clean" then
            fs.delet(PWD.."/bin")
            l61.exit(0)
        end
    end


    if not fs.exists(PWD.."/bin") then
            fs.mkdir(PWD.."/bin")
    end
    for i = 1, argc do
        print(argv[i])
    end

    gcc.form()
    for i = 1, l61.taplelen(src_files) do
        if fs.getEx(src_files[i]) == ".cpp" then--string.find(, ".cpp") then
            print(gcc.CXX.." "..INC.." ".." -c "..src_files[i].." -o ./bin/"..fs.raw_filename(src_files[i])..".cpp.o")
            exec(gcc.CXX.." "..INC.." ".." -c  "..src_files[i].." -o ./bin/"..fs.raw_filename(src_files[i])..".cpp.o")
        end
    end
    local bin_files = fs.list_files(PWD.."/bin")
    local o_files = ""
    for i = 1, l61.taplelen(bin_files) do
        if string.find(bin_files[i], ".o") then
            print(bin_files[i])
           o_files = o_files.." ./bin/"..bin_files[i]
        end
    end
    print(gcc.CXX..o_files.." -o ./test")
    exec(gcc.CXX..o_files.." -o ./test")
    return 69
end
