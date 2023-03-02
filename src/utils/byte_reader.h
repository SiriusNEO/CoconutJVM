/*!
 *    ________  ________  ________  ________  ________   ___  ___  _________
 *   |\   ____\|\   __  \|\   ____\|\   __  \|\   ___  \|\  \|\  \|\___   ___\
 *   \ \  \___|\ \  \|\  \ \  \___|\ \  \|\  \ \  \\ \  \ \  \\\  \|___ \  \_|
 *    \ \  \    \ \  \\\  \ \  \    \ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *     \ \  \____\ \  \\\  \ \  \____\ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *      \ \_______\ \_______\ \_______\ \_______\ \__\\ \__\ \_______\   \ \__\
 *       \|_______|\|_______|\|_______|\|_______|\|__| \|__|\|_______|    \|__|
 *
 * \file src/utils/byte_reader.h
 * \brief ByteReader: a byte memory pool with some reading methods.
 * \author SiriusNEO
 */

#ifndef SRC_UTILS_BYTE_READER_H_
#define SRC_UTILS_BYTE_READER_H_

#include "logging.h"
#include "typedef.h"

namespace coconut {

namespace utils {

/*!
 * \brief ByteReader is a wrapper for a memory pool, with inferfaces to access
 * the data (in byte unit).
 *
 * Users can choose whether to let this reader to allocate memory internally or
 * pass extern memory pool to it. This will be indicated by a bool variable
 * borrowFlag_.
 */
class ByteReader {
 public:
  /*! \brief The cursor of the reader. Indicate the position in the memory pool
   * where the reader is in. */
  int cursor;

  /*! \brief The memory pool. */
  BYTE* bytePool;

 private:
  /*! \brief The size of the memory pool. */
  size_t poolSize_;

  /*! \brief A flag showing whether the memory pool is allocated internally or
   * passed externally. The name follows the Rust programming language. */
  bool borrowFlag_;

  /*!
   * \brief Check whether the memory pool is overflowed by some reading actions.
   * \param preReadNum Estimated numbers of bytes which will be read.
   */
  void checkOverflow_(int preReadNum) {
    CHECK(cursor + preReadNum > poolSize_) << "ByteReader bytePool overflow!";
  }

 public:
  /*!
   * \brief Default constructor. Allocating memory internally.
   * \param poolSize The size of the memory pool.
   */
  ByteReader(size_t poolSize)
      : cursor(0), poolSize_(poolSize), borrowFlag_(false) {
    bytePool = new BYTE[poolSize_];
  }

  /*!
   * \brief Default constructor. Pass the external pool.
   * \param poolSize The size of the memory pool.
   * \param externPool The external memory pool.
   */
  ByteReader(size_t poolSize, BYTE* externPool)
      : cursor(0),
        poolSize_(poolSize),
        bytePool(externPool),
        borrowFlag_(true) {}

  /*! \brief The default destructor. */
  ~ByteReader() {
    if (!borrowFlag_) {
      delete[] bytePool;
    }
  }

  /*!
   * \brief Check the status of the reader. (If an overflow happens, the reader
   * is considered as "bad")
   * \return Whether it is good.
   */
  bool good() { return cursor < poolSize_; }

  /*! \brief Fetch an uint8 (1 byte) from the pool. */
  uint8_t fetchU1();

  /*! \brief Fetch an uint16 (2 bytes) from the pool. */
  uint16_t fetchU2();

  /*! \brief Fetch an uint32 (4 bytes) from the pool. */
  uint32_t fetchU4();

  /*! \brief Fetch an int8 from the pool. */
  int8_t fetchInt8();

  /*! \brief Fetch an int16 from the pool. */
  int16_t fetchInt16();

  /*! \brief Fetch an int32 from the pool. */
  int32_t fetchInt32();

  /*! \brief Fetch an uint64 (8 bytes) from the pool. */
  uint64_t fetchU8();

  /*!
   * \brief Fetch a certain number of bytes from the pool and put into the
   * buffer.
   * \param byteNum The number of bytes to be fetched.
   * \param buffer The buffer we put fetched bytes.
   */
  void fetchBytes(size_t byteNum, std::vector<BYTE>& buffer);

  /*!
   * \brief Fetch a certain number of bytes from the pool and put into the
   * buffer.
   * \param byteNum The number of bytes to be fetched.
   * \param buffer The buffer we put fetched bytes.
   */
  void fetchBytes(size_t byteNum, BYTE* buffer);

  /*! \brief Padding the cursor of the reader to 4 bytes alignment. (Useful in
   * some instructions, such as tableswitch) */
  void padding4Bytes();

  /*!
   * \brief Fetch a list of uint16.
   * It will firstly fetch an uint16 n, which is the length of the list. Then it
   * will fetch n uint16 from the memory pool.
   * \param buffer The buffer we put fetched bytes.
   */
  void fetchU2List(std::vector<uint16_t>& buffer);

  /*!
   * \brief Fetch a list of int32.
   * It will firstly fetch an int32 n, which is the length of the list. Then it
   * will fetch n int32 from the memory pool.
   * \param buffer The buffer we put fetched bytes.
   */
  void fetchInt32List(int intNum, std::vector<int>& buffer);
};

}  // namespace utils

}  // namespace coconut

#endif  // SRC_UTILS_BYTE_READER_H_
