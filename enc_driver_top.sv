module enc_driver_top(
    input   logic   clk,
    output  logic   SCLK,
    output  logic   MOSI,
    input   logic   MISO,
    output  logic   SS
);
    
    logic   run_req = 1'b1;
    logic   end_flag;
    logic   [7:0]   write_data = 8'h00;
    logic   [2:0]   opcode = 3'b11;
    logic   [4:0]   write_addr = 5'b11111;

    logic   [15:0]  q;
    logic   [7:0]   address = 8'h00;

    always_ff @(posedge clk) begin
        if(address == 16'h9c) begin
            address <= address;
            run_req <= 1'b1;
        end else if(end_flag) begin
            address <= address + 8'h1;
            run_req <= 1'b1;
        end else begin
            address <= address;
            run_req <= 1'b0;
        end
    end

    ROM ROM(
        .address    (address),
        .clock      (clk    ),
        .q          (q      )
    );
	 
	assign {opcode, write_addr, write_data} = q;

    enc_driver enc_driver(
        .clk        (clk        ),
        .SCLK       (SCLK       ),
        .MOSI       (MOSI       ),
        .MISO       (MISO       ),
        .SS         (SS         ),
        .run_req    (run_req    ),
        .end_flag   (end_flag   ),
        .write_data (write_data ),
        .opcode     (opcode     ),
        .write_addr (write_addr )
    );

endmodule
