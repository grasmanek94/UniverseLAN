local DIR_ROOT = (path.getabsolute('..') .. '/')

dofile('genie_common.lua')

function unet_project(options)
	options = unet_verify_options(options)

	project 'unet'
		kind 'StaticLib'

		includedirs {
			DIR_ROOT .. 'include/',
		}

		pchheader 'Unet_common.h'
		pchsource(DIR_ROOT .. 'src/Unet_common.cpp')

		unet_defines()
		unet_modules(options.modules, true)
		unet_guid()

		-- Files
		files {
			DIR_ROOT .. 'src/*.cpp',
			DIR_ROOT .. 'src/*.c',
			DIR_ROOT .. 'src/Results/*.cpp',
			DIR_ROOT .. 'include/**.hpp',
			DIR_ROOT .. 'include/**.h',
		}

		-- Remove xxhash.cpp because we're using it with XXH_INLINE_ALL
		removefiles { DIR_ROOT .. 'src/xxhash.cpp' }
		defines { 'XXH_INLINE_ALL' }

		-- System sources
		if os.get() == 'windows' then
			files {
				DIR_ROOT .. 'src/System/SystemWindows.cpp',
			}
		elseif os.get() == 'linux' then
			files {
				DIR_ROOT .. 'src/System/SystemLinux.cpp',
			}
		elseif os.get() == 'macosx' then
			files {
				DIR_ROOT .. 'src/System/SystemMacOS.mm',
			}
		end

		-- On Windows, disable permissive compiling for more healthy Windows errors
		if os.get() == 'windows' then
			buildoptions { '/permissive-' }
		end
end
