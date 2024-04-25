local DIR_ROOT = (path.getabsolute('..') .. '/')
local DIR_LIB = DIR_ROOT .. 'lib/'

return function(options, core)
	if not options then options = {} end
	if not options.dir then options.dir = DIR_LIB .. 'galaxy/' end
	if not options.config then options.config = {} end

	configuration(options.config)

	if core then
		-- Files
		files {
			DIR_ROOT .. 'include/Unet/Services/ServiceGalaxy.h',
			DIR_ROOT .. 'src/Services/ServiceGalaxy.cpp',
		}
	end

	-- Include dir
	includedirs {
		options.dir .. 'Include/',
	}

	if options.link then
		-- Lib dir
		libdirs {
			options.dir .. 'Libraries/',
		}

		-- Link
		if os.get() == 'linux' then
			configuration(unet_merge_config(options.config, 'x64'))
				links { 'Galaxy64' }
			configuration(unet_merge_config(options.config, 'x32'))
				links { 'Galaxy' }
		else
			configuration(options.config)
				links { 'Galaxy' }
		end
	end
end
