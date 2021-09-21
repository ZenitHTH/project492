#ifndef TYPEOF_H
#define TYPEOF_H

const char* TypeOf(const bool&)   { static const char type[] = "bool";    return type; }
const char* TypeOf(const bool*)   { static const char type[] = "bool*";   return type; }
const char* TypeOf(const char&)   { static const char type[] = "char";    return type; }
const char* TypeOf(const char*)   { static const char type[] = "char*";   return type; }
const char* TypeOf(const double&) { static const char type[] = "double";  return type; }
const char* TypeOf(const double*) { static const char type[] = "double*"; return type; }
const char* TypeOf(const float&)  { static const char type[] = "float";   return type; }
const char* TypeOf(const float*)  { static const char type[] = "float*";  return type; }
const char* TypeOf(const int&)    { static const char type[] = "int";     return type; }
const char* TypeOf(const int*)    { static const char type[] = "int*";    return type; }

#endif