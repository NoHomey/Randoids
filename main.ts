/*import wiringPiSetup = require('./driver/wiringPiSetup/wiringPiSetup');
import output = require('./driver/output/output');
import input = require('./driver/input/input');

const chips: number = 8;
const data: number = 0;
const clock: number = 2;
const latch: number = 3;
const wiring: string = "BRG";

wiringPiSetup();

var out: output.Output = new output.Output(chips, data, clock, latch, wiring);
for(var i: number = 0; i < 64; ++i) {
    out.setRGBLED(i, new Uint16Array([4000, 1000, 2000]));
}
out.write();

setTimeout(() => {
    for(var i: number = 0; i < 64; ++i) {
        out.clearRGBLED(i);
    }
    out.write();   
},1000)

var buttons: number = input();*/

import Position = require('./game/Position');
import color = require('./game/Color');

Position.setDirectionMax(8);

