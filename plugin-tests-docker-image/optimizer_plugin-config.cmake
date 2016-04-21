# Try to find the optimizer_plugin library

# OPTIMIZER_PLUGIN_FOUND       - System has optimizer_plugin lib
# OPTIMIZER_PLUGIN_LIBRARY     - Library needed to use optimizer_plugin


if (OPTIMIZER_PLUGIN_LIBRARY)
	# Already in cache, be silent
	set(OPTIMIZER_PLUGIN_FIND_QUIETLY TRUE)
endif()

find_library(OPTIMIZER_PLUGIN_LIBRARY NAMES ClanPlugin.so)
find_program(CLANG_EXECUTABLE_PATH NAMES bin/clang)

if (OPTIMIZER_PLUGIN_LIBRARY)
	message(STATUS "clang executable path found =) ${CLANG_EXECUTABLE_PATH}")
	message(STATUS "Library optimizer_plugin found =) ${OPTIMIZER_PLUGIN_LIBRARY}")
else()
	message(STATUS "Library optimizer_plugin not found =(")
endif()

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(OPTIMIZER_PLUGIN DEFAULT_MSG OPTIMIZER_PLUGIN_LIBRARY)

mark_as_advanced(OPTIMIZER_PLUGIN_LIBRARY)
