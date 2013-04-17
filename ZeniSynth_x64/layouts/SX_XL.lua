dofile("layouts/SX_mouse.lua")
dofile("layouts/SX_symbol.lua")

function SX.XL()

	if SCAN==SC_XL and ONESHOT and UP then
		if isIMEConverting() then
			SHIFT=false sendScan(SC_F10) SHIFT=true
		else
			system.setIMEStatus(false)
		end
		return true
	end


	if SX.mouse() then return true end

	if XL then
		if SX.symbol() then return true
		elseif SCAN==SC_XL then return true
		elseif SCAN==SC_1 then sendScan(SC_F1,UP) return true
		elseif SCAN==SC_2 then sendScan(SC_F2,UP) return true
		elseif SCAN==SC_3 then sendScan(SC_F3,UP) return true
		elseif SCAN==SC_4 then sendScan(SC_F4,UP) return true
		elseif SCAN==SC_5 then sendScan(SC_F5,UP) return true
		elseif SCAN==SC_6 then sendScan(SC_F6,UP) return true
		elseif SCAN==SC_7 then sendScan(SC_F7,UP) return true
		elseif SCAN==SC_8 then sendScan(SC_F8,UP) return true
		elseif SCAN==SC_9 then sendScan(SC_F9,UP) return true
		elseif SCAN==SC_0 then sendScan(SC_F10,UP) return true
		elseif SCAN==SC_MINUS then sendScan(SC_F11,UP) return true
		elseif SCAN==SC_EQUAL then sendScan(SC_F12,UP) return true
		end
	end
	return false
end