function SX.XR2()

	if XR2 then
		if SCAN==SC_E then sendScan(SC_UP,UP) return true
		elseif SCAN==SC_D then sendScan(SC_DOWN,UP) return true
		elseif SCAN==SC_S then sendScan(SC_LEFT,UP) return true
		elseif SCAN==SC_F then sendScan(SC_RIGHT,UP) return true
		elseif SCAN==SC_SPACE then sendScan(SC_BS,UP) return true

		elseif SCAN==SC_Y then sendScan(SC_NUMLOCK,UP) return true
		elseif SCAN==SC_N then sendScan(SC_NUM0,UP) return true
		elseif SCAN==SC_M then sendScan(SC_NUM1,UP) return true 
		elseif SCAN==SC_COMMA then sendScan(SC_NUM2,UP) return true 
		elseif SCAN==SC_PERIOD then sendScan(SC_NUM3,UP) return true 
		elseif SCAN==SC_J then sendScan(SC_NUM4,UP) return true 
		elseif SCAN==SC_K then sendScan(SC_NUM5,UP) return true 
		elseif SCAN==SC_L then sendScan(SC_NUM6,UP) return true 
		elseif SCAN==SC_U then sendScan(SC_NUM7,UP) return true 
		elseif SCAN==SC_I then sendScan(SC_NUM8,UP) return true
		elseif SCAN==SC_O then sendScan(SC_NUM9,UP) return true

--		elseif VK==SC_XR2 then return true
		end
	end
	if SCAN==SC_KANA then

		conv=isIMEConverting()		
--		out(conv)
		if conv then
			sendScan(SC_F7,UP)
		end
		return true
	end

	return false
end