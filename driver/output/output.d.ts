declare module output {
    class Output {
        constructor(data: number, clock: number, latch: number, blank: number);
        write(screen: Uint16Array): void;
        private data_: number;
        private clock_: number;
        private latch_: number;
        private blank_: number;
    }
}

export = output;