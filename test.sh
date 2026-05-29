cd ./bin
cmake ./../
cmake --build . --target scrabble_test
./scrabble_test ../wordlists/NWL2023-modified.txt ../wordlists/trie.txt ../wordlists/extensions.txt ../games
