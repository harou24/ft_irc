if [ $# -eq 1 ] && [ "$1" == "build" ]; then
    mkdir -p build && cmake -S . -B build && cmake --build build && cp build/irc_server.exe .;
elif [ $# -eq 1 ] && [ "$1" == "clean" ]; then
    git clean -d -f -X &&  rm -rf build && rm -f irc_server.exe;
elif [ $# -eq 1 ] && [ "$1" == "test" ]; then
     mkdir -p build && cmake -S . -B build && cmake --build build && cd build && ctest --verbose;
else
    echo "NO ARGS ERROR\n  Run -> bash manager build | test | cleean\n" ;
fi
