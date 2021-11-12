#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace ds_common
{
	class dsa_obj
	{
	public:
		explicit dsa_obj(std::string obj_type) : obj_type_(std::move(obj_type)) {}
		virtual ~dsa_obj() = default;


		// Print the object
		void display()
		{
			std::cout << obj_type_ << std::endl;
			std::cout << "{" << std::endl;

			for (const std::vector<std::string> rows = str_out(); auto & element : rows)
			{
				std::cout << "    " << element << std::endl;
			}

			std::cout << "}" << std::endl;
		}

		// Get the string output of the object
		std::string to_string()
		{
			std::string result = obj_type_ + " { ";

			for (const std::vector<std::string> rows = str_out(); auto & element : rows)
			{
				result += element + ", ";
			}

			return result.substr(0, result.length() - 2) + " }";
		}

		// Get size of the object
		virtual size_t get_size() = 0;

	protected:
		const std::string obj_type_;

		virtual std::vector<std::string> str_out() = 0;
	};

	// template<class T>
	// [[nodiscard]] std::string get_obj_type()
	// {
	// 	{
	// 		// convert typename into string stream
	// 		std::stringstream ss(typeid(T).name());
	// 		std::string target_str;
	// 		size_t margin = 0;
	// 		// use space as delimiter for cutting string
	// 		while (getline(ss, target_str, ' '))
	// 		{
	// 			// Check if the token has "::" operator
	// 			margin = target_str.find("::");
	// 			if (margin != std::string::npos)
	// 			{
	// 				break;
	// 			}
	//
	// 		}
	//
	// 		// Return the partition of the target_str after the "::" operator
	// 		return target_str.substr(margin + 2);
	// 	}
	// }
} // namespace ds_common
