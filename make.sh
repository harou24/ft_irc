#!/bin/bash

#configuration
BUILD_FOLDER="build"
SRC_FOLDER="src"
APPS_FOLDER="apps"
TESTS_FOLDER="tests/src"

display_info ()
{
    printf "\n\n*************** CPP HELPER ***************\n\n";
    echo "Commands available :";
    echo "  build              build the project";
    echo "  clean              clean build folder";
    echo "  test               run unitests";
    echo "  create             generate .cpp/.hpp files, generate cpp module";
    echo "  save               create a save branch and push on github";
    echo "  run                run executable in APPS_FOLDER";
}


create_cpp_header ()
{
    if [ $# -ne 1 ]; then
        echo "NB ARG ERROR";
    else
        echo "creating $1 ...";
        touch $1;
        echo -n "#ifndef " > $1; 
        echo  $1 | tr '[a-z]' '[A-Z]' | sed -E 's/[.]+/_/g'  >> $1;
        echo -n "# define " >> $1;
        echo -n $1 | tr '[a-z]' '[A-Z]' | sed -E 's/[.]+/_/g' >> $1;
        printf "\n\n\n\n\n\n\n\n\n\n\n" >> $1;
        echo "#endif" >> $1;
    fi
}

create_cpp_file ()
{
    echo "creating $1.cpp ...";
    touch "$1.cpp";
    echo -n "#include " > $1.cpp;
    echo -n '"' >> $1.cpp;
    echo -n "$1.hpp" >> $1.cpp;
    echo '"' >> $1.cpp;
}

create_cpp_module ()
{
    echo "creating module $1 ...";
    mkdir -p $SRC_FOLDER/$1;
    cd $SRC_FOLDER/$1/;
    create_cpp_header "$1.hpp";
    create_cpp_file $1;
}

create_cpp_test ()
{
    echo "creating test $1 in $TESTS_FOLDER";
    touch $TESTS_FOLDER/$1.cpp;
    echo "#include <catch2/catch.hpp>" > $TESTS_FOLDER/$1.cpp;
    printf "\n" >> $TESTS_FOLDER/$1.cpp;
    echo "TEST_CASE(\"your test\", \"[TEST]\")" >> $TESTS_FOLDER/$1.cpp;
    echo "{" >> $TESTS_FOLDER/$1.cpp;
    echo "  REQUIRE(42 == 42);" >> $TESTS_FOLDER/$1.cpp ;
    echo "}" >> $TESTS_FOLDER/$1.cpp;
}

run_cmake ()
{
    if [ "$1" == "build" ]; then
        mkdir -p $BUILD_FOLDER && cmake -S . -B $BUILD_FOLDER && cmake --$BUILD_FOLDER $BUILD_FOLDER;
    elif [ "$1" == "clean" ]; then
        git clean -d -f -X &&  rm -rf $BUILD_FOLDER;
    elif [ "$1" == "test" ]; then
        mkdir -p $BUILD_FOLDER &&
            cmake -S . -B $BUILD_FOLDER && 
            cmake --$BUILD_FOLDER $BUILD_FOLDER && 
            cd $BUILD_FOLDER && ctest --output-on-failure;
    fi
}

save ()
{
    BRANCH_EXIST=`git branch -a | grep save`;
    if [ BRANCH_EXIST == "" ]; then
        git add .;
        git commit -m "save";
        git branch save;
        git checkout save;
        git push --set-upstream origin save;
    else
        printf "You already have save branch :\n$BRANCH_EXIST\n";
        echo "Saving failed";
    fi
}

if [ $# -eq 1 ]; then
    if [ "$1" == "build" ] || [ "$1" == "clean" ] || [ "$1" == "test" ]; then
        run_cmake $1;
    elif [ "$1" == "-h" ] || [ "$1" == "-help" ]; then
        display_info
    elif [ "$1" == "save" ]; then
        save
    else
        echo "NB_ARG Error : build | clean | test | -h / --help\n";
    fi
elif [ $# -eq 2 ]; then
    if [ "$1" == "create" ]; then
        if [[ "$2" == *hpp ]] && [ ! -f $2 ]; then
            create_cpp_header $2;
        fi
    fi
elif [ $# -eq 3 ]; then
    if [ "$1" == "create" ]; then
        if [[ "$2" == "module" ]] && [ ! -d $2 ]; then
            create_cpp_module $3;
        elif [[ "$2" == "test" ]] && [ ! -d $TESTS_FOLDER/$2 ]; then
            create_cpp_test $3; 
        fi
    fi
else
    echo "NO ARGS ERROR\n  Run -> bash manager build | test | cleean\n" ;
fi

