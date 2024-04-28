workspace "Saddle"
	arch = "x64"

	architecture ("" .. arch)

	configurations {
		"Debug",
		"Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-" .. arch

project "Saddle"
		location "Saddle"
		kind "SharedLib"
		language "C++"

		targetdir ("bin/" .. outputdir .. "/%{prj.name}")
		objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

		files {
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp"
		}

		includedirs {
			"Saddle/src/Saddle"
		}

		filter "system:windows"
			cppdialect "C++17"
			staticruntime "On"
			systemversion "latest"

			defines {
				"SDL_PLATFORM_WINDOWS",
				"SDL_BUILD_DLL"
			}

			postbuildcommands {
				("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Run")
			}

		filter "configurations:Debug"
			defines "SDL_DEBUG"
			symbols "On"

		filter "configurations:Release"
			defines "SDL_RELEASE"
			optimize "On"

project "Run"
	location "Run"
	kind "ConsoleApp"

	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"Saddle/src"
	}

	links {
		"Saddle"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines {
			"SDL_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "SDL_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "SDL_RELEASE"
		optimize "On"