#include "../veb/veb.h"
#include <gtest/gtest.h>

TEST(VEBTree, Insert) {
  VEBTree veb(16);
  veb.insert(10);

  EXPECT_EQ(veb.getmin(), 10);
  EXPECT_EQ(veb.getmax(), 10);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
