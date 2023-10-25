module aes_wrapper(
    // Clock and reset.
    input wire           iClk,
    input wire           iReset_n,

    // Control for Avalon.
    input wire           iChipselect,
    input wire           iWrite,
    input wire           iRead,

    // Data ports.
    input wire  [7 : 0]  iAddress,
    input wire  [31 : 0] iWrite_data,
    output wire [31 : 0] oRead_data
);

// Wires
wire       wWrite_enable_to_prince;


// Combinational logics
assign wWrite_enable_to_prince = iWrite & !(iRead);


// Module instances
aes DUT(
    .clk            (iClk),
    .reset_n        (iReset_n),

    .cs             (iChipselect),
    .we             (wWrite_enable_to_prince),

    .address        (iAddress),
    .write_data     (iWrite_data),

    .read_data      (oRead_data)
);

endmodule
