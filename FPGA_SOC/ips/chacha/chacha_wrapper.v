module chacha_wrapper(
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
wire       wWrite_enable_to_chacha;


// Combinational logics
assign wWrite_enable_to_chacha = iWrite & !(iRead);


// Module instances
chacha DUT(
    .clk            (iClk),
    .reset_n        (iReset_n),

    .cs             (iChipselect),
    .we             (wWrite_enable_to_chacha),

    .addr           (iAddress),
    .write_data     (iWrite_data),

    .read_data      (oRead_data)
);

endmodule
