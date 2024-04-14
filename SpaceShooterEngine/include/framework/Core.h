#include <stdio.h>

namespace ly {

//Macro for logging the frame rate
#define LOG(M, ...) printf(M "\n", ##__VA_ARGS__)
}