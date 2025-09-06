option("examples", { description = "Build the examples", default = false })

if has_config("examples") then
	set_group("Examples")
	if has_config("vulkan") then
		includes("Vulkan/xmake.lua")
	end
	if has_config("metal") then
		includes("Metal/xmake.lua")
	end
	if has_config("webgpu") then
		includes("WebGPU/xmake.lua")
	end
	if has_config("opengl") then
		includes("OpenGL/xmake.lua")
	end
	if has_config("software") then
		includes("Software/xmake.lua")
	end
	if has_config("d3d11") then
		includes("D3D11/xmake.lua")
	end
end
