cd ./bin
cmake ./../
cmake --build . --target scrabble_debug
./scrabble_debug ../wordlists/NWL2023-modified.txt ../wordlists/trie.txt ../wordlists/extensions.txt ../games
