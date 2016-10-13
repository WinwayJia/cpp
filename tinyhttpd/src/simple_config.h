#ifndef __SIMPLE_CONFIG_H__
#define __SIMPLE_CONFIG_H__

#include <string>
#include <map>

int get_config_map(const char *config_file, std::map<std::string, std::string> &configs);

#endif // __SIMPLE_CONFIG_H__
