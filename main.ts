import output = require('./driver/output/output');
import input = require('./driver/input/input');

var buttons: number = input();
var out: output.Output = new output.Output(8, 0, 2, 3);
out.setup();
for(var i: number = 0; i < 64; ++i) {
    out.setRGBLED(i, new Uint16Array([2000, 4000, 1000]));
}
out.write();
