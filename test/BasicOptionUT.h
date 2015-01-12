#ifndef BASICOPTIONUT_H
#define BASICOPTIONUT_H

#include <memory>
#include <gtest/gtest.h>
#include "BasicOption.h"


class BasicOptionOptionUTFixture : public ::testing::Test
{
public:
	BasicOptionOptionUTFixture() : option_() {}
	std::unique_ptr<ql::BasicOption<>> option_;

protected:
	virtual void	SetUp();

};



#endif