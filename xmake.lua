add_rules("mode.debug", "mode.release")

package("raylib")
    add_deps("cmake")
    set_sourcedir(path.join(os.scriptdir(), "raylib"))
    on_install(function (package)
		if is_plat("wasm") then
			io.writefile("xmake.lua", [[
add_rules("mode.debug", "mode.release")
target("raylib") do
	set_kind("static")
	set_optimize("fastest")
	add_files(
		"src/rcore.c",
		"src/rshapes.c",
		"src/rtextures.c",
		"src/rtext.c",
		"src/rmodels.c",
		"src/utils.c",
		"src/raudio.c"
	)
	add_headerfiles("src/*.h")
	add_includedirs("src",{public=true})
	add_defines("PLATFORM_WEB", "GRAPHICS_API_OPENGL_ES2")
	add_ldflags("-s USE_GLFW=3")
end
			]])
			import("package.tools.xmake").install(package)
		else
			local configs = {}
			table.insert(configs, "-DCMAKE_BUILD_TYPE=" .. (package:debug() and "Debug" or "Release"))
			table.insert(configs, "-DBUILD_SHARED_LIBS=" .. (package:config("shared") and "ON" or "OFF"))
			import("package.tools.cmake").install(package, configs)
		end
	end)
package_end()

add_requires("raylib")


target("xavine") do
	set_kind("binary")
	set_optimize("fastest")
	add_files("src/*.cpp")
	add_packages("raylib")
	if is_plat("wasm") then
		add_defines("PLATFORM_WEB")
		add_ldflags("-s USE_GLFW=3", "--shell-file raylib/src/shell.html", {force = true})
	end
end