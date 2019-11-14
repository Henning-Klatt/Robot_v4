~/.platformio/packages/tool-avrdude/avrdude -C ~/.platformio/packages/tool-avrdude/avrdude.conf -P usb -c usbtiny -p m328pb -U efuse:w:0xFD:m
~/.platformio/packages/tool-avrdude/avrdude -C ~/.platformio/packages/tool-avrdude/avrdude.conf -P usb -c usbtiny -p m328pb -U hfuse:w:0xDA:m
~/.platformio/packages/tool-avrdude/avrdude -C ~/.platformio/packages/tool-avrdude/avrdude.conf -P usb -c usbtiny -p m328pb -U lfuse:w:0xFF:m
