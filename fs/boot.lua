function boot()
    print("[λ61/LUA] Runing main\n")
    exit_code = main(sys.argc, sys.argv)
    setExitCode(exit_code)
end