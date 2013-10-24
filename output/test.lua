require 'std' -- load lua standard library for pretty printing etc.

pprint = function(arg) print(prettytostring(arg)) end

require 'macadr' -- load browse function from browse0conf module

pprint(macadr) -- print conf0 module to see what we have

function printmac(ip) print(ip, pcall(macadr.read, {ip = ip})) end

printmac('192.168.10.84')
printmac('192.168.10.97')
printmac('192.168.10.174')