#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace ds_common
{
	using namespace std;

	template <class T>
	class dsaObj
	{
	public:
		dsaObj() : objType(getObjType()) {}

		// Print the object
		void display()
		{
			cout << objType << endl;
			cout << "{" << endl;

			vector<string> rows = str_out();
			for (auto& element : rows)
			{
				cout << "    " << element << endl;
			}

			cout << "}" << endl;
		}

		// Get the string output of the object
		string toString()
		{
			string result = objType + " { ";

			vector<string> rows = str_out();
			for (auto& element : rows)
			{
				result = result + element + ", ";
			}

			return result.substr(0, result.length() - 2) + " }";
		}

		// Get size of the object
		virtual int getSize() = 0;

	protected:
		const string objType;

		virtual vector<string> str_out() = 0;

	private:
		
		string getObjType()
		{
			// convert typename into string stream
			stringstream ss(typeid(T).name());
			string target_str;
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
	};
} // namespace ds_common
