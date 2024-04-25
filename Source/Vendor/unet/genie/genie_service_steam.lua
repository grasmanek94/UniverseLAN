local DIR_ROOT = (path.getabsolute('..') .. '/')
local DIR_LIB = DIR_ROOT .. 'lib/'

return function(options, core)
	if not options then options = {} end
	if not options.dir then options.dir = DIR_LIB .. 'steamworks/' end
	if not options.config then options.config = {} end

	configuration(options.config)

	if core then
		-- Files
		files {
			DIR_ROOT .. 'include/Unet/Services/ServiceSteam.h',
			DIR_ROOT .. 'src/Services/ServiceSteam.cpp',
		}
	end

	-- Include dir
	includedirs {
		options.dir .. 'public/',
	}

	if options.link then
		-- Lib dir
		if os.get() == 'windows' then
			configuration(unet_merge_config(options.config, 'x64'))
				libdirs {
					options.dir .. 'redistributable_bin/win64/',
				}
			configuration(unet_merge_config(options.config, 'x32'))
				libdirs {
					options.dir .. 'redistributable_bin/',
				}
		elseif os.get() == 'linux' then
			configuration(unet_merge_config(options.config, 'x64'))
				libdirs {
					options.dir .. 'redistributable_bin/linux64/',
				}
			configuration(unet_merge_config(options.config, 'x32'))
				libdirs {
					options.dir .. 'redistributable_bin/linux32/',
				}
		elseif os.get() == 'macosx' then
			libdirs {
				options.dir .. 'redistributable_bin/osx32/',
			}
		end

		-- Link
		if os.get() == 'windows' then
			configuration(unet_merge_config(options.config, 'x64'))
				links { 'steam_api64' }
			configuration(unet_merge_config(options.config, 'x32'))
				links { 'steam_api' }
		else
			configuration(options.config)
				links { 'steam_api' }
		end
	end
end
