declare class Range {
    private from_;
    private to_;
    constructor(from: number, to: number);
    isInRange(num: number): boolean;
    notInRange(num: number): boolean;
    range(): number[];
}
export = Range;
