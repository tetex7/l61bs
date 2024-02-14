---comment
---@param lang string
---@param obj string
---@return string
function pre_comp_print(primp, lang, obj)
    return color.GREEN..primp..": "..color.YELLOW..lang..color.GREEN.." -> "..color.BLUE..obj..color.NO_COL
end

---comment
---@param lang string
---@param obj string
function comp_print(primp, lang, obj)
    print(pre_comp_print(primp, lang, obj))
end