#include <gtest/gtest.h>

extern "C" {
#include "../include/cub3D.h"
}
// Demonstrate some basic assertions.
TEST(read_map, zero_number) {
  EXPECT_EXIT( read_map(0) , ::testing::ExitedWithCode(14), "Error:*");
}

TEST(read_map, NULL) {
  EXPECT_EXIT( read_map(NULL) , ::testing::ExitedWithCode(14), "Error:*");
}

TEST(read_map, normal_map) {
  char filename[] = "../data/maps/test1.cub";
  EXPECT_STREQ(read_map(filename), "maptest1\n");
}

TEST(read_map, no_extension) {
  char filename[] = "../data/maps/test2";
  EXPECT_STREQ(read_map(filename), "noextension\n");
}

TEST(getTotalBytes, filename) {
  char filename[] = "../data/maps/test2";
  EXPECT_EQ(get_total_bytes(filename), 12);
}
