




module top (
    input wire [7:0] datain,
    output reg [7:0] dataout,
    input wire dataclk,
    input wire seeddata,
    input wire setseed,
    input wire streamdata
);
    

    // seed data buffer
    reg [15:0] seeddatabuffer [8:0];

    // key buffer
    reg [7:0] keybuffer;
    wire [7:0] keybufferwire;
    always @* keybuffer[7:0] = keybufferwire[7:0];

    linearfeedbackshiftregister16 mylfsr_0( .seed(seeddatabuffer[0]) , .setseed(setseed) , .clk(dataclk) , .outputbit(keybufferwire[0]) );
    linearfeedbackshiftregister16 mylfsr_1( .seed(seeddatabuffer[1]) , .setseed(setseed) , .clk(dataclk) , .outputbit(keybufferwire[1]) );
    linearfeedbackshiftregister16 mylfsr_2( .seed(seeddatabuffer[2]) , .setseed(setseed) , .clk(dataclk) , .outputbit(keybufferwire[2]) );
    linearfeedbackshiftregister16 mylfsr_3( .seed(seeddatabuffer[3]) , .setseed(setseed) , .clk(dataclk) , .outputbit(keybufferwire[3]) );
    linearfeedbackshiftregister16 mylfsr_4( .seed(seeddatabuffer[4]) , .setseed(setseed) , .clk(dataclk) , .outputbit(keybufferwire[4]) );
    linearfeedbackshiftregister16 mylfsr_5( .seed(seeddatabuffer[5]) , .setseed(setseed) , .clk(dataclk) , .outputbit(keybufferwire[5]) );
    linearfeedbackshiftregister16 mylfsr_6( .seed(seeddatabuffer[6]) , .setseed(setseed) , .clk(dataclk) , .outputbit(keybufferwire[6]) );
    linearfeedbackshiftregister16 mylfsr_7( .seed(seeddatabuffer[7]) , .setseed(setseed) , .clk(dataclk) , .outputbit(keybufferwire[7]) );
    


    always @(posedge dataclk)
    begin

        // if we have seed data to clock in...
        if ( seeddata )
        begin
            seeddatabuffer[7][15:8] <= seeddatabuffer[7][7:0];
            seeddatabuffer[7][7:0] <= seeddatabuffer[6][15:8];
            seeddatabuffer[6][15:8] <= seeddatabuffer[6][7:0];
            seeddatabuffer[6][7:0] <= seeddatabuffer[5][15:8];
            seeddatabuffer[5][15:8] <= seeddatabuffer[5][7:0];
            seeddatabuffer[5][7:0] <= seeddatabuffer[4][15:8];
            seeddatabuffer[4][15:8] <= seeddatabuffer[4][7:0];
            seeddatabuffer[4][7:0] <= seeddatabuffer[3][15:8];
            seeddatabuffer[3][15:8] <= seeddatabuffer[3][7:0];
            seeddatabuffer[3][7:0] <= seeddatabuffer[2][15:8];
            seeddatabuffer[2][15:8] <= seeddatabuffer[2][7:0];
            seeddatabuffer[2][7:0] <= seeddatabuffer[1][15:8];
            seeddatabuffer[1][15:8] <= seeddatabuffer[1][7:0];
            seeddatabuffer[1][7:0] <= seeddatabuffer[0][15:8];
            seeddatabuffer[0][15:8] <= seeddatabuffer[0][7:0];
            seeddatabuffer[0][7:0] <= datain[7:0];
        end

        if ( streamdata )
        begin
            dataout[7:0] <= keybuffer[7:0] ^ datain[7:0];
        end
        
    end




endmodule








module linearfeedbackshiftregister16 (
    
    // seed value input
    input wire [15:0] seed,
    // set seed value
    input wire setseed,
    // clock input
    input wire clk,
    // lsft output
    output reg outputbit

);
    
    // 16 bits of shift register storage
    reg [15:0] theactualregister;
        
    // whenever the clock goes high
    always @(posedge clk) begin
        
        // if we are setting the seed
        if (setseed) begin
            // copy the seed into the register
            theactualregister[15:1] <= seed[14:0];
            // calculate the new bit
            theactualregister[0] <= ( ( ( seed[15] ^ seed[13] ) ^ seed[12] ) ^ seed[10] );

        end
        // if we are not setting the seed
        else begin
            
            // put the old bit on the output
            outputbit <= theactualregister[15];

            // shift the register
            theactualregister[15:1] <= theactualregister[14:0];

            // calculate the new bit
            theactualregister[0] <= ( ( ( theactualregister[15] ^ theactualregister[13] ) ^ theactualregister[12] ) ^ theactualregister[10] );
            
        end

    end

endmodule




































































