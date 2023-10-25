`timescale 1ns / 1ps

module gcd_tb ( );

reg			tb_iClk;
reg			tb_iRst;
reg			tb_iValid;
reg [15:0]	tb_iA;
reg [15:0]  tb_iB;

wire		tb_oValid;
wire		tb_oRead;
wire [15:0]	tb_oC;
// --------------------------------------------------------------



initial begin
	tb_iClk 	<= 1'b0;
	tb_iRst 	<= 1'b1;
	tb_iValid 	<= 1'b0;
	tb_iA 		<= 16'd0;
	tb_iB 		<= 16'd0;
end


parameter CLOCK_PERIOD = 10;
always
	begin : Clock_Generator
		#((CLOCK_PERIOD) / 2) tb_iClk <= ~tb_iClk;
	end



initial begin
	#3 tb_iRst <= 1'b0;

	@(negedge tb_iClk);
	tb_iA 		<= 16'd31;
	tb_iB 		<= 16'd3;
	tb_iValid 	<= 1'b1;

	#(CLOCK_PERIOD);
	// @(posedge tb_iClk);
	tb_iValid 	<= 1'b0;

	#200;


	@(negedge tb_iClk);
	tb_iA 		<= 16'd1323;
	tb_iB 		<= 16'd612;
	tb_iValid 	<= 1'b1;

	#(CLOCK_PERIOD);
	// @(posedge tb_iClk);
	tb_iValid 	<= 1'b0;

	#300;


	@(negedge tb_iClk);
	tb_iA 		<= 16'd23532;
	tb_iB 		<= 16'd544;
	tb_iValid 	<= 1'b1;

	#(CLOCK_PERIOD);
	// @(posedge tb_iClk);
	tb_iValid 	<= 1'b0;

	#800 $finish;
end


gcd DUT (
	.iClk(tb_iClk), 
	.iRst(tb_iRst), 

	.iValid(tb_iValid), 
	.iA(tb_iA), 
	.iB(tb_iB), 

	.oValid(tb_oValid), 
	.oReady(tb_oRead), 
	.oC(tb_oC)
	);


endmodule
