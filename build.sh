
isTest=false

if [ "$1" = "-t" ] || [ "$2" = "-t" ]; then
	isTest=true
fi

isValgrind=false
if [ "$1" = "-mem" ] || [ "$2" = "-mem" ] ; then
	isValgrind=true
fi

appendPrefix() {
	local array_name="$1[@]"
	local input_array=("${!array_name}")
	local prefix="$2"
	local new_array=()

	for element in "${input_array[@]}"; do
		new_array+=("${prefix}${element}")
	done

	echo "${new_array[@]}"
}

#tpdbPath="./external/tpdb/"
#tpdbC=("utils.c" "log.c" "storage.c" "tableData.c" "table.c")
#tpdbRelative=$(appendPrefix "tpdbC" "${tpdbPath}")

ErrorsPath="./src/Errors/"
ErrorsC=("I_Errors.c")
ErrorsRelative=$(appendPrefix "ErrorsC" "${ErrorsPath}")

InterfacePath="./src/Interface/"
InterfaceC=("I_Database.c" "I_Row.c" "I_Table.c")
InterfaceRelative=$(appendPrefix "InterfaceC" "${InterfacePath}")

completeCPaths=($ErrorsRelative $InterfaceRelative)

projectRunC="./src/"
runPath="./build/"

if [ $isTest = true ]; then
	echo "Building Unit tests executable"
	projectRunC+="Tests/UnitTests.c"
	runPath+="test"
else
	echo "Building executable"
	projectRunC+="main.c"
	runPath+="run"
fi

#echo "${projectRunC} ${completeCPaths[@]}"
#gcc $projectRunC -o $runPath
gcc $projectRunC "${completeCPaths[@]}" -o $runPath

if [ $isValgrind = true ]; then
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --read-inline-info=yes -s $runPath
else
	$runPath
fi