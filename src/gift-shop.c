#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char *TEST_INPUT =
    "11-22,95-115,998-1012,1188511880-1188511890,222220-222224,1698522-1698528,446443-446449,38593856-38593862,565653-565659,824824821-824824827,2121212118-2121212124";

static const long long TEST_EXPECT_PART1 = 1227775554LL;
static const long long TEST_EXPECT_PART2 = 4174379265LL;

#define INPUT_FILE "../input/2"

long long invalid_ranges(FILE *fp, int (*is_invalid)(long long)) {
	char line[1024];
	long long invalid_sum = 0;

	if (!fgets(line, sizeof(line), fp)) {
		return 0;
	}

	char *token = strtok(line, ",");
	while (token) {
		char *dash = strchr(token, '-');
		if (dash) {
			*dash = '\0';
			long long start = atoll(token);
			long long end   = atoll(dash + 1);

			for (long long id = start; id <= end; id++) {
				if (is_invalid(id)) {
					invalid_sum += id;
				}
			}
		}

		token = strtok(NULL, ",");
	}

	return invalid_sum;
}

int is_invalid_part1(long long n) {
	char s[32];
    int len, half;

    sprintf(s, "%lld", n);
    len = (int)strlen(s);

	// must be even otherwise can't be a double
    if (len % 2 != 0) {
        return 0;
    }

	// leading zero not allowed
    if (s[0] == '0') {
        return 0;
    }

    half = len / 2;

	// for "1212"
	// i = 0: s[0] == s[2] -> '1' == '1'
	// i = 1: s[1] == s[3] -> '2' == '2'
    for (int i = 0; i < half; i++) {
        if (s[i] != s[i + half]) {
            return 0;
        }
    }

    return 1;
}

int is_invalid_part2(long long n) {
    char s[32];
    sprintf(s, "%lld", n);
    int len = strlen(s);

	// cannot repeat if length is 1 or zero
    if (len <= 1) {
        return 0;
    }

    if (s[0] == '0') {
        return 0;
    }

	// a sequence above len/2 = 5 cannot repeat twice when len = 10
    for (int i = 1; i <= len / 2; i++) {
        if (len % i != 0) {
            continue; 
        }

        int repeat = len / i;
        if (repeat < 2) {
            continue; 
        }

		// for s = "11", i = 1, len = 2
		// j = 0: s[0] == s[0 % 1] -> '1' == '1'
		// j = 1: s[1] == s[1 % 1] -> '1' == '1'
        int match = 1;
        for (int j = i; j < len; j++) {
            if (s[j] != s[j % i]) {
                match = 0;
                break;
            }
        }

        if (match) {
            return 1; 
        }
    }

    return 0; 
}

long long part1(FILE *fp) {
	return invalid_ranges(fp, is_invalid_part1);
}

long long part2(FILE *fp) {
	return invalid_ranges(fp, is_invalid_part2);
}

long long run_test_part1(void) {
    FILE *fp = tmpfile();
    if (!fp) {
        perror("tmpfile");
        exit(EXIT_FAILURE);
    }

    fputs(TEST_INPUT, fp);
    rewind(fp);

    long long result = part1(fp);
    fclose(fp);
    return result;
}

long long run_test_part2(void) {
    FILE *fp = tmpfile();
    if (!fp) {
        perror("tmpfile");
        exit(EXIT_FAILURE);
    }

    fputs(TEST_INPUT, fp);
    rewind(fp);

    long long result = part2(fp);
    fclose(fp);
    return result;
}

int main(void) {
    long long test1 = run_test_part1();
    printf("Test 1 result: %lld\n", test1);
    if (test1 != TEST_EXPECT_PART1) {
        printf("Part 1 test failed: got %lld, expected %lld\n", test1, TEST_EXPECT_PART1);
        return 1;
    }

    long long test2 = run_test_part2();
    printf("Test 2 result: %lld\n", test2);
    if (test2 != TEST_EXPECT_PART2) {
        printf("Part 2 test failed: got %lld, expected %lld\n", test2, TEST_EXPECT_PART2);
        return 1;
    }

    FILE *fp = fopen(INPUT_FILE, "r");
    if (!fp) {
        perror(INPUT_FILE);
        return 1;
    }

    long long result1 = part1(fp);
    rewind(fp);
    long long result2 = part2(fp);
    fclose(fp);

    printf("Part 1 result: %lld\n", result1);
    printf("Part 2 result: %lld\n", result2);

    return 0;
}
