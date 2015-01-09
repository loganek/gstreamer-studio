/*
 * maintest.cpp
 *
 *  Created on: Jan 9, 2015
 *      Author: loganek
 */

#include <gtest/gtest.h>

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
