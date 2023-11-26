#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "fmt.h"

int parse_ipv4_addr(const char* addr, unsigned char* octets) {
    unsigned i = 0;     // indexing for addr
    unsigned j = 0;     // indexing for octets
    unsigned char octet = 0;

    while (addr[i] != '\0') {
        if (isdigit(addr[i])) {
            octet = (octet * 10) + addr[i] - '0';
            if (octet > 255) {
                fprintf(stderr, "value %d in octet %d is not in range [0, 255]\n", octet, j);
                return -1;
            }
        } else if (addr[i] == '.') {
            if (j > 2) {
                fprintf(stderr, "addr contains more than 4 octets\n");
                return -1;
            }

            octets[j++] = octet;
            octet = 0;
        } else {
            fprintf(stderr, "invalid character '%c' encountered in addr at index %d\n", addr[i], i);
            return -1;
        }

        i++;
    }

    octets[j] = octet;
    if (j != 3) {
        fprintf(stderr, "addr contains less than 4 octets\n");
        return -1;
    }

    return 0;
}
