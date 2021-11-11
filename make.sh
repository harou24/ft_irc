if [ $# -eq 1 ] && [ "$1" == "build" ]; then
    mkdir -p build && cmake -S . -B build && cmake --build build;
elif [ $# -eq 1 ] && [ "$1" == "clean" ]; then
    git clean -d -f -X &&  rm -rf build;
elif [ $# -eq 1 ] && [ "$1" == "test" ]; then
     mkdir -p build && cmake -S . -B build && cmake --build build && cd build && ctest --output-on-failure;
else
    echo "NO ARGS ERROR\n  Run -> bash manager build | test | cleean\n" ;
fi
