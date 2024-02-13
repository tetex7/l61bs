libcolor={}

local esc = string.char(27, 91)
libcolor.esc = esc
libcolor.NO_COL  = esc.."0m"
libcolor.RED     = esc.."0;31m"
libcolor.GREEN   = esc.."0;32m"
libcolor.BLUE    = esc.."0;34m"
libcolor.YELLOW  = esc.."0;33m"
libcolor.BLINK   = esc.."33;5m"
libcolor.MAGENTA = esc.."0;35m"