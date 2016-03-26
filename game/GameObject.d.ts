import Pixel = require('./Pixel');
import Position = require('./Position');

declare class GameObject {
    position: Position;
    public direction: Position;
    figure: Pixel[];
    constructor(position: Position, figure: Pixel[]);
    progress(position: Position): Pixel[];
    isDead(): boolean;
}
export = GameObject;
