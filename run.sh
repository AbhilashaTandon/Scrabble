
cd ./bin
cmake ./../
cmake --build . --target scrabble
./scrabble_debug ../wordlists/NWL2023-modified.txt ../games

