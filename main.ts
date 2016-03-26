import wiringPiSetup = require('./driver/wiringPiSetup/wiringPiSetup');
import output = require('./driver/output/output');
import input = require('./driver/input/input');
import Position = require('./game/Position');
import color = require('./game/Color');
import Pixel = require('./game/Pixel');
import GameObject = require('./game/GameObject');
import Range = require('./game/Range');

const chips: number = 8;
const data: number = 0;
const clock: number = 2;
const latch: number = 3;
const wiring: string = "BRG";

wiringPiSetup();
Position.setDirectionMax(chips);

var screen: color.Color[] = new Array<color.Color>(chips * chips);
var out: output.Output = new output.Output(chips, data, clock, latch, wiring);
var shoot: boolean;
var spaceShip: Pixel[] = [
    new Pixel(color.Color.Blue, new Position(0, 0)),
    new Pixel(color.Color.Blue, new Position(0, 1)),
    new Pixel(color.Color.Blue, new Position(0, -1)),
    new Pixel(color.Color.Blue, new Position(1, 0))
];
var player: GameObject = new GameObject(new Position(3, 0), new Position(0, 0), spaceShip);

function updateScreen(): void {
    for(var i: number = 0; i < screen.length; ++i) {
        out.setRGBLED(i, color.ColorToUint16Array(screen[i]);
    }
    out.write();   
}

function readInput(): Position {
    shoot = false;
    var buttons: number = input();
    var left: number = (buttons & 1) ? 1 : 0;
    var right: number = (buttons & 4) ? 1 : 0;
    var x: number = left - right;
    shoot = Boolean(buttons & 2);
    return new Position(x, 0);
}

function move(object: GameObject) {
    for(var i: number = 0; i < object.figure.length; ++i) {
        out.clearRGBLED(object.figure[i].position.toNumber());
    }
    var updated: Pixel[] = object.progress(object.position);
    for(var i: number = 0; i < updated.length; ++i) {
        screen[updated[i].position.toNumber()] = updated[i].color;
    }
}

setInterval(() => {
    player.direction = readInput();
    player.position.add(player.direction);
    move(player);
    updateScreen();
}, 6000);


