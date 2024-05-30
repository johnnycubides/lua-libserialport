# lua-libserialport

Se crea esta librería que funciona con Lua en su versión 5.4.6, que hace uso de
libserialport, permite las diferentes configuraciones, control a través de timeout,
para lectura y escritura de datos y control de dtr, rts para algunas tarjetas
de desarrollo que requieren un estado incial de estas para su funcionamiento.

## Descarga y compilación de librería

### Plataforma Linux

Descargar y compilar las dependendencias:

```
make libserialport-linux lua-linux
cd src/
make all
make dist-linux
```

Lo anterior genera el comprimido `libserial.zip` que puede usar con la
versión de Lua indicada.

Si desea puede hacer pruebas de la librería con el script de prueba con el comando:

```
make test
```

### Plataforma Windows

TODO: Requiere crear los scripts


### Importación de librería

```lua
-- libserial.so depende de la librería compartida lib/libserialport.so.0
-- Con la siguiente instrucción es localizada relativamente
package.cpath = package.cpath .. ";./lib/?.so"

-- Importar la librería serial para usar en lua
local serial = require("libserial")
```

### Busqueda de puertos seriales

Función:

```lua
local ports = serial.list_ports()
```

Ejemplo:

```lua
-- Obtener información sobre los diferentes puertos seriales
local ports = serial.list_ports()

-- si ports == nil se muestra el mensaje como error
assert(ports, "No hay puertos seriales disponibles")

-- Ver puertos disponibles
for key, value in pairs(ports) do
	print(key .. ": " .. value)
end
```

### Abrir un puerto serial

Función:

```lua
local port, error = serial.open("/dev/ttyUSB0", options)
```

Ejemplo:

```lua
local options = {
  baudRate = 115200
}

local port, error = serial.open("/dev/ttyUSB0", options)

-- En el caso de no poder abrir el puerto, error indica la razón posible.
assert(port, error)
```

La variable `options` que representa una tabla puede tener cualquiera de los valores que se muestran
a continuación comentados, los que están seleccionados son los que se dan por default.

Opciones:
```lua
local options = {
  baudRate = 9600,  -- 9600, 19200, 38400, 57600, 115200 
  bits = 8,         -- 7, 8
  parity = 0,       -- SP_PARITY_INVALID = -1, SP_PARITY_NONE = 0,
                    -- SP_PARITY_ODD = 1, SP_PARITY_EVEN = 2,
                    -- SP_PARITY_MARK = 3, SP_PARITY_SPACE = 4 
  stopBits = 1,
  flowControl = 0,  -- SP_FLOWCONTROL_NONE = 0, SP_FLOWCONTROL_XONXOFF = 1,
                    -- SP_FLOWCONTROL_RTSCTS = 2, SP_FLOWCONTROL_DTRDSR = 3 
  dtr = -1,          -- SP_DTR_INVALID = -1, SP_DTR_OFF = 0,
                    -- SP_DTR_ON = 1, SP_DTR_FLOW_CONTROL = 2 
  rts = -1,          -- SP_RTS_INVALID = -1, SP_RTS_OFF = 0,
                    -- SP_RTS_ON = 1, SP_RTS_FLOW_CONTROL = 2 
  cts = 0,          -- SP_CTS_INVALID = -1,
                    -- SP_CTS_IGNORE = 0,
                    -- SP_CTS_FLOW_CONTROL = 1 
}
```
### Leer del puerto serial

Función:

```lua
local data_in, received_size = serial.read(port, data_in_size, timeout_ms)
```

Ejemplo:

```lua
local data_in_size = 3 -- Cantidad de datos a recibir
local timeout_ms = 1000 -- Esperar en milisegundos
local data_in, received_size = serial.read(port, data_in_size, timeout_ms)
if data_in then
  if received_size == size_data_in then
    print("Se recibieron la cantidad de datos esperados")
  end
  print("datain: " .. data_in .." received_size: " .. received_size)
else
  print("No se recibieron datos")
end
```

**Nota**: Si `timeout_ms = 0` la aplicación se bloquea hasta recibir los datos indicados en `size_data_in` por el puerto.

### Escribir en el puerto serial

Es importante indica que no se envía al final ningún comando especial como "\r\n", si los requiere debe agregarlos 
en el string a enviar.

Función:

```lua
local result = serial.write(port, data_out, timeout_ms)
```

Ejemplo:

```lua
local data_out = "hello!"
local timeout _ms = 1000 -- Esperar en milisegundos
local result = serial.write(port, data_out, timeout_ms)
if result then
  print("Cantidad de datos enviados: " .. result)
end
```

**Nota**: Si `timeout_ms = 0`la aplicación se bloquea hasta enviar todos los datos indicados.

### Cerrar puerto serial

Función:

```lua
local result = serial.close(port)
```

Ejemplo:

```lua
local result = serial.close(port)
-- Si result = nil se genera el error indicado en el mensaje
assert(result, "No fue posible cerrar el puerto")
```

### Referencias

* [libserialport api](https://www.sigrok.org/api/libserialport/0.1.1/index.html)
* [lua 5.4](https://www.lua.org/manual/5.4/)
* [jpnevulator](https://jpnevulator.snarl.nl/)

Regards:

Johnny Cubides
