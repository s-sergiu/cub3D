#include <gtest/gtest.h>

extern "C" {
#include "../include/cub3D.h"
}
// Demonstrate some basic assertions.
TEST(Sergiu, TestFilename) {
  // Expect equality.
  EXPECT_DEATH( read_map(0) , "Error:*");
  //EXPECT_EXIT( read_map(0) , ::testing::ExitedWithCode(14), "Error:*");
}
