// Copyright Dmitro bjornus Szewczuk 2017

#include "../include/Radon.hpp"

#include <assert.h>

namespace radon
{
	Section::Section()
		: Named()
	{
	}


	Section::Section(const std::string & name)
		: Named(name)
	{
	}


	Key Section::getKey(const std::string & name)
	{
		for each (auto var in keys)
		{
			if (var.getName() == name)
				return var;
		}

		assert(1);
	}


	void Section::addKey(Key & variable)
	{
		keys.push_back(variable);
	}
}