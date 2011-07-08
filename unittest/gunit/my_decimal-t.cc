/* Copyright (c) 2011, Oracle and/or its affiliates. All rights reserved.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; version 2 of the License.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA */

#include "my_config.h"
#include <gtest/gtest.h>

#include <my_decimal.h>

namespace {

class DecimalTest : public ::testing::Test
{
protected:
  my_decimal d1;
  my_decimal d2;
};

TEST_F(DecimalTest, CopyAndCompare)
{
  ulonglong val= 42;
  EXPECT_EQ(0, ulonglong2decimal(val, &d1));

  d2= d1;                                       // operator=()
  my_decimal d3(d1);                            // Copy constructor.

  EXPECT_EQ(0, my_decimal_cmp(&d1, &d2));
  EXPECT_EQ(0, my_decimal_cmp(&d2, &d3));
  EXPECT_EQ(0, my_decimal_cmp(&d3, &d1));

  ulonglong val1, val2, val3;
  EXPECT_EQ(0, decimal2ulonglong(&d1, &val1));
  EXPECT_EQ(0, decimal2ulonglong(&d2, &val2));
  EXPECT_EQ(0, decimal2ulonglong(&d3, &val3));
  EXPECT_EQ(val, val1);
  EXPECT_EQ(val, val2);
  EXPECT_EQ(val, val3);

  // The CTOR/operator=() generated by the compiler would fail here:
  val= 45;
  EXPECT_EQ(0, ulonglong2decimal(val, &d1));
  EXPECT_EQ(1, my_decimal_cmp(&d1, &d2));
  EXPECT_EQ(1, my_decimal_cmp(&d1, &d3));
}


TEST_F(DecimalTest, Swap)
{
  ulonglong val1= 1;
  ulonglong val2= 2;
  EXPECT_EQ(0, ulonglong2decimal(val1, &d1));
  EXPECT_EQ(0, ulonglong2decimal(val2, &d2));
  my_decimal d1copy(d1);
  my_decimal d2copy(d2);
  EXPECT_EQ(0, my_decimal_cmp(&d1, &d1copy));
  EXPECT_EQ(0, my_decimal_cmp(&d2, &d2copy));
  d1.swap(d2);
  EXPECT_EQ(0, my_decimal_cmp(&d2, &d1copy));
  EXPECT_EQ(0, my_decimal_cmp(&d1, &d2copy));
}

}
