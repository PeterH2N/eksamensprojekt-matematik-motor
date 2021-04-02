#ifndef GLOBALS_H
#define GLOBALS_H

#include <string>
#include <map>
#include <vector>
#include <functional>

static char operators[] = { '+', '-', '*', '/', '^', '=', '(', ')', ':' };
static char seperators[] = { ';' };
static std::map<std::string, double> identifiers;
static std::map< std::string, std::function<void()> > storedFunctions;

#endif GLOBALS_H

