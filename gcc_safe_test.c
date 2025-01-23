#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define SHELL_SCRIPT "./gcc_safe.sh"
#define TEST_SOURCE_FILE "test_program.c"
#define TEST_BINARY "test_program"

void create_test_source_file() {
    FILE *file = fopen(TEST_SOURCE_FILE, "w");
    if (!file) {
        perror("Failed to create test source file");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "#include <stdio.h>\nint main() { printf(\"Hello, World!\\n\"); return 0; }\n");
    fclose(file);
}

void test_safe_compilation() {
    printf("Running test: Safe compilation\n");
    int ret = system(SHELL_SCRIPT " -o " TEST_BINARY " " TEST_SOURCE_FILE);
    assert(ret == 0);
    printf("Safe compilation passed.\n");
}

void test_disallowed_flag() {
    printf("Running test: Disallowed flag\n");
    int ret = system(SHELL_SCRIPT " -fno-stack-protector -o " TEST_BINARY " " TEST_SOURCE_FILE);
    assert(ret != 0);
    printf("Disallowed flag test passed.\n");
}

void test_missing_mandatory_flag() {
    printf("Running test: Missing mandatory flag\n");
    int ret = system(SHELL_SCRIPT " -o " TEST_BINARY " " TEST_SOURCE_FILE);
    assert(ret == 0); // Mandatory flags are added by the script
    printf("Missing mandatory flag test passed.\n");
}

void test_invalid_input() {
    printf("Running test: Invalid input\n");
    int ret = system(SHELL_SCRIPT " -o " TEST_BINARY " non_existent_file.c");
    assert(ret != 0);
    printf("Invalid input test passed.\n");
}

void cleanup() {
    remove(TEST_SOURCE_FILE);
    remove(TEST_BINARY);
}

int main() {
    printf("Creating test source file...\n");
    create_test_source_file();

    printf("Starting test suite for gcc_safe.sh...\n");

    test_safe_compilation();
    test_disallowed_flag();
    test_missing_mandatory_flag();
    test_invalid_input();

    printf("Cleaning up...\n");
    cleanup();

    printf("All tests passed!\n");
    return 0;
}

