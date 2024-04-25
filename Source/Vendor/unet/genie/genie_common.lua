local DIR_GENIE = (path.getabsolute('.') .. '/')

-- Verifies and returns a valid options object
function unet_verify_options(options)
	if not options then options = {} end
	if not options.modules then options.modules = { enet = { link = true } } end
	return options
end

function unet_merge_config(cfg, filter)
	local ret = {}

	if type(cfg) == 'table' then
		for _, v in ipairs(cfg) do
			table.insert(ret, v)
		end
	else
		table.insert(ret, cfg)
	end

	if type(filter) == 'table' then
		for _, v in ipairs(filter) do
			table.insert(ret, v)
		end
	else
		table.insert(ret, filter)
	end

	return ret
end

-- Include the standard defines for Unet.
function unet_defines()
	if os.get() == 'windows' then
		defines {
			'PLATFORM_WINDOWS',
			'_CRT_SECURE_NO_WARNINGS',
			'NOMINMAX',
		}
	elseif os.get() == 'linux' then
		defines { 'PLATFORM_LINUX' }
	elseif os.get() == 'macosx' then
		defines { 'PLATFORM_MACOS' }
	end

	configuration 'Debug'
		defines { 'DEBUG' }
	configuration 'Release'
		defines {
			'NDEBUG',
			'RELEASE',
		}
	configuration {}
end

-- Include all modules from the given list
function unet_modules(modules, core)
	for k, v in pairs(modules) do
		local f = dofile(DIR_GENIE .. 'genie_service_' .. k .. '.lua')
		if f then
			f(v, core)
			configuration(v.config or {})
			defines { 'UNET_MODULE_' .. k:upper() }
			configuration {}
		else
			error('Unable to find service module ' .. k .. '!')
		end
	end
end

-- Sets the project up for building with the guid code
function unet_guid()
	-- Guid defines
	if os.get() == 'windows' then
		defines { 'GUID_WINDOWS' }
	elseif os.get() == 'linux' then
		defines { 'GUID_LIBUUID' }
	elseif os.get() == 'macosx' then
		defines { 'GUID_CFUUID' }
	else
		defines { 'GUID_GENERIC' }
	end

	-- Guid links
	if os.get() == 'linux' then
		links { 'uuid' }
	elseif os.get() == 'macosx' then
		links { 'CoreFoundation.framework' }
	end
end
