#! /bin/zsh

echo -e "\033c"
cp "$1$2" "Temp/src$2"
if [ $2x = ".cpp"x ]; then
	# g++ Temp/src$2 -o Temp/exec -std=c++98 -Wall -Wshadow -Wextra -g
	# g++ Temp/src$2 -o Temp/exec -std=c++17 -Wall -Wshadow -Wextra -g
	g++ "Temp/src$2" -o Temp/exec -std=c++14 -Wall -Wshadow -Wextra -g -fsanitize=undefined -I/home/tiger0132/code-backup/Temp $3 -lquadmath -DLOCAL
elif [ $2x = ".c"x ]; then
	gcc "Temp/src$2" -o Temp/exec -std=c99 -Wall -Wshadow -Wextra -g -lm $3
	# gcc Temp/src$2 -o Temp/exec -std=c99 -Wall -Wshadow -Wextra -g -fsanitize=undefined -fsanitize=address
fi