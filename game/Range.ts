class Range {
    private from_: number;
    private to_: number;
    
    public constructor(from: number, to: number) {
        this.from_ = from;
        this.to_ = to;
    }
    
    public isInRange(num: number): boolean {
        return (num >= this.from_ && num <= this.to_);
    }
    
    public notInRange(num: number): boolean {
        return !this.isInRange(num);
    }
    
    public tryToThrowOutOfRange(num: number, name: string, what: string): void {
        if(this.notInRange(num)) {
            throw new RangeError(`${name} is out of range when calling: ${what} whit: ${name} = ${num}`);
        }
    }
    
    public range(): number[] {
        var range: number[] = [];
        for(var i: number = this.from_; i <= this.to_; ++i) {
            range[i] = i;
        }
        return range;
    }
}

export = Range;