declare class Position {
    private static max_;
    x: number;
    y: number;
    constructor(x: number, y: number);
    toNumber(): number;
    isEqual(position: Position): boolean;
    add(position: Position): Position;
    sub(position: Position): Position;
    static fromNumber(num: number): Position;
    static setDirectionMax(max: number): void;
}
export = Position;
