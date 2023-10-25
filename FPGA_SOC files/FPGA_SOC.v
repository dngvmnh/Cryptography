module FPGA_SOC(
	input 			CLOCK_50,
	input 	[0:0] 	KEY, 
	output	[9:0]	LEDR
);


system nios_system(
	.clk_clk 		(CLOCK_50),
	.reset_reset_n	(KEY[0]),
	.led_external_connection_export({22'd0, LEDR})
);

endmodule

