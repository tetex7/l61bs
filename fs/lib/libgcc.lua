libgcc = {}

libgcc.PRFIX = ""
libgcc.CC = string.format("%sgcc", libgcc.PRFIX)
libgcc.LD = string.format("%sld", libgcc.PRFIX)
libgcc.CXX = string.format("%sg++", libgcc.PRFIX)
libgcc.AS = string.format("%sAS", libgcc.PRFIX)

function libgcc.form()
    libgcc.CC = string.format("%sgcc", libgcc.PRFIX)
    libgcc.LD = string.format("%sld", libgcc.PRFIX)
    libgcc.CXX = string.format("%sg++", libgcc.PRFIX)
    libgcc.AS = string.format("%sAS", libgcc.PRFIX)
end