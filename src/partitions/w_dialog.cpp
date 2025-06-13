module wind;

import <string>;
import <cstdint>;
import <memory>;
import std;
import :base;
import :dson;
import :config;
import :string;
import :dialog;

namespace wind
{
	auto dialog_t::on_event(const ALLEGRO::EVENT& event) -> bool
	{
		return false;
	}
}
