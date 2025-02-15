export module wind.d_addon:parser;

import <cassert>;
import <memory>;
import <vector>;
import <string>;
import <cstdint>;
import <any>;
import <functional>;
import allegro;
import wind;
import :base;
import :object;

namespace wind
{
	namespace datafile
	{
		export class parser_t
		{
		public:
			parser_t() = delete;
			explicit parser_t(d_t& datafile);
			parser_t(const parser_t& parser) = delete;
			~parser_t() = default;

			static auto parse(const json_t& json, d_t& datafile) -> int32_t;

		private:
			auto parse_json(const json_t& json) -> int32_t;
			auto parse_array(const json_array_t& array) -> int32_t;
			auto parse_object(const json_t& json, datafile::object_t& dobject) -> int32_t;

			d_t& m_datafile;
		};
	}
}
