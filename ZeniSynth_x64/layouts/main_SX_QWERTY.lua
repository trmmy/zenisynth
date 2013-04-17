dofile("layouts/SX_base.lua")

dofile("layouts/SX_XR.lua")
dofile("layouts/SX_XL.lua")
dofile("layouts/SX_XR2.lua")

out("SX :: Synergistic eXtended")



function main(vkCode,scanCode,flags,altdown)

	SX.acquire(vkCode,scanCode,flags)

	--XL ( Mouse , Symbols )
	if SX.XL() then return end
	if SX.XR() then return end
	if SX.XR2() then return end
	sendInput(VK,scanCode,flags)


end