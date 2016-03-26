import Range = require("./Range");

class Position {
    private static max: number;
    private static range: Range;
    private x_: number;
    private y_: number;
    
    public constructor(x: number, y: number) {
        Position.range.tryToThrowOutOfRange(x, "x", "new Position(x, y)");
        Position.range.tryToThrowOutOfRange(y, "y", "new Position(x, y)");
        this.x_ = x;
        this.y_ = y;
    }
    
    public set x(x : number) {
        Position.range.tryToThrowOutOfRange(x, "x", "set {Position}.x");
        this.x_ = x;
    }
    
    public set y(y : number) {
        Position.range.tryToThrowOutOfRange(y, "y", "set {Position}.y");
        this.y_ = y;
    }
    
    public get x(): number {
        return this.x_;
    }
    
    public get y(): number {
        return this.y_;
    }
    
    public toNumber(): number {
        return this.x_ * Position.max + this.y_;
    }
    
    public static fromNumber(num: number): Position {
        var range = new Range(0, Position.max * Position.max);
        range.tryToThrowOutOfRange(num, "num", "Position.fromNumber(num)");
        var y: number = num % Position.max;
        var x: number = (num - y) / Position.max;
        return new Position(x, y);
    }
    
    public static setDirectionMax(max: number): void {
        Position.max = max;
        Position.range = new Range(0, max - 1);
    }
}

export = Position;