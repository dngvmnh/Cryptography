module test (
input [1:0] in,
input sel,
output out
);
assign out = sel ? in[1] : in[0];

endmodule