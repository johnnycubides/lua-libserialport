package.cpath = package.cpath .. ";./lib/?.so"
package.cpath = package.cpath .. ";./?.so"

local serial = require("libserial")

local ports = serial.list_ports()

-- Ver puertos disponibles
for key, value in pairs(ports) do
	print(key .. ": " .. value)
end

assert(ports[3], "Puerto nil")
print(ports[3])

local port, error = serial.open(ports[3])
assert(port, error)

local dataout = "print(1+1)\r\n"
serial.write(port, dataout, 1000)
local res = serial.close(port)
assert(res, "No fue posible cerrar el puerto ")
