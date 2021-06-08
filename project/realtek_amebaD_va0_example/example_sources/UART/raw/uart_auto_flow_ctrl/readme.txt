Example Description

This example demo the function of Auto Flow control.
Please connect 2 board to run this example.

Required Components:
    2 EV boards
		
Connect to 2 borads

Board1                  Board2
PA18(TX)    <----->     PA19(RX)
PA19(RX)    <----->     PA18(TX)
PA17(CTS)   <----->     PA16(RTS)
PA16(RTS)   <----->     PA17(CTS)
GND         <----->     GND

This example shows:
The first powered board will be the TX side, the othse one will be the RX side.
The RX side will make some delay every 16-bytes received, by this way we can trigger the flow control mechanism.

