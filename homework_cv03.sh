#!/usr/bin/env bash
# author Lukas Forst
# date 17.10.2017

web_page=""
arg_num=0
read_from_stdin=false

parse_pdf(){
    echo "${web_page}" | tr -d '\n' | grep -io "<a[[:space:]]*href=\"[^\"]\+\.pdf\">" | awk 'BEGIN{FS="\""}{print $2}'
}

get_page(){
    web_page="`wget -qO- "${url}"`"
}

verify_arg(){
    if [ "${arg_num}" -gt "1" ]; then
        >&2 echo "Script has too many arguments!"
        exit 1
    fi
}

print_man(){
    echo "Usage of the script:"
    echo "`basename $0` [-h] [-i] [-u <argument>]"
    echo "-h show this man page"
    echo "-i script takes url from standard input"
    echo "-u script takes url as an argument"
    exit 0
}

if [ $# -gt 2 ] || [ $# == 0 ]; then
    >&2 echo "Script has invalid number of arguments!"
    exit 2
fi

while getopts ":hiu:" opt; do
  case $opt in
  h) print_man
    ;;
  i) arg_num=$((arg_num+1))
     verify_arg
     read_from_stdin=true
    ;;
  u) arg_num=$((arg_num+1))
     verify_arg
     url="${OPTARG}"
    ;;
  ?) >&2 echo "Script has invalid argument to run!"
    exit 1
    ;;
  esac
done
shift $(($OPTIND - 1))
# url="https://cw.fel.cvut.cz/wiki/_media/courses/b4b35osy/cviceni/cviceni03_test_html.txt"

if [[ ${read_from_stdin} = true ]]; then
    read -r url
fi

get_page
parse_pdf