dofile("layouts/SX_base.lua")

dofile("layouts/SX_XR.lua")
dofile("layouts/SX_XL.lua")
dofile("layouts/SX_XR2.lua")
dofile("layouts/SX_QwertyToSX.lua")
dofile("layouts/app/Blender.lua")

out("SX :: Synergistic eXtended")

--a=cdata.new(10)

function main(vkCode,scanCode,flags,altdown)

	SX.acquire(vkCode,scanCode,flags)
--out(scanCode)
	--XL ( Mouse , Symbols )
	
	if SX.XR() then return end
	if SX.XR2() then return end
	
	if false
	or string.match(system.getActiveWindowName(),"^Half[-]Life.*")
	or string.match(system.getActiveWindowName(),"^Mirror's Edge.*")
	or string.match(system.getActiveWindowName(),"^HALF[-]LIFE.*")
	or string.match(system.getActiveWindowName(),"^FX11.*")
	or string.match(system.getActiveWindowName(),"^World of Warcraft*")
	or string.match(system.getActiveWindowName(),"^- Crysis.*")
	or string.match(system.getActiveWindowName(),"^Unreal Tournament.*")
	or string.match(system.getActiveWindowName(),"^S[.]T[.]A[.]L[.]K[.]E[.]R[.].*")
	or string.match(system.getActiveWindowName(),"^Halo")
	or string.match(system.getActiveWindowName(),"^Halo 2.*")
	or string.match(system.getActiveWindowName(),"^Lost Planet Ver.*")
	or string.match(system.getActiveWindowName(),"^Versatile Engine demo.*")
	or string.match(system.getActiveWindowName(),"^Nexuiz.*")
	or string.match(system.getActiveWindowName(),"^WarRock.*")
	or string.match(system.getActiveWindowName(),"^DOOM 3.*")
	or string.match(system.getActiveWindowName(),"^Trine.*")
	or string.match(system.getActiveWindowName(),"^Modern Warfare 2.*")
	or string.match(system.getActiveWindowName(),"^Borderlands.*")
	or string.match(system.getActiveWindowName(),"^Shattered Horizon")
	then
		if scanCode==SC_NONCONVERT then
			scanCode=SC_NUM0
		elseif scanCode==SC_TILDE then
			sendInput(VK,scanCode,flags)
			system.setIMEStatus(false)
		end
	else
		if SX.XL() then return end
		if string.match(system.getActiveWindowName(),"^Blender.*") then
			if SX.Blender() then return end
		elseif false
		or string.match(system.getActiveWindowTopName(),"^Left 4 Dead")
		or string.match(system.getActiveWindowTopName(),"^Autodesk Softimage.*")
		then
		else
			if SX.QwertyToSX() then return end
		end
	end
	sendInput(VK,scanCode,flags)

--out(a:size())
--out(a:getPtr())
--a.rawSet(a:getPtr(),0x6463,4);
--out(a.rawGet(a:getPtr(),1));
end