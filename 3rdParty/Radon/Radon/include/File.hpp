// Copyright Dmitro bjornus Szewczuk 2017 under zlib license

#pragma once

#include <string>
#include <vector>
#include <memory>

namespace radon
{
	class Section;

	class File
	{
	public:

		File(const std::string & path, bool reading = true);

		std::unique_ptr<Section> getSection(const std::string & name);

		void addSection(Section & category);

		void saveToFile();

	private:
		std::vector<std::unique_ptr<Section>> sections;
		std::string path;
	};
}