#pragma once
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

namespace ds_modals
{
	constexpr auto ds_version = 1.0;

	class dsa_obj
	{
	public:
		explicit dsa_obj(std::string obj_type)
		{
			ds_modal_["structure"] = std::move(obj_type);
			ds_modal_["version"] = ds_version;
		}
		virtual ~dsa_obj() = default;

		// Get size of the object
		[[nodiscard]] virtual size_t size() const = 0;
		// Get the string output of the object
		std::string to_string()
		{
			serialize();
			return ds_modal_.dump();
		}

		// Print the object
		virtual void display() = 0;

	protected:
		json ds_modal_;

		// Update JSON object
		virtual void serialize() = 0;
		// Parse a JSON into a object
		virtual void deserialize(std::ifstream ifs) = 0;
	};
} // namespace ds_common