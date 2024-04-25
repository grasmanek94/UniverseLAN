local DIR_ROOT = (path.getabsolute('..') .. '/')
local DIR_CLI = DIR_ROOT .. 'cli/'

dofile('genie_common.lua')

function unet_cli_project(options)
	options = unet_verify_options(options)

	project 'unet_cli'
		kind('ConsoleApp')

		configuration 'Debug'
			debugdir(DIR_ROOT .. 'bin/debug/')

		configuration 'Release'
			debugdir(DIR_ROOT .. 'bin/release/')

		configuration {}

		unet_defines()
		unet_modules(options.modules)
		unet_guid()

		-- Files
		files {
			DIR_CLI .. '**.cpp',
			DIR_CLI .. '**.c',
			DIR_CLI .. '**.hpp',
			DIR_CLI .. '**.h',
		}

		-- Includes
		includedirs {
			DIR_CLI,
			DIR_ROOT .. 'include/',
		}

		-- Links
		links {
			'unet',
		}

		-- Specify rpath
		if os.get() == 'linux' then
			linkoptions { '-Wl,-rpath,.' }
		elseif os.get() == 'macosx' then
			linkoptions { '-Wl,-rpath,"@loader_path",-rpath,.' }
		end

		-- On Windows, disable permissive compiling for more healthy Windows errors
		if os.get() == 'windows' then
			buildoptions { '/permissive-' }
		end
end
