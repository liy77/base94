

type base94string = string;

declare interface Base94 {
    (str: string): base94string;
    encode(data: string): base94string;
    decode(data: base94string): string;
}

declare const base94: Base94;

export = base94;