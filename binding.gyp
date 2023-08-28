{
	"targets": [
		{
			"target_name": "sun-moon-almanac",
			"cflags_cc": ["-std=c++0x"],
			"sources": [
				"src/sunmoon.cpp",
				"src/lib/DateTime.cpp",
				"src/lib/DMS.cpp",
				"src/lib/InterpolationCalculator.cpp",
				"src/lib/Location.cpp",
				"src/lib/MoonCoordinates.cpp",
				"src/lib/MoonIluminationCalculator.cpp",
				"src/lib/MoonIluminationData.cpp",
				"src/lib/RiseSetInfo.cpp",
				"src/lib/SunCoordinates.cpp",
				"src/lib/SunCoordinatesMotion.cpp",
				"src/lib/SunTwilightsCalculator.cpp",
				"src/lib/SunTwilightsData.cpp",
				"src/lib/Utils.cpp",
			],
			"include_dirs": [
				"<!(node -e \"require('nan')\")",
				"src/**/*.h",
			]
		}
	]
}