import output = require('./driver/output/output');
import input = require('./driver/input/input');

var out: output.Output = new output.Output(2, 0, 3, 4);
var arr: number[] = new Array<number>(132);
for(var i: number = 0; i < 132; ++i) {
    arr[i] = !(i % 5) ? 0 : 4095;
}
out.write(new Uint16Array(arr));
var buttons: number = input();
console.log("Input:", buttons);