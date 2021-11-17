#pragma once
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

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

		// Get the string output of the object
		[[nodiscard]] std::string to_string() const
		{
			return ds_modal_.dump();
		}

		// Get size of the object
		[[nodiscard]] virtual size_t size() const = 0;
		// Print the object
		virtual void display() = 0;

	protected:
		json ds_modal_;

		virtual void update_json() = 0;
	};
} // namespace ds_common
