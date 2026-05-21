
#ifndef EXTENSIONS_H
#define EXTENSIONS_H
#include "helper.h"
#include <unordered_map>
#include <vector>

typedef std::vector<std::pair<std::string, std::string>> extension;
typedef std::unordered_map<std::string, extension> extension_map;

extension_map read_file(std::string file_path);

#endif
