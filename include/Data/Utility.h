// Copyright (C) 2020 Maxim, 2dev2fun@gmail.com. All rights reserved.

#pragma once

#include <dirent.h>
#include <stdexcept>
#include <string>
#include <vector>

namespace simple {

std::vector<std::string> FilesInDir(char const* path, char const* extension) {
	std::vector<std::string> listFiles;

	struct dirent* entry;
	DIR* dir = opendir(path);

	if (dir == NULL) {
		std::runtime_error("Directory not found!");
	}

	while ((entry = readdir(dir)) != NULL) {
		std::string filename = entry->d_name;
		if (filename.substr(filename.find_last_of(".") + 1) == extension) {
			listFiles.push_back(filename);
		}
	}

	closedir(dir);

	return listFiles;
}

} // namespace simple
