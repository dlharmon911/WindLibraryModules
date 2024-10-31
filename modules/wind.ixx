module;


export module wind;

export import allegro;

export import :base;
export import :bitmap;
export import :box;
export import :color;
export import :config;
export import :console;
export import :console.base;
export import :console.font;
export import :dialog;
export import :dson;
export import :error;
export import :file;
export import :frame;
export import :hex;
export import :input;
export import :json;
export import :map;
export import :math;
export import :memory;
export import :path;
export import :string;
export import :system;
export import :tilemap;
export import :tilesheet;
export import :vector;

namespace wind
{
	export template <typename T> int32_t run(int32_t argc, char** argv)
	{
		int32_t rv = 0;
		wind::vector_t<wind::string_t> args(argc);

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

