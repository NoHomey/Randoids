declare class Range {
    private from_: number;
    private to_: number;
    public constructor(from: number, to: number);
    public isInRange(num: number): boolean;
    public notInRange(num: number): boolean;
    public tryToThrowOutOfRange(num: number, name: string, what: string): void;
    public range(): number[];
}

export = Range;