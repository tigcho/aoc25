#include <stdio.h>
#include <stdlib.h>

static const char *TEST_INPUT =
    "L68\n"
    "L30\n"
    "R48\n"
    "L5\n"
    "R60\n"
    "L55\n"
    "L1\n"
    "L99\n"
    "R14\n"
    "L82\n";

static const int TEST_EXPECT_PART1 = 3;
static const int TEST_EXPECT_PART2 = 6;

#define INPUT_FILE "input"

int part1(FILE *fp) {
    int dial_position = 50;
    int zero_count = 0;
    char line[256];

    while (fgets(line, sizeof(line), fp)) {
        char dir = line[0];
        int dist = atoi(&line[1]);
        int pos = dial_position;

        if (dir == 'L') {
            pos -= dist;
            pos = (pos % 100 + 100) % 100;
        } else if (dir == 'R') {
            pos = (pos + dist) % 100;
        }

        if (pos == 0) {
            zero_count++;
        }
        dial_position = pos;
    }

    return zero_count;
}

int part2(FILE *fp) {
    int dial_position = 50;
    int zero_count = 0;
    char line[256];

    while (fgets(line, sizeof(line), fp)) {
        char dir = line[0];
        int dist = atoi(&line[1]);

        if (dir == 'L') {
            for (int i = 0; i < dist; i++) {
                if (dial_position == 0) {
                    dial_position = 99;
                } else {
                    dial_position--;
                }

                if (dial_position == 0) {
                    zero_count++;
                }
            }
        } else if (dir == 'R') {
            for (int i = 0; i < dist; i++) {
                if (dial_position == 99) {
                    dial_position = 0;
                } else {
                    dial_position++;
                }

                if (dial_position == 0) {
                    zero_count++;
                }
            }
        }
    }

    return zero_count;
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

int run_test_part2(void) {
    FILE *fp = tmpfile();
    if (!fp) {
        perror("tmpfile");
        exit(EXIT_FAILURE);
    }

    fputs(TEST_INPUT, fp);
    rewind(fp);

    int result = part2(fp);
    fclose(fp);
    return result;
}

int main(void) {
    int test1 = run_test_part1();
    printf("Test 1 result: %d\n", test1);
    if (test1 != TEST_EXPECT_PART1) {
        printf("Part 1 test failed: got %d, expected %d\n",
               test1, TEST_EXPECT_PART1);
        return 1;
    }

    int test2 = run_test_part2();
    printf("Test 2 result: %d\n", test2);
    if (test2 != TEST_EXPECT_PART2) {
        printf("Part 2 test failed: got %d, expected %d\n",
               test2, TEST_EXPECT_PART2);
        return 1;
    }

    FILE *fp = fopen(INPUT_FILE, "r");
    if (!fp) {
        perror(INPUT_FILE);
        return 1;
    }

    int result1 = part1(fp);
    rewind(fp); 
    int result2 = part2(fp);
    fclose(fp);

    printf("Part 1 result: %d\n", result1);
    printf("Part 2 result: %d\n", result2);

    return 0;
}
