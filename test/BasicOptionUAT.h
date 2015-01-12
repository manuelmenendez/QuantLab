#ifndef BASICOPTIONUAT_H
#define BASICOPTIONUAT_H

#include <memory>
#include <gtest/gtest.h>
#include "BasicOption.h"


class BasicOptionOptionUATFixture : public ::testing::Test
{
public:
	BasicOptionOptionUATFixture() : option_() {}
	std::unique_ptr<ql::BasicOption<>> option_;
protected:
	virtual void	SetUp();

};

#endif