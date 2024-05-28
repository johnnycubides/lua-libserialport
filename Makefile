
lua-linux:
	@echo "Descarga compilación o crosscompilación de Lua"
	bash ./scripts/lua.bash download
	bash ./scripts/lua.bash build-linux
	bash ./scripts/lua.bash install-linux
	
