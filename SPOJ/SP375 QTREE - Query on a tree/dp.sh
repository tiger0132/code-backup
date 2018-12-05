BOLD=`tput bold`
RED="\033[31m${BOLD}"
GREEN="\033[32m${BOLD}"
DGREEN="\033[0;32m"
RESET="\033[0m"
WA_CNT=1
TESTCASE=1

BF="1"
STD="std"
GEN="data"
GEN_IN="in.in"
STD_OUT="std.out"
BF_OUT="wa.out"

g++ ${STD}.cpp -o ${STD}
echo ${GREEN} ✔ Compile: Success${RESET}
g++ ${BF}.cpp -o ${BF}
echo ${GREEN} ✔ Compile: Success${RESET}
g++ ${GEN}.cpp -o ${GEN}
echo ${GREEN} ✔ Compile: Success${RESET}

while true; do
	if [ ${WA_CNT} -gt 100 ]; then
		echo ${RED} ✘ THE STD IS BULLSHIT!!!${RESET}
		exit 1
	fi
	
	if ./${GEN}; then
		echo ${DGREEN} ✔ Generator: Success${RESET}
	else
		echo ${RED} ✘ Generator: Failure${RESET}
		exit 1
	fi
	
	if ./${BF}; then
		echo ${DGREEN} ✔ Brute force: Success${RESET}
	else
		echo ${RED} ✘ Brute force: Failure${RESET}
	fi
	
	if ./${STD}; then
		echo ${DGREEN} ✔ std: Success${RESET}
	else
		echo ${RED} ✘ std: Failure${RESET}
	fi 
	
	# ./${GEN}
	# ./${BF}
	# ./${STD}

	if diff ${BF_OUT} ${STD_OUT}; then 
		echo "${GREEN}${BOLD} ✔ Accepted${RESET} on Test ${BOLD}#${TESTCASE}${RESET}"
	else
		echo "${RED}${BOLD} ✘ Wrong Answer${RESET} on Test ${BOLD}#${TESTCASE}${RESET} (${WA_CNT} time(s))"
		cp ${GEN_IN} wa${WA_CNT}.in
		WA_CNT=$((${WA_CNT}+1))
	fi
	
	TESTCASE=$((${TESTCASE}+1))
done
