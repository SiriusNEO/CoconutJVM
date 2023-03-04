// Test utils/mutf8

#include <gtest/gtest.h>

#include "../src/utils/mutf8.h"

// test decodeMUTF8FromBytes

TEST(UTILS_MUTF8, DecodeMUTF8) {
  std::vector<BYTE> bytes = {0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x20, 0xe4,
                             0xb8, 0x96, 0xe7, 0x95, 0x8c, 0x21, 0x20,
                             0x53, 0x61, 0x6e, 0x74, 0xc3, 0xa9, 0xed,
                             0xa0, 0xbc, 0xed, 0xbd, 0xbb};
  std::string str = coconut::utils::decodeMUTF8FromBytes(bytes);
  std::string expected =
      "Hello 世界! Santé🍻";  // not sure it can work in all machines

  EXPECT_EQ(str, expected);
}
