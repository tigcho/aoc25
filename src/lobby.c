#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char *TEST_INPUT =
	"987654321111111\n"
	"811111111111119\n"
	"234234234234278\n"
	"818181911112111";

static const int TEST_EXPECT_PART1 = 357;
static const long long TEST_EXPECT_PART2 = 3121910778619;

#define INPUT_FILE "../input/3"

int part1(FILE *fp) {
    int total = 0;
    char line[256];

    while (fgets(line, sizeof(line), fp)) {
		line[strcspn(line, "\n")] = 0;
        int len = (int)strlen(line);
        int max_jolt = 0;

        for (int i = 0; i < len; i++) {
            for (int j = i + 1; j < len; j++) {
                int a = line[i] - '0';
                int b = line[j] - '0';
                int jolt = a * 10 + b;

                if (jolt > max_jolt) {
                    max_jolt = jolt;
                }
            }
        }
        total += max_jolt;
    }

    return total;
}

long long part2(FILE *fp) {
    char line[256];
    long long total = 0;
    const int K = 12;

    while (fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\n")] = 0;
        int n = (int)strlen(line);
        int pos = 0;
        char picked[16];
        int out_idx = 0;
        int remaining = K;

        while (remaining > 0) {
            int best_pos = pos;
            int search_limit = n - remaining;

            for (int i = pos; i <= search_limit; i++) {
                if (line[i] > line[best_pos]) {
                    best_pos = i;
                }
            }

            picked[out_idx++] = line[best_pos];
            pos = best_pos + 1;
            remaining--;
        }

        picked[out_idx] = '\0';
        long long value = atoll(picked); 
        total += value;
    }

    return total;
}

int run_test_part1(void) {
    FILE *fp = tmpfile();
    if (!fp) {
        perror("tmpfile");
        exit(EXIT_FAILURE);
    }

    fputs(TEST_INPUT, fp);
    rewind(fp);  

    int result = part1(fp);
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
    int test1 = run_test_part1();
    printf("Test 1 result: %d\n", test1);
    if (test1 != TEST_EXPECT_PART1) {
        printf("Part 1 test failed: got %d, expected %d\n", test1, TEST_EXPECT_PART1);
        return 1;
    }

    long long test2 = run_test_part2();
    printf("Test 2 result: %lld\n", test2);
    if (test2 != TEST_EXPECT_PART2) {
        printf("Part 2 test failed: got %d, expected %d\n", test2, TEST_EXPECT_PART2);
        return 1;
    }
    FILE *fp = fopen(INPUT_FILE, "r");
    if (!fp) {
        perror(INPUT_FILE);
        return 1;
    }

    int result1 = part1(fp);
    rewind(fp); 
    long long result2 = part2(fp);
    fclose(fp);

    printf("Part 1 result: %d\n", result1);
    printf("Part 2 result: %lld\n", result2);

    return 0;
}
