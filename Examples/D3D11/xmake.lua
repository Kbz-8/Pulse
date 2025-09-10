target("D3D11Example")
	add_deps("pulse_gpu")
	if is_plat("linux") then
		set_extension(".x86_64")
		add_defines("PULSE_D3D11_COMPILER_UNAVAILABLE")
	end
	add_files("*.c")
target_end()
