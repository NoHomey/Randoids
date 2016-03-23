import output = require('./driver/output/output');
import input = require('./driver/input/input');

var out: output.Output = new output.Output(1, 2, 3, 4);
out.write(new Uint16Array([1, 3, 5, 7, 9, 2, 4, 6, 8, 0]));
var buttons: number = input();
console.log("Input:", buttons);