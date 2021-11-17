#pragma once
#include "pch.h"

namespace ds_modals
{
	template <typename T>
	class stack final : public dsa_obj
	{
	public:
		explicit stack(unsigned short length);
		~stack() override;

		[[nodiscard]] bool is_empty() const;

		void push(T obj);

		T* pop();

		[[nodiscard]] size_t size() const override;

	protected:
		std::vector<std::string> str_out() override;
		
	private:
		const unsigned short len_;
		T* arr_fixed_;
		int top_;
	};
}
