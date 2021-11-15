#!/bin/bash

display_info ()
{
	printf "\n\n*************** CPP HELPER ***************\n\n";
	echo "Commands available :";
	echo "  build              build the project";
	echo "  clean              clean build folder";
	echo "  test               run unitests";
	echo "  create             generate .cpp/.hpp files, generate cpp module";
	echo "  save               create a save branch and push on github";
}


create_cpp_header ()
{
	if [ $# -ne 1 ]; then
		echo "NB ARG ERROR";
	else
		touch $1;
		echo "#ifndef ${1^^}" | sed -r 's/[.]+/_/g'  > $1;
		echo "# define ${1^^}" | sed -r 's/[.]+/_/g' >> $1;
		printf "\n\n\n\n\n\n\n\n\n\n\n" >> $1;
		echo "#endif" >> $1;
	fi
}

run_cmake ()
{

	if [ "$1" == "build" ]; then
    		mkdir -p build && cmake -S . -B build && cmake --build build;
	elif [ "$1" == "clean" ]; then
    		git clean -d -f -X &&  rm -rf build;
	elif [ "$1" == "test" ]; then
     		mkdir -p build &&
			cmake -S . -B build && 
			cmake --build build && 
			cd build && ctest --output-on-failure;

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
		echo "CMD NOT FOUND\n";
	fi
elif [ $# -eq 2 ]; then
	if [ "$1" == "create" ]; then
		if [[ "$2" == *hpp ]] && [ ! -f $2 ]; then
			create_cpp_header $2;
		fi
	fi
else
    echo "NO ARGS ERROR\n  Run -> bash manager build | test | cleean\n" ;
fi

