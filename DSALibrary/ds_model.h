#pragma once
#include <sstream>
#include <string>
#include <vector>

namespace ds_common
{
	// Get the typename
	template <typename T> inline const std::string getObjName(const T* obj)
	{
		// convert typename into string stream
		std::stringstream ss(typeid(obj).name());
		std::string target_str;
		size_t margin;
		// use space as delim for cutting string
		while (getline(ss, target_str, ' '))
		{
			// Check if the token has "::" operator
			margin = target_str.find("::");
			if (margin != std::string::npos)
			{
				break;
			}
		}

		// Return the partition of the target_str after the "::" operator
		return target_str.substr(margin + 2);
	}

	class dsaObj
	{
	public:
		dsaObj(std::string obj);

		// Print the object
		void display();

		// Get the string output of the object
		std::string toString();

		// Get size of the object
		virtual int getSize() = 0;

	protected:
		const std::string objType;

		virtual std::vector<std::string> str_out() = 0;
	};
} // namespace ds_common
