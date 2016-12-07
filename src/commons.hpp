#pragma once

static const char* SAVE_PATH = "downloads/content/";

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    std::string buf;
    while (std::getline(ss, item, delim)) {
      if (item[item.length() - 1] == '\\') {
        buf += item.substr(0, item.length() - 1) + delim;
      } else {
        buf += item;
        elems.push_back(buf);
        buf.clear();
      }
    }
    return elems;
}


std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}