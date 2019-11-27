#include "gtest/gtest.h"
#include "TritSet.h"

TEST(Tests, Capacity_Test) {
    TritSet set (1000);
    int capacity = set.capacity();
    set[0] = True;
    set[10000] = False;
    EXPECT_GE(capacity, 1000 * 2 / 8 / sizeof(uint));
    EXPECT_EQ(set[0], True);
    EXPECT_EQ(set[10000], False);
    EXPECT_EQ(set[100], Unknown);
    EXPECT_GT(set.capacity(), capacity);
    capacity = set.capacity();
    set[100000] = Unknown;
    EXPECT_EQ(set.capacity(), capacity);
}

TEST(Tests, Shrink_Test) {
    TritSet set (10);
    int capacity = set.capacity();
    set[100] = True;
    set[100] = Unknown;
    EXPECT_GT(set.capacity(), capacity);
    set.shrink();
    EXPECT_EQ(set.capacity(), capacity);
    set[100] = True;
    capacity = set.capacity();
    set[1000] = False;
    EXPECT_GT(set.capacity(), capacity);
    set[1000] = Unknown;
    set.shrink();
    EXPECT_EQ(set.capacity(), capacity);
}

TEST(Tests, And_Test) {
    TritSet a(10);
    a[0] = True;
    a[1] = False;
    a[3] = True;
    a[4] = False;
    a[5] = True;
    TritSet b(100);
    b[0] = False;
    b[1] = False;
    b[2] = False;
    b[3] = True;
    b[4] = True;
    b[20] = True;
    b[21] = False;
    TritSet c = a & b;
    EXPECT_EQ(b.capacity(), c.capacity());
    EXPECT_EQ(c[0], False);
    EXPECT_EQ(c[1], False);
    EXPECT_EQ(c[2], False);
    EXPECT_EQ(c[3], True);
    EXPECT_EQ(c[4], False);
    EXPECT_EQ(c[5], Unknown);
    EXPECT_EQ(c[6], Unknown);
    EXPECT_EQ(c[20], Unknown);
    EXPECT_EQ(c[21], False);
    EXPECT_EQ(c[22], Unknown);
}

TEST(Tests, Or_Test) {
    TritSet a(10);
    a[0] = True;
    a[1] = False;
    a[3] = True;
    a[4] = False;
    a[5] = True;
    TritSet b(100);
    b[0] = False;
    b[1] = False;
    b[2] = False;
    b[3] = True;
    b[4] = True;
    b[20] = True;
    b[21] = False;
    TritSet c = b | a;
    EXPECT_EQ(b.capacity(), c.capacity());
    EXPECT_EQ(c[0], True);
    EXPECT_EQ(c[1], False);
    EXPECT_EQ(c[2], Unknown);
    EXPECT_EQ(c[3], True);
    EXPECT_EQ(c[4], True);
    EXPECT_EQ(c[5], True);
    EXPECT_EQ(c[6], Unknown);
    EXPECT_EQ(c[20], True);
    EXPECT_EQ(c[21], Unknown);
    EXPECT_EQ(c[22], Unknown);
}

TEST(Tests, Not_Test) {
    TritSet a(3);
    a[0] = True;
    a[1] = False;
    a = ~a;
    EXPECT_EQ(a[0], False);
    EXPECT_EQ(a[1], True);
    EXPECT_EQ(a[2], Unknown);
}

TEST(Tests, Cardinality_Test) {
    TritSet a(10);
    a[0] = True;
    a[1] = False;
    a[3] = True;
    a[5] = True;
    a[12] = False;
    EXPECT_EQ(a.cardinality(True), 3);
    EXPECT_EQ(a.cardinality(False), 2);
    EXPECT_EQ(a.cardinality(Unknown), 8);
    EXPECT_EQ(a.cardinality()[True], a.cardinality(True));
    EXPECT_EQ(a.cardinality()[False], a.cardinality(False));
    EXPECT_EQ(a.cardinality()[Unknown], a.cardinality(Unknown));
}

TEST(Tests, Trim_Test) {
    TritSet a(100);
    int capacity = a.capacity();
    EXPECT_EQ(a.length(), 0);
    a[10000000] = False;
    EXPECT_EQ(a.length(), 10000001);
    a.trim(100);
    EXPECT_EQ(a.length(), 0);
    EXPECT_EQ(a.capacity(), capacity);
}

TEST(Tests, Shrink_Test_2) {
    TritSet a(100);
    TritSet b;
    b = a;
    TritSet c = a;
    EXPECT_EQ(b.capacity(), a.capacity());
    EXPECT_EQ(c.capacity(), a.capacity());
    b.shrink();
    c.shrink();
    EXPECT_EQ(b.capacity(), 0);
    EXPECT_EQ(c.capacity(), a.capacity());
}

TEST(Tests, Big_Test) {
    TritSet a;
    for (int i = 0; i < 99'999'999; ++i) {
        if (i % 3 == 1) {
            a[i] = True;
        }
        else if (i % 3 == 2) {
            a[i] = False;
        }
    }
    for (int i = 0; i < 99'999'999; ++i) {
        if (i % 3 == 1) {
            EXPECT_EQ(a[i], True);
        }
        else if (i % 3 == 2) {
            EXPECT_EQ(a[i], False);
        }
        else {
            EXPECT_EQ(a[i], Unknown);
        }
    }
    EXPECT_EQ(a.cardinality(True), 33'333'333);
    EXPECT_EQ(a.cardinality(False), 33'333'333);
    EXPECT_EQ(a.cardinality(Unknown), 33'333'333);
}

TEST(Tests, New_Test) {
    TritSet a, b;
    a[5] = True;
    b[5] = True;
    a[4] = False;
    b[4] = True;
    EXPECT_EQ(a[5], b[5]);
}

int main (int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

}