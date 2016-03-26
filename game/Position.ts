class Position {
    private static max_: number;
    public x: number;
    public y: number;
    
    public constructor(x: number, y: number) {
        this.x = x;
        this.y = y;
    }
    
    public toNumber(): number {
        return this.x * Position.max_ + this.y;
    }
    
    public isEqual(position: Position): boolean {
        return Boolean((this.x === position.x) && (this.y === position.y));
    }
    
    public add(position: Position): Position {
        return new Position(this.x + position.x, this.y + position.y);
    }
    
    public sub(position: Position): Position {
        return new Position(this.x - position.x, this.y - position.y);
    }
    
    public static fromNumber(num: number): Position {
        var y: number = num % Position.max_;
        var x: number = (num - y) / Position.max_;
        return new Position(x, y);
    }
    
    public static setDirectionMax(max: number): void {
        Position.max_ = max;
    }
}

export = Position;