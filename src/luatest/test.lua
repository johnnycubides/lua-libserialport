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

local options = {
	baudRate = 115200,
	flowControl = 0,
	rts = 0,
	dtr = 0,
}

-- local port, error = serial.open(ports[3], options)
local port, error = serial.open("/dev/ttyUSB0", options)
assert(port, error)

serial.read(port, 10000, 3000)

serial.write(port, "\n", 100)
serial.read(port, 100, 300)
local dataout = "print(1+1)\n"
print(serial.write(port, dataout, 1000))
local res = serial.close(port)
assert(res, "No fue posible cerrar el puerto ")
