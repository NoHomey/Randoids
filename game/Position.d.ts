declare class Position {
    private static max: number;
    private static range: Range;
    private x_: number;
    private y_: number;
    public constructor(x: number, y: number);
    public toNumber(): number;
    public static fromNumber(num: number): Position;
    public static setDirectionMax(max: number): void;
}

export = Position;