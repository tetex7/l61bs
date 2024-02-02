--fs = libmount("libfs")
bash = libmount("libbash")
--l61 = libl61
gcc =  libmount("libgcc")


src_files = fs.lfl("./src")--list_files(PWD.."/src")
bin_files = fs.list_files(PWD.."/bin")

INC = "-I./include"

function main(argc, argv)
    if not fs.exists(PWD.."/bin") then
            exec("mkdir "..PWD.."/bin")
    end

    for i = 1, argc do
        print(argv[i])
    end
    gcc.form()
    for i = 1, l61.taplelen(src_files) do
        if string.find(src_files[i], ".cpp") then
            print(gcc.CXX.." "..INC.." ".." -c "..src_files[i].." -o ./bin/"..fs.raw_filename(src_files[i])..".o")
            exec(gcc.CXX.." "..INC.." ".." -c  "..src_files[i].." -o ./bin/"..fs.raw_filename(src_files[i])..".o")
        end
    end
    o_files = ""
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
