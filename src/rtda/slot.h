/*!
 *   ________  ________  ________  ________  ________   ___  ___  _________
 *   |\   ____\|\   __  \|\   ____\|\   __  \|\   ___  \|\  \|\  \|\___   ___\
 *   \ \  \___|\ \  \|\  \ \  \___|\ \  \|\  \ \  \\ \  \ \  \\\  \|___ \  \_|
 *    \ \  \    \ \  \\\  \ \  \    \ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *     \ \  \____\ \  \\\  \ \  \____\ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *      \ \_______\ \_______\ \_______\ \_______\ \__\\ \__\ \_______\   \ \__\
 *       \|_______|\|_______|\|_______|\|_______|\|__| \|__|\|_______|    \|__|
 *
 * \file src/rtda/slot.h
 * \brief The slot in the table / operand stack.
 * \author SiriusNEO
 */

#ifndef SRC_RTDA_SLOT_H_
#define SRC_RTDA_SLOT_H_

#include "../utils/logging.h"
#include "../utils/typedef.h"
#include "heap/object.h"

namespace coconut {

namespace rtda {

/*! \brief A slot in the table is 32bit. */
typedef uint32_t Slot32;

/*!
 * \brief The slot definition in the table. Either to be a data field (slot32
 * bytes) or a ObjectRef.
 *
 * \note In some machine (64bit machine), ref (the pointer) is 64bit. So the
 * union is 64bit. So why long and double still cost 2 slots (in this case, are
 * 128 bits)? It looks like a waste of space. The answer is: obey the standard
 * of JVM.
 */
typedef union {
  Slot32 bytes;
  Object* ref;
} Slot;

/*!
 * \brief List of Slots. Providing necessary reading/writing methods.
 */
class SlotList {
 private:
  /*! \brief Slots in the table. */
  Slot* slots_;

  /*! \brief Max number of slots. */
  unsigned int capacity_;

  /*!
   * \brief Check whether the LVT is overflowed by loading in some index.
   * \param index The index we will load.
   */
  void checkOverflow_(unsigned int index) {
    CHECK(index < capacity_) << "LocalVariableTable overflow!";
  }

 public:
  /*!
   * \brief Default constructor.
   * \param capacity Max number of slots.
   */
  SlotList(unsigned int capacity) : capacity_(capacity) {
    slots_ = new Slot[capacity_];
  }

  /*! \brief Default destructor. */
  ~SlotList() { delete[] slots_; }

  /*! \brief Show the brief info of the table. */
  std::string brief();

  /*!
   * \brief Set an integer(int32) to a postion.
   * \param index The position we set the data.
   * \param val The data we want to set.
   */
  void setInt(unsigned int index, int32_t val);

  /*!
   * \brief Get an integer(int32) from a postion.
   * \param index The position we fetch the data.
   */
  int32_t getInt(unsigned int index);

  /*!
   * \brief Set a float32 number to a postion.
   * \param index The position we set the data.
   * \param val The data we want to set.
   */
  void setFloat(unsigned int index, float val);

  /*!
   * \brief Get a float32 number from a postion.
   * \param index The position we fetch the data.
   */
  float getFloat(unsigned int index);

  /*!
   * \brief Set a long(int64) integer to a postion.
   * \param index The position we set the data.
   * \param val The data we want to set.
   */
  void setLong(unsigned int index, long long val);

  /*!
   * \brief Get a long(int64) integer from a postion.
   * \param index The position we fetch the data.
   */
  long long getLong(unsigned int index);

  /*!
   * \brief Set a double(float64) number to a postion.
   * \param index The position we set the data.
   * \param val The data we want to set.
   */
  void setDouble(unsigned int index, double val);

  /*!
   * \brief Get a double(float64) number from a postion.
   * \param index The position we fetch the data.
   */
  double getDouble(unsigned int index);

  /*!
   * \brief Set an Object reference to a postion.
   * \param index The position we set the ref.
   * \param ref The ref we want to set.
   */
  void setRef(unsigned int index, Object* ref);

  /*!
   * \brief Get an Object reference from a postion.
   * \param index The position we fetch the data.
   */
  Object* getRef(unsigned int index);
};

};  // namespace rtda

};  // namespace coconut

#endif  // SRC_RTDA_SLOT_H_
