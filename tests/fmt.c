#include <stdio.h>
#include <stdlib.h>

#include "fmt.h"

int test_parse_ipv4_addr() {
    int err, tc_failed, tc_len, fails = 0;
    unsigned char octets[4];

    struct {
        const char* name;
        const char* addr;
        int err;
        unsigned char octets[4];
    } tc[] = {
        {
            .name = "valid_min",
            .addr = "0.0.0.0",
            .err = 0,
            .octets = {0, 0, 0, 0}
        },
        {
            .name = "valid_max",
            .addr = "255.255.255.255",
            .err = 0,
            .octets = {255, 255, 255, 255}
        },
        {
            .name = "valid_mid",
            .addr = "10.0.23.100",
            .err = 0,
            .octets = {10, 0, 23, 100}
        },
        {
            .name = "invalid_high",
            .addr = "10.0.260.100",
            .err = 1,
        },
        {
            .name = "invalid_dots_more",
            .addr = "10.0.240.100.1",
            .err = 1,
        },
        {
            .name = "invalid_dots_less",
            .addr = "10.0.1",
            .err = 1,
        },
        {
            .name = "invalid_chars",
            .addr = "10.0.1.a",
            .err = 1,
        }
    };

    tc_len = sizeof(tc)/sizeof(tc[0]);
    printf("test_parse_ipv4_addr: start\n");
    for (int i = 0; i < tc_len; i++) {
        printf("(%d) %s: start\n", i, tc[i].name);
        
        tc_failed = 0;
        err = parse_ipv4_addr(tc[i].addr, octets);
        if (tc[i].err == 0 && err == 0) {
            for (int j = 0; j < 4; j++) {
                if (tc[i].octets[j] != octets[j]) {
                    fprintf(stderr, "expected %d, got %d at octet %d\n", tc[i].octets[j], octets[j], j);
                    tc_failed = 1;
                    break;
                }
            }
        } else if (tc[i].err != 0 && err != 0) {

        } else {
            fprintf(stderr, "expected %d, got %d as err\n", tc[i].err, err);
            tc_failed = 1;
        }

        if (tc_failed == 0) {
            printf("(%d) %s: passed\n", i, tc[i].name);
        } else {
            fprintf(stderr, "(%d) %s: failed\n", i, tc[i].name);
            fails++;
        }
    }

    if (fails == 0) {
        printf("test_parse_ipv4_addr: passed\n");
    } else {
        fprintf(stderr, "test_parse_ipv4_addr: failed (%d test cases)\n", fails);
    }

    return fails;
}

int main() {
    int fails = 0;

    if (test_parse_ipv4_addr() != 0) {
        fails++;
    }

    if (fails > 0) {
        fprintf(stderr, "\n%d test(s) failed\n", fails);
        exit(1);
    }

    return 0;
}
