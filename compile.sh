#! /bin/zsh

newFilename=`echo $1 | md5sum | cut -d' ' -f1`;

cp $1$2 Temp/${newFilename}$2
g++ Temp/${newFilename}$2 -o Temp/exec -std=c++98 -Wall -Wshadow -Wextra

# -fsanitize=address -fsanitize=undefined

# sed -i /TEMP_FILENAME/d ~/.zshrc
# echo "export TEMP_FILENAME=\"${newFilename}\"" >> ~/.zshrc