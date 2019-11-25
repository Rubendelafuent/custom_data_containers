solution "data_containers"
	configurations {
			"Release",
			"Debug"
		}
    defines {
		"WIN32",
		"_CONSOLE",
	}
    platforms {"x32", "x64"}
    location "../../vs"

	project "data_containers"
		language "C"
		kind "ConsoleApp"
    links{}

    includedirs{
      "../../include",
	}

    files{
      "../../src/**.c",
      "../../include/**.h"
    }
	configuration "Debug"
		flags { "Symbols" }

	configuration "vs2017"
	windowstargetplatformversion "10.0.15063.0"
