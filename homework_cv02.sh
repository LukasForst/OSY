#!/bin/bash

DIR_COUNT=0
FILE_COUNT=0
LINK_COUNT=0
COMPUTED_FILES=()

WRITE_SUMMARY=false
MAKE_ARCHIVE=false
ERROR_FILE=false

COUNTING=false

main_loop(){
	while read -r LINE
	do
		if [[ ${LINE} == "FILE "* ]]; then
			RELATIVE_PATH="${LINE:5:${#LINE}}"
			FILE_PATH=$(realpath -s "${RELATIVE_PATH}")
			process_data

		fi

	done

	write_result
}

process_data(){
	if [[ -d "${FILE_PATH}" ]]; then #directory
		((DIR_COUNT++))

		if [ "${COUNTING}" = true ]; then
			echo "DIR ${DIR_COUNT} '${FILE_PATH}'"
		else
			echo "DIR '${FILE_PATH}'"
		fi
	elif [[ -L "${FILE_PATH}" ]]; then #sym link
		((LINK_COUNT++))
		LINK_DESTINATION=$(readlink ${FILE_PATH})
		if [ "${COUNTING}" = true ]; then
			echo "LINK ${LINK_COUNT} '${FILE_PATH}' '${LINK_DESTINATION}'"
		else
			echo "LINK '${FILE_PATH}' '${LINK_DESTINATION}'"
		fi
	elif [[ -f "${FILE_PATH}" ]]; then #file
		COMPUTED_FILES+=("${FILE_PATH}")
		((FILE_COUNT++))

		LINE_COUNT=$(wc -l < "${FILE_PATH}")
		FIRST_LINE=$(head -n 1 "${FILE_PATH}")

		if [ "${COUNTING}" = true ]; then
			echo "FILE ${FILE_COUNT} '${FILE_PATH}' ${LINE_COUNT} '${FIRST_LINE}'"
		else
			echo "FILE '${FILE_PATH}' ${LINE_COUNT} '${FIRST_LINE}'"
		fi
	else
		>&2 echo "ERROR '${RELATIVE_PATH}'"
		ERROR_FILE=true
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
	if [ "${WRITE_SUMMARY}" = true ]; then
		echo ${FILE_COUNT}
		echo ${DIR_COUNT}
		echo ${LINK_COUNT}
	fi

	if [ "${MAKE_ARCHIVE}" = true ]; then
		tar -czf output.tgz "${COMPUTED_FILES[@]}"
	fi
	
	if [ "${ERROR_FILE}" = true ]; then
		exit 1
	else
		exit 0
	fi
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
		?)
			exit 2
			;;
	esac
done
shift $(($OPTIND - 1))

main_loop