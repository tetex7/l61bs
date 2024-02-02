libfs={
    CWD = PWD
}


function libfs.list_files(dir)
    local df = l61.stringEx.split(exec(string.format("ls %s", dir)), "  \n")
    return df
end

function libfs.lfs_l(path)
    local f = fs.list_files(path)
    local files = ""
    local sep = ""
    for i = 1, l61.taplelen(f) do
        if fs.is_dir(path.."/"..f[i]) then
            files = files..sep..libfs.lfs(f[i])
        else
            files = files..sep..f[i]
        end
        sep = " "
    end
    return files
end

function libfs.lfl_l(dir)
    local df = l61.stringEx.split(libfs.lfs_l(dir), " ")
    return df
end


function libfs.lfs(path)
    local f = fs.list_files(path)
    local files = ""
    local sep = ""
    for i = 1, l61.taplelen(f) do
        if fs.is_dir(path.."/"..f[i]) then
            files = files..sep..libfs.lfs(path.."/"..f[i])
        else
            files = files..sep..path.."/"..f[i]
        end
        sep = " "
    end
    return files
end

function libfs.lfl(dir)
    local df = l61.stringEx.split(libfs.lfs(dir), " ")
    return df
end
