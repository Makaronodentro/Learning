#include <stdint.h>

typedef uint16_t HEXA;

typedef struct 
{ 
    HEXA   h1; 
    HEXA   h2; 
    HEXA   h3; 
    HEXA   h4;
    char*  img;
    
} __attribute__((__packed__)) 
JPG;
