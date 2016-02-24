#ifndef _TXTFILEIO_H
#define _TXTFILEIO_H

#include <string>
#include <vector>

namespace txtfileio {

std::vector<std::string> readlines(std::string filename, std::vector<std::string>::size_type num_lines = -1);

void tokenize(const std::string &line, std::vector<std::string> &tokens,
    const std::string &delimiters = " ", bool trimEmpty = false);
}

#endif