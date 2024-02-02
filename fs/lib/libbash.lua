libbash={}

function libbash.run(p)
    return exec(string.format("bash %s", p))
end