#!/bin/bash

DIR_COUNT=0
FILE_COUNT=0
LINK_COUNT=0
COMPUTED_FILES=()


main_loop(){
	while read -r LINE
	do
		if [[ ${LINE} == "FILE "* ]]; then

			FILE_PATH=$(realpath ${LINE:5:${#LINE}})
			process_data

		fi

	done

	write_result
}

process_data(){
	if [ -d ${FILE_PATH} ]; then #directory
		((DIR_COUNT++))

		if [ ${COUNTING} ]; then
			echo "DIR ${DIR_COUNT} '${FILE_PATH}'"
		else
			echo "DIR '${FILE_PATH}'"
		fi
	elif [ -L ${FILE_PATH} ]; then #sym link
		((LINK_COUNT++))

		LINK_DESTINATION=$(readlink -f ${FILE_PATH})

		if [ ${COUNTING} ]; then
			echo "LINK ${LINK_COUNT} '${FILE_PATH}' '${LINK_DESTINATION}'"
		else
			echo "LINK '${FILE_PATH}' '${LINK_DESTINATION}'"
		fi
	elif [ -f ${FILE_PATH} ]; then #file
		COMPUTED_FILES+=("${FILE_PATH}")
		((FILE_COUNT++))

		LINE_COUNT=$(wc -l < ${FILE_PATH})
		FIRST_LINE=$(head -n 1 ${FILE_PATH})

		if [ ${COUNTING} ]; then
			echo "FILE ${FILE_COUNT} '${FILE_PATH}' ${LINE_COUNT} '${FIRST_LINE}'"
		else
			echo "FILE '${FILE_PATH}' ${LINE_COUNT} '${FIRST_LINE}'"
		fi
	else
		echo "ERROR '${FILE_PATH}'"
	fi
}

write_manual(){
	echo "Script usage:"
	echo "`basename $0` [-h] [-v] [-z] [-n]"
	echo "-h shows this man page"
	echo "-v at the end of the run it will list the number of valid files, directories and links (in this order and one per line)"
	echo "-z at the end, packs all valid files (not symlinks) into the .tar.gz archive named 'output.tgz'"
	echo "-n changes the output format so that the current number of files (order) is entered between the FILE / DIR / LINK string and the path. directories / symlinks (each type is numbered separately)"
	exit 0
}

write_result(){
	if [ ${WRITE_SUMMARY} ]; then
		echo ${FILE_COUNT}
		echo ${DIR_COUNT}
		echo ${LINK_COUNT}
	fi

	if [ ${MAKE_ARCHIVE} ]; then
		tar -czf output.tgz ${COMPUTED_FILES[@]}
	fi
	exit 0
}

while getopts ":hvzn" opt; do
	case $opt in
		h) write_manual
			;;
		v) WRITE_SUMMARY=true
			;;
		z) MAKE_ARCHIVE=true
			;;
		n) COUNTING=true
			;;
		?) echo "Wrong argument."
			exit 2
			;;
	esac
done
shift $(($OPTIND - 1))

main_loop