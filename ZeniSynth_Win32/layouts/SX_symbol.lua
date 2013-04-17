
function SX.symbol()
	if XL then
		if SCAN==SC_H then
			if SHIFT then
				sendScan(SC_YENANDBAR,UP) return true
			else
				sendScan(SC_LSHIFT,false) sendScan(SC_7,UP) sendScan(SC_LSHIFT,true) return true
			end
		elseif SCAN==SC_U then
			if SHIFT then sendScan(SC_YENANDBAR,UP) return true
			else	sendScan(SC_LSHIFT,false) sendScan(SC_6,UP) sendScan(SC_LSHIFT,true) return true
			end
		elseif SCAN==SC_N then
			if SHIFT then SHIFT=false sendScan(SC_LSHIFT,true) sendScan(SC_YENANDBAR,UP) sendScan(SC_LSHIFT,false) SHIFT=true return true
			else sendScan(SC_LSHIFT,false) sendScan(SC_2,UP) sendScan(SC_LSHIFT,true) return true
			end
		elseif SCAN==SC_O then	sendScan(SC_SLASH,UP) return true
		elseif SCAN==SC_P then
			sendScan(SC_LSHIFT,false) sendScan(SC_QUOTE,UP) sendScan(SC_LSHIFT,true) return true
		elseif SCAN==SC_J then
			if SHIFT then
				sendScan(SC_LSHIFT,false) sendScan(SC_COMMA,UP) sendScan(SC_LSHIFT,true) return true
			else
				sendScan(SC_LSHIFT,false) sendScan(SC_8,UP) sendScan(SC_LSHIFT,true) return true
			end
		elseif SCAN==SC_I then
			if SHIFT then
				sendScan(SC_LSHIFT,false) sendScan(SC_PERIOD,UP) sendScan(SC_LSHIFT,true) return true
			else
				sendScan(SC_LSHIFT,false) sendScan(SC_9,UP) sendScan(SC_LSHIFT,true) return true
			end
		elseif SCAN==SC_K then
			if SHIFT then
				SHIFT=false sendScan(SC_LSHIFT,true) sendScan(SC_RSQUAREBRACKET,UP) sendScan(SC_LSHIFT,false) SHIFT=true return true
			else
				sendScan(SC_LSHIFT,false) sendScan(SC_RSQUAREBRACKET,UP) sendScan(SC_LSHIFT,true) return true

			end
		elseif SCAN==SC_L then
			if SHIFT then
				SHIFT=false sendScan(SC_LSHIFT,true) sendScan(SC_BACKSLASH,UP) sendScan(SC_LSHIFT,false) SHIFT=true return true
			else
				sendScan(SC_LSHIFT,false) sendScan(SC_BACKSLASH,UP) sendScan(SC_LSHIFT,true) return true
			end
		elseif SCAN==SC_COMMA then
			sendScan(SC_LSHIFT,false) sendScan(SC_SEMICOLON,UP) sendScan(SC_LSHIFT,true) return true
		elseif SCAN==SC_PERIOD then
			sendScan(SC_MINUS,UP) return true
		elseif SCAN==SC_SEMICOLON then
			if SHIFT then
				sendScan(SC_LSHIFT,false) sendScan(SC_REVERSESOLIDUS,UP) sendScan(SC_LSHIFT,true) return true
			else
				sendScan(SC_LSHIFT,false) sendScan(SC_MINUS,UP) sendScan(SC_LSHIFT,true) return true
			end
		end
	end

	return false
end