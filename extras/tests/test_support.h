#ifndef ECOSENSE_TEST_SUPPORT_H
#define ECOSENSE_TEST_SUPPORT_H
#include <stdio.h>
#include <stdlib.h>
#define ASSERT_TRUE(expr) do { if (!(expr)) { fprintf(stderr, "ASSERT_TRUE failed: %s:%d: %s\n", __FILE__, __LINE__, #expr); return 1; } } while (0)
#define ASSERT_EQ(a,b) do { auto _a=(a); auto _b=(b); if (!(_a == _b)) { fprintf(stderr, "ASSERT_EQ failed: %s:%d: %s != %s (%ld vs %ld)\n", __FILE__, __LINE__, #a, #b, (long)_a, (long)_b); return 1; } } while (0)
#endif
