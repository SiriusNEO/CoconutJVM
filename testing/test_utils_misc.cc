// Test utils/misc

#include <gtest/gtest.h>

#include "../src/utils/misc.h"

// test split

TEST(UTILS_MISC, Split) {
  std::string originStr = "123.456.789";
  std::vector<std::string> buf;
  coconut::utils::split(originStr, '.', buf);

  EXPECT_EQ(buf[0], "123");
  EXPECT_EQ(buf[1], "456");
  EXPECT_EQ(buf[2], "789");
}

// test instanceof

class Parent {
 public:
  virtual ~Parent() {}
};

class Son1 : public Parent {
 public:
  ~Son1() {}
};

class Son2 : public Parent {
 public:
  ~Son2() {}
};

TEST(UTILS_MISC, InstanceOf) {
  Parent* ptr = new Son1();

  GTEST_ASSERT_TRUE(coconut::utils:: instanceof <Son1>(ptr));
  GTEST_ASSERT_FALSE(coconut::utils:: instanceof <Son2>(ptr));

  delete ptr;
}
