SX={}
VK=0
SCAN=0
DOWN=false
ONESHOT=false
R=false
RCOUNT=0
UP=false
XL=false
XL2=false
XR=false
XR2=false

VK_XR=VK_CONVERT
VK_XL=VK_NONCONVERT
VK_XR2=VK_OEM_COPY
VK_XL2=VK_LWIN
SC_XR=SC_CONVERT
SC_XL=SC_NONCONVERT
SC_XR2=SC_KANA
SHIFT=false
CTRL=false

function sendScan(scanCode,up)

--	if up == nil then
--		sendScan(scanCode,false)
--		sendScan(scanCode,true)
--	else
		flags=KEYEVENTF_SCANCODE
		if up then flags=flags+KEYEVENTF_KEYUP end
		
		-- put an extended flag if this key cord is special
		if 0xE000 <= scanCode then
			flags=flags+KEYEVENTF_EXTENDEDKEY
			scanCode=scanCode-0xE000
		end
	--	if SHIFT then flags=flags+KEYEVENTF_EXTENDEDKEY end
		sendInput(0,scanCode,flags)
--	end
end

function key(vkCode)
	key(vkCode,false)
	key(vkCode,true)
end

function key(vkCode,up)
	flags=0
	if up then flags=KEYEVENTF_KEYUP end
	if SHIFT then flags=flags+KEYEVENTF_EXTENDEDKEY end
	sendInput(vkCode,0,flags)
end


function SX.acquire(vkCode,scanCode,flags)
	SCAN=scanCode
	prevVK=VK
	prevDOWN=DOWN
	VK=vkCode

	DOWN=AND(flags,KEYEVENTF_KEYUP)==0
	UP=DOWN~=true

	if prevVK==VK then
		ONESHOT=true
		if DOWN and prevDOWN then
			R=true
			RCOUNT=RCOUNT+1
		else
			RCOUNT=0
		end
	else
		ONESHOT=false
		R=false
		RCOUNT=0
	end

	if VK==VK_SHIFT or VK==VK_LSHIFT or VK==VK_RSHIFT or SCAN==SC_LSHIFT or SCAN==SC_RSHIFT then

		SHIFT = DOWN
	end

	if SCAN==SC_CAPSLOCK then
		VK=VK_CONTROL
		SCAN=SC_CAPSLOCK
	end

	if VK==VK_CONTROL or SCAN==SC_LCTRL or SCAN==SC_RCTRL then
		CTRL = DOWN
	end

	if SCAN==SC_XR then
		XR=DOWN
	elseif SCAN == SC_XL then
		XL=DOWN
	elseif SCAN == SC_XR2 then

		XR2=DOWN
	end

--	press,toggle=getKeyState(VK_OEM_COPY)
--	out("vk="..VK)
--	out("scan="..SCAN)
--	out("down="..tostring(DOWN))
--	out("press="..tostring(press))
--	out("toggle="..tostring(toggle))
--	out("----")
end