
lua-linux:
	@echo "Descarga compilación o crosscompilación de Lua"
	bash ./scripts/lua.bash download
	bash ./scripts/lua.bash build-linux
	bash ./scripts/lua.bash install-linux

libserialport-linux:
	@echo "Descargar y crear librería libserialport"
	bash ./scripts/libserialport.bash download
	bash ./scripts/libserialport.bash build-linux
	
