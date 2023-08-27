{

	"targets": [
		{
			"target_name": "sun-moon-almanac",
			"cflags_cc": ["-std=c++2a"],
			"sources": [
				"src/sun-moon.cpp",
				"src/lib/sun-moon/DateTime.cpp",
				"src/lib/sun-moon/DMS.cpp",
				"src/lib/sun-moon/InterpolationCalculator.cpp",
				"src/lib/sun-moon/Location.cpp",
				"src/lib/sun-moon/MoonCoordinates.cpp",
				"src/lib/sun-moon/MoonIluminationCalculator.cpp",
				"src/lib/sun-moon/MoonIluminationData.cpp",
				"src/lib/sun-moon/RiseSetInfo.cpp",
				"src/lib/sun-moon/SunCoordinates.cpp",
				"src/lib/sun-moon/SunCoordinatesMotion.cpp",
				"src/lib/sun-moon/SunTwilightsCalculator.cpp",
				"src/lib/sun-moon/SunTwilightsData.cpp",
				"src/lib/sun-moon/Utils.cpp",
			],
			"include_dirs": [
				"src/**/*.h",
				"<!(node -e \"require('nan')\")"
			]
		}
	]
}