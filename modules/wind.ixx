module;

export module wind;

export import allegro;

export import :array;
export import :base;
export import :bitmap;
export import :box;
export import :color;
export import :config;
export import :console;
export import :console.base;
export import :console.font;
export import :dialog;
export import :dialog.widget;
export import :dson;
export import :error;
export import :faders;
export import :file;
export import :flag;
export import :frame;
export import :hex;
export import :input;
export import :json;
export import :log;
export import :map;
export import :math;
export import :matrix;
export import :memory;
export import :ninepatch;
export import :path;
export import :random;
export import :string;
export import :system;
export import :tilemap;
export import :tilesheet;
export import :value;
export import :vector3d;
export import :word;

namespace wind
{
	export template <typename T> int32_t run(int32_t argc, char** argv)
	{
		static_assert(std::is_base_of<wind::dialog_t, T>::value, "T must be a subclass of wind::dialog_t");

		int32_t rv = 0;
		wind::array_t<wind::string_t> args(argc);

		for (int32_t i = 0; i < argc; ++i)
		{
			args[i] = argv[i];
		}

		std::shared_ptr<T> dialog = std::make_shared<T>();

		if (dialog)
		{
			system_t system(dialog);

			rv = system.run(args);

			dialog.reset();
		}
		else
		{
			rv = -1;
		}

		return rv;
	}
}
