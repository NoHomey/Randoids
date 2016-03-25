import output = require('./driver/output/output');
import input = require('./driver/input/input');

var out: output.Output = new output.Output(8, 2, 0, 3, "BRG");
var arr: number[] = new Array<number>(192);

for(var i: number = 0; i < 64; ++i) {
    console.log(i);
    out.setRGBLED(i, new Uint16Array(4100, 0, 0));
}
out.write();
var buttons: number = input();