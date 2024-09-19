#!/bin/bash
#AGGELOS NIKOLAOS POTAMIANOS, 1084537
#GRIGORIOS TZWRTZAKIS, 1084538
#ANDREAS KATSAROS, 1084522

declare -g filename=$1

id(){
	echo "1084537|1084538|1084522"
}

mining_usernames(){

var="$@"
if [[ -z $var ]]; then awk ' { arr[$3]++ } END { for( no in arr) { printf no "\t" arr[no] "\n"} } ' $filename |sort | uniq

else awk -v pat="- $var" '$0~pat' $filename

fi
}

method(){
var="$@"
if [[ -z $var ]] || [[ $var != "GET" ]] && [[ $var != "POST" ]]; then echo "Wrong Method Name"
 

else 
	awk -v pat="$var" '$0~pat' $filename
	
fi

}

count_browsers(){
match(){
for browser in "Mozilla" "Chrome" "Safari" "Edg"
do
awk  -v pat=$browser 'BEGIN{count=0} $0~pat {count+=1} END {print pat "\t" count}' $filename
done
}
match
}


getip(){
var="$@"
if [[ -z $var ]] || [[ $var != "IPv4" ]] && [[ $var != "IPv6" ]]; then echo "Wrong Method Name"
 
elif [[ $var == "IPv4" ]]; then 
	sed -n '/127.0.0.1/p' $filename
else 	sed -n '/::1/p' $filename
fi
}

getdate(){
var="$@"
month="Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec"

if [[ -z $var ]]; then echo "Wrong Date"
elif grep -q -w $var <<< "$month" ; then awk -v pat="$var" '$0~pat' $filename 
else echo "Wrong Date"
fi
}


if [[ 0 == $# ]]; then
	id
	
elif [[ $filename  == *.log  ]]; then 
	opt="$2";
	case "$opt" in
		"--usrid" ) mining_usernames "$3" ;;
		"-method" ) method "$3" ;;
		"--browsers" ) count_browsers ;;
		"--servprot" ) getip "$3" ;;
		"--datum" )getdate "$3" ;;
		"" ) cat -n $1 ;;
		* ) echo "Wrong argument \o/ " ;;
	
	esac
elif [[ $filename != *.log ]]; then
	echo "Wrong File Argument"
fi
