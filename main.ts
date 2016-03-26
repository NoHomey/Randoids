import output = require('./driver/output/output');
import input = require('./driver/input/input');

const chips: number = 8;
const data: number = 0;
const clock: number = 2;
const latch: number = 3;
const wiring: string = "BRG";
var buttons: number = input();
var out: output.Output = new output.Output(chips, data, clock, latch, wiring);
out.setup();
for(var i: number = 0; i < 64; ++i) {
    out.setRGBLED(i, new Uint16Array([4000, 1000, 2000]));
}
out.write();
