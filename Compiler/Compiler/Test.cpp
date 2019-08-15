
//#include <vcclr.h>
#include "stdafx.h"
#include <boost/test/included/unit_test.hpp>
#define BOOST_TEST_MODULE mytests

//#include "Compiler.h"


BOOST_AUTO_TEST_CASE(myTestCase)
{
  BOOST_TEST(1 == 1);
  BOOST_TEST(true);
}