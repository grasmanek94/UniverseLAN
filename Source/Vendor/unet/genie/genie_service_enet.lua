local DIR_ROOT = (path.getabsolute('..') .. '/')
local DIR_LIB = DIR_ROOT .. 'lib/'

return function(options, core)
	if not options then options = {} end
	if not options.dir then options.dir = DIR_LIB .. 'enet/' end
	if not options.config then options.config = {} end
	if options.link == nil then options.link = true end

	configuration(options.config)

	if core then
		-- Files
		files {
			DIR_ROOT .. 'include/Unet/Services/ServiceEnet.h',
			DIR_ROOT .. 'src/Services/ServiceEnet.cpp',
		}
	end

	-- Include dir
	includedirs {
		options.dir .. 'include/',
	}

	if options.link then
		-- Library dir
		libdirs {
			options.dir .. 'lib/',
		}

		-- Link
		if os.get() == 'windows' then
			configuration(unet_merge_config(options.config, { 'Debug', 'x64' }))
				links { 'enet64d' }
			configuration(unet_merge_config(options.config, { 'Release', 'x64' }))
				links { 'enet64' }

			configuration(unet_merge_config(options.config, { 'Debug', 'x32' }))
				links { 'enetd' }
			configuration(unet_merge_config(options.config, { 'Release', 'x32' }))
				links { 'enet' }
		else
			configuration(options.config)
				links { 'enet' }
		end

		-- Additional libraries
		if os.get() == 'windows' then
			configuration(options.config)
				links {
					'Ws2_32',
					'Winmm',
				}
		end
	end
end
