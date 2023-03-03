/*!
 *   ________  ________  ________  ________  ________   ___  ___  _________
 *   |\   ____\|\   __  \|\   ____\|\   __  \|\   ___  \|\  \|\  \|\___   ___\
 *   \ \  \___|\ \  \|\  \ \  \___|\ \  \|\  \ \  \\ \  \ \  \\\  \|___ \  \_|
 *    \ \  \    \ \  \\\  \ \  \    \ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *     \ \  \____\ \  \\\  \ \  \____\ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *      \ \_______\ \_______\ \_______\ \_______\ \__\\ \__\ \_______\   \ \__\
 *       \|_______|\|_______|\|_______|\|_______|\|__| \|__|\|_______|    \|__|
 *
 * \file src/rtda/vmstack/local_variable_table.h
 * \brief JVM Local Variable Table.
 * \author SiriusNEO
 */

#ifndef SRC_RTDA_VMSTACK_LOCAL_VARIABLE_TABLE_H_
#define SRC_RTDA_VMSTACK_LOCAL_VARIABLE_TABLE_H_

#include "../../utils/logging.h"
#include "slot.h"

namespace coconut {

namespace rtda {

/*!
 * \brief Local Variable Table of JVM.
 *
 * It is in a frame of the JVM Stack. It stores values of local variables in
 * current scope. A slot is 32bit in JVM convention so long/double take two
 * slots.
 */
class LocalVariableTable {
 private:
  /*! \brief Slots in the table. */
  Slot* slots_;

  /*! \brief Max number of slots. */
  unsigned int maxLocals_;

  /*!
   * \brief Check whether the LVT is overflowed by loading in some index.
   * \param index The index we will load.
   */
  void checkOverflow_(unsigned int index) {
    CHECK(index < maxLocals_) << "LocalVariableTable overflow!";
  }

 public:
  /*!
   * \brief Default constructor.
   * \param maxLocals Max number of slots.
   */
  LocalVariableTable(unsigned int maxLocals) : maxLocals_(maxLocals) {
    slots_ = new Slot[maxLocals_];
  }

  /*! \brief Default destructor. */
  ~LocalVariableTable() { delete[] slots_; }

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

}  // namespace rtda

}  // namespace coconut

#endif  // SRC_RTDA_VMSTACK_LOCAL_VARIABLE_TABLE_H_
