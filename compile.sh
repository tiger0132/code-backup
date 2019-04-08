#! /bin/bash

cp "$1$2" "Temp/src$2"
if [ $2x = ".cpp"x ]; then
	# g++ Temp/src$2 -o Temp/exec -std=c++98 -Wall -Wshadow -Wextra -g
	g++ Temp/src$2 -o Temp/exec -std=c++11 -Wall -Wshadow -Wextra -g
	# g++ Temp/src$2 -o Temp/exec -std=c++98 -Wall -Wshadow -Wextra -g -fsanitize=undefined -fsanitize=address
elif [ $2x = ".c"x ]; then
	gcc Temp/src$2 -o Temp/exec -std=c99 -Wall -Wshadow -Wextra -g
	# gcc Temp/src$2 -o Temp/exec -std=c99 -Wall -Wshadow -Wextra -g -fsanitize=undefined -fanitize=address
fi