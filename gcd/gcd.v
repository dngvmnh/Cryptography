/*
 *		(G)reatest (C)ommon (D)ivider
 * 			Khai Minh Ma - 2023
 */

module gcd (
	input wire			iClk,
	input wire			iRst,

	input wire			iValid,
	input wire [15:0]	iA,
	input wire [15:0]  	iB,

	output reg			oValid, // ?? what for
	output reg			oReady,	// USED
	output reg [15:0]	oC
	);


reg [15:0] 	internal_input_A;
reg [15:0] 	internal_input_B;
reg [15:0]	internal_Swap;
reg 		internal_Run;

reg [15:0] 	internal_output_C;


always@(posedge iClk or posedge iRst)
begin

	if(iRst)					// if reset - reset
	begin
		internal_input_A 	<= 16'd0;
		internal_input_B 	<= 16'd0;
		internal_Swap 		<= 16'd0;
		internal_Run 		<= 1'b0;

		internal_output_C 	<= 16'd0;

		oValid 				<= 1'b0;
		oReady 				<= 1'b0;
	end


	// -----------------------------------------------------------------------------------------------
	else 
	begin 						// if not reset - then operate
								
		if(iValid)				// input is valid - get input, reset and config some control signals
		begin
			internal_input_A <= iA;
			internal_input_B <= iB;
			internal_Run 	 <= 1'b1;

			oValid 	<= 1'b0;
			oReady 	<= 1'b0;
		end

		else if (oValid)
		begin
			oReady 		<= oValid; 
			oValid 		<= 1'b0;
			oC 			<= internal_output_C;
		end




		if(internal_Run)
		begin

			oValid 		<= oValid;
			oReady 		<= oReady;

			if(internal_input_B == 16'd0)
			begin
				internal_Run 		<= 1'b0;
				oValid 				<= 1'b1;
				internal_output_C 	<= internal_input_A;
			end

			else if (internal_input_A > internal_input_B) 
			begin
				internal_Swap 	 = internal_input_A;
				internal_input_A = internal_input_B;
				internal_input_B = internal_Swap;
			end

			else
				internal_input_B <= internal_input_B - internal_input_A;

		end

	end
	// -----------------------------------------------------------------------------------------------





end

endmodule
