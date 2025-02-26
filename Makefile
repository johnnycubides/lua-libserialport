dependencies-windows:
	@echo "Instalación de dependencias para crosscompilación, TARGET=Windows"
	bash ./scripts/libserialport.bash dependencies-windows

lua-download:
	@echo "Descarga de lua"
	bash ./scripts/lua.bash download

lua-linux:
	@echo "Compilación o crosscompilación de Lua"
	bash ./scripts/lua.bash build-linux
	bash ./scripts/lua.bash install-linux

lua-windows:
	@echo "Compilación o crosscompilación de Lua"
	bash ./scripts/lua.bash build-windows
	bash ./scripts/lua.bash install-windows

libserialport-download:
	@echo "Descargar la librería libserialpor"
	bash ./scripts/libserialport.bash download

libserialport-linux:
	@echo "Compilar la librería para Linux"
	# bash ./scripts/libserialport.bash dependencies-linux
	bash ./scripts/libserialport.bash build-linux
	
libserialport-windows:
	@echo "Cross compilar la librería para Windows"
	# bash ./scripts/libserialport.bash dependencies-windows
	bash ./scripts/libserialport.bash build-windows
